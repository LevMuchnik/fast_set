
#include "..\Utilities\MatLabDefs.h"
#include <memory.h>

template <typename T> mxArray* IsMemberSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz);
template <typename T> mxArray* IsMemberSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz, mxArray*& pai);
bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[]);
void __cdecl mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
#pragma region check input validity
	if (nrhs!=2) { mexErrMsgTxt("Wrong number of input parameters"); }
	if (nlhs!=1 && nlhs!=2) { mexErrMsgTxt("Wrong number of output parameters"); }
	if (mxGetNumberOfDimensions(prhs[0])!=2 || mxGetNumberOfDimensions(prhs[1])!=2) { mexErrMsgTxt("Inputs must be vectors"); }
	if ( (mxGetM(prhs[0])>1 && mxGetN(prhs[0])>1) || (mxGetM(prhs[1])>1 && mxGetN(prhs[1])>1) ) { mexErrMsgTxt("Inputs must be vectors, not matrices"); }
	if (ProcessEmptyInput(prhs[0],prhs[1],nlhs,plhs)) { return ; }
	if ( mxIsComplex(prhs[0]) || mxIsComplex(prhs[1]) ) { mexErrMsgTxt("Complex types are not supported"); }
	if (mxGetClassID(prhs[0])!=mxGetClassID(prhs[1]) ) { mexErrMsgTxt("Both vectors must be of the same data type"); }
#pragma endregion // check input validity

	mxClassID classid = mxGetClassID(prhs[0]);
	const double *ap = mxGetPr(prhs[0]);
	const mwSize asz = mxGetNumberOfElements(prhs[0]);
	const double *bp = mxGetPr(prhs[1]);
	const mwSize bsz = mxGetNumberOfElements(prhs[1]);
	if (nlhs<=1) {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = IsMemberSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = IsMemberSorted(classid,ap,asz,bp,bsz); break;
			case mxSINGLE_CLASS		:	plhs[0] = IsMemberSorted(classid,(const float*)ap,asz,(const float*)bp,bsz); break;
			case mxINT8_CLASS		:	plhs[0] = IsMemberSorted(classid,(const char*)ap,asz,(const char*)bp,bsz); break;
			case mxUINT8_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz); break;
			case mxINT16_CLASS		:	plhs[0] = IsMemberSorted(classid,(const short *)ap,asz,(const short*)bp,bsz); break;
			case mxUINT16_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz); break;
			case mxINT32_CLASS		:	plhs[0] = IsMemberSorted(classid,(const int*)ap,asz,(const int*)bp,bsz); break;
			case mxUINT32_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz); break;
			case mxINT64_CLASS		:	plhs[0] = IsMemberSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz); break;
			case mxUINT64_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
	else {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = IsMemberSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz,plhs[1]); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = IsMemberSorted(classid,ap,asz,bp,bsz,plhs[1]); break;
			case mxSINGLE_CLASS		:	plhs[0] = IsMemberSorted(classid,(const float*)ap,asz,(const float*)bp,bsz,plhs[1]); break;
			case mxINT8_CLASS		:	plhs[0] = IsMemberSorted(classid,(const char*)ap,asz,(const char*)bp,bsz,plhs[1]); break;
			case mxUINT8_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz,plhs[1]); break;
			case mxINT16_CLASS		:	plhs[0] = IsMemberSorted(classid,(const short *)ap,asz,(const short*)bp,bsz,plhs[1]); break;
			case mxUINT16_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz,plhs[1]); break;
			case mxINT32_CLASS		:	plhs[0] = IsMemberSorted(classid,(const int*)ap,asz,(const int*)bp,bsz,plhs[1]); break;
			case mxUINT32_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz,plhs[1]); break;
			case mxINT64_CLASS		:	plhs[0] = IsMemberSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz,plhs[1]); break;
			case mxUINT64_CLASS		:	plhs[0] = IsMemberSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz,plhs[1]); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
}

bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[])
{
	if (!mxIsEmpty(ap) && !mxIsEmpty(bp)) { return false; }
	plhs[0] = mxCreateNumericMatrix(mxGetM(ap),mxGetN(ap),mxLOGICAL_CLASS,mxREAL); 
	if (nlhs>1) {
		#ifdef _M_X64
			plhs[1] = mxCreateNumericMatrix(mxGetM(ap),mxGetN(ap),mxUINT64_CLASS,mxREAL); 
		#else  // 32 bit compilation
			plhs[1] = mxCreateNumericMatrix(mxGetM(ap),mxGetN(ap),mxUINT32_CLASS,mxREAL); 
		#endif
	}
	return true;
}
template <typename T> mxArray* IsMemberSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz)
{
	mxArray* Result = mxCreateLogicalMatrix(1,asz);  // initialized to 0
	bool* pResult = reinterpret_cast<bool*>(mxGetPr(Result));
	if (asz==0 || bsz==0) { return Result; }
	unsigned int ai = 0, bi = 0;
	while (ai<asz && bi < bsz) {
		if (ap[ai]==bp[bi]) {
			pResult[ai]	= true;
			++ai; ++bi;
		}
		else if (ap[ai]<bp[bi]) { ++ai; }
		else { ++bi; }
	}
	return Result;
}

template <typename T> mxArray* IsMemberSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz, mxArray*& pai)
{
	mxArray* Result = mxCreateLogicalMatrix(1,asz);  // initialized to 0
	#ifdef _M_X64
		pai =  mxCreateNumericMatrix(1,asz,mxUINT64_CLASS,mxREAL);
		unsigned __int64* ppai= reinterpret_cast<unsigned __int64*>(mxGetPr(pai));
	#else  // 32 bit compilation
		pai =  mxCreateNumericMatrix(1,asz,mxUINT32_CLASS,mxREAL);
		unsigned int* ppai= reinterpret_cast<unsigned int*>(mxGetPr(pai));
	#endif

	unsigned char* pResult = reinterpret_cast<unsigned char*>(mxGetPr(Result)); // don't use bool as it might have different size. 
	if (asz==0 || bsz==0) { return Result; }
	unsigned int ai = 0, bi = 0;
	while (ai<asz && bi < bsz) {
		if (ap[ai]==bp[bi]) {
			pResult[ai]	= true;
			ppai[ai++] = ++bi;	
		}
		else if (ap[ai]<bp[bi]) { ++ai; }
		else { ++bi; }
	}
	return Result;
}