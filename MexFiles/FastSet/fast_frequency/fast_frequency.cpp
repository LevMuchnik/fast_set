
#include "..\Utilities\MatLabDefs.h"
#include <memory.h>
#include <set>
#include <vector>
#include <algorithm>

template <typename T> mxArray* Frequency( mxClassID classid,const mxArray* A,const T* ap,  const mwSize asz);
template <typename T> mxArray* Frequency( mxClassID classid,const mxArray* A,const T* ap,  const mwSize asz, mxArray*& pIDs);
bool ProcessEmptyInput(const mxArray* ap,int nlhs, mxArray *plhs[]);

void __cdecl mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
#pragma region check input validity
	if (nrhs!=1) { mexErrMsgTxt("Wrong number of input parameters"); }
	if (nlhs>1 && nlhs!=2 ) { mexErrMsgTxt("Wrong number of output parameters"); }
	if (mxGetNumberOfDimensions(prhs[0])!=2 ) { mexErrMsgTxt("Inputs must be vectors"); }
	if (mxGetM(prhs[0])>1 && mxGetN(prhs[0])>1)  { mexErrMsgTxt("Inputs must be vectors, not matrices")	; }
	if (ProcessEmptyInput(prhs[0],nlhs,plhs)) { return ; }
	if ( mxIsComplex(prhs[0]) ) { mexErrMsgTxt("Complex types are not supported"); }
#pragma endregion // check input validity
	mxClassID classid = mxGetClassID(prhs[0]);
	const double *ap = mxGetPr(prhs[0]);
	const mwSize asz = mxGetNumberOfElements(prhs[0]);
	if (nlhs<=1) {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = Frequency(classid,prhs[0],(const bool*)ap,asz); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = Frequency(classid,prhs[0],ap,asz); break;
			case mxSINGLE_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const float*)ap,asz); break;
			case mxINT8_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const char*)ap,asz); break;
			case mxUINT8_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned char*)ap,asz); break;
			case mxINT16_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const short *)ap,asz); break;
			case mxUINT16_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned short *)ap,asz); break;
			case mxINT32_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const int*)ap,asz); break;
			case mxUINT32_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned int*)ap,asz); break;
			case mxINT64_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const __int64*)ap,asz); break;
			case mxUINT64_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned __int64*)ap,asz); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
	else {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = Frequency(classid,prhs[0],(const bool*)ap,asz,plhs[1]); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = Frequency(classid,prhs[0],ap,asz,plhs[1]); break;
			case mxSINGLE_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const float*)ap,asz,plhs[1]); break;
			case mxINT8_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const char*)ap,asz,plhs[1]); break;
			case mxUINT8_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned char*)ap,asz,plhs[1]); break;
			case mxINT16_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const short *)ap,asz,plhs[1]); break;
			case mxUINT16_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned short *)ap,asz,plhs[1]); break;
			case mxINT32_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const int*)ap,asz,plhs[1]); break;
			case mxUINT32_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned int*)ap,asz,plhs[1]); break;
			case mxINT64_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const __int64*)ap,asz,plhs[1]); break;
			case mxUINT64_CLASS		:	plhs[0] = Frequency(classid,prhs[0],(const unsigned __int64*)ap,asz,plhs[1]); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
}


bool ProcessEmptyInput(const mxArray* ap,int nlhs, mxArray *plhs[])
{
	if (!mxIsEmpty(ap)) { return false; }
	plhs[0] = mxCreateNumericMatrix(0,0,mxGetClassID(ap),mxREAL); 
	if (nlhs>1) {
		#ifdef _M_X64
			mxClassID classid = mxUINT64_CLASS;
		#else  // 32 bit compilation
			mxClassID classid = mxUINT32_CLASS;
		#endif
		plhs[1] = mxCreateNumericMatrix(0,0,classid,mxREAL); 
	}
	return true;
}
template <typename T> mxArray* Frequency( mxClassID classid,const mxArray* A,const T* ap,  const mwSize asz)
{
	mxArray *mxDummy = NULL;
	mxArray* Result = Frequency(classid,A,ap,asz,mxDummy);
	mxDestroyArray(mxDummy); mxDummy = NULL;	
	return Result;
}

template <typename T> mxArray* Frequency( mxClassID classid,const  mxArray* A,const T* ap,  const mwSize asz, mxArray*& pIDs)
{
	if (asz==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); }
	mxArray* plhs[3]; 
	mxArray* Input = const_cast<mxArray*>(A);
	if (mexCallMATLAB(3, plhs,1,&Input ,"fast_unique")!=0) {  mexErrMsgTxt("Call to fast_unique failed"); }
	mxDestroyArray(plhs[1]); plhs[1] = NULL;
	const mwSize ResultSize = mxGetM(plhs[0])*mxGetN(plhs[0]);	
	pIDs = plhs[0];

	#ifdef _M_X64
		mxArray* Result = mxCreateNumericMatrix( 1, ResultSize , mxUINT64_CLASS,mxREAL);	
		unsigned __int64* pResult = (unsigned __int64*)mxGetPr(Result);
		const __int64* pIndexes = (const __int64*)mxGetPr(plhs[2]);
	#else  // 32 bit compilation
		mxArray* Result = mxCreateNumericMatrix( 1,ResultSize , mxUINT32_CLASS,mxREAL);	
		unsigned int* pResult = (unsigned int*)mxGetPr(Result);
		const int* pIndexes = (const int*)mxGetPr(plhs[2]);
	#endif
	
	const mwSize SourceSize = mxGetM( plhs[2])*mxGetN(plhs[2]);
	
	for (mwSize i = 0; i < SourceSize; ++i) {
		++pResult[ pIndexes[i]-1] ;
	}
	mxDestroyArray(plhs[2]); plhs[2] = NULL;
	return Result;
}