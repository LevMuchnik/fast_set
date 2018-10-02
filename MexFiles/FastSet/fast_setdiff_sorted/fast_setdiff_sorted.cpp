
#include "..\Utilities\MatLabDefs.h"
#include <memory.h>


template <typename T> mxArray* SetDiffSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz);
template <typename T> mxArray* SetDiffSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz, mxArray*& pai);
bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[]);

void __cdecl mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
#pragma region check input validity
	if (nrhs!=2) { mexErrMsgTxt("Wrong number of input parameters"); }
	if (nlhs>2) { mexErrMsgTxt("Wrong number of output parameters"); }
	if (mxGetNumberOfDimensions(prhs[0])!=2 || mxGetNumberOfDimensions(prhs[1])!=2) { mexErrMsgTxt("Inputs must be vectors"); }
	if ( (mxGetM(prhs[0])>1 && mxGetN(prhs[0])>1) || (mxGetM(prhs[1])>1 && mxGetN(prhs[1])>1) ) { mexErrMsgTxt("Inputs must be vectors, not matrices"); }
	if ( mxIsComplex(prhs[0]) || mxIsComplex(prhs[1]) ) { mexErrMsgTxt("Complex types are not supported"); }
	if (ProcessEmptyInput(prhs[0],prhs[1],nlhs,plhs)) { return ; }
	if (mxGetClassID(prhs[0])!=mxGetClassID(prhs[1]) ) { mexErrMsgTxt("Both vectors must be of the same data type"); }
#pragma endregion // check input validity
	mxArray *c = NULL, *ia=NULL;
	mxClassID classid = mxGetClassID(prhs[0]);
	const double *ap = mxGetPr(prhs[0]);
	const mwSize asz = mxGetNumberOfElements(prhs[0]);
	const double *bp = mxGetPr(prhs[1]);
	const mwSize bsz = mxGetNumberOfElements(prhs[1]);
	if (nlhs<=1) {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = SetDiffSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = SetDiffSorted(classid,ap,asz,bp,bsz); break;
			case mxSINGLE_CLASS		:	plhs[0] = SetDiffSorted(classid,(const float*)ap,asz,(const float*)bp,bsz); break;
			case mxINT8_CLASS		:	plhs[0] = SetDiffSorted(classid,(const char*)ap,asz,(const char*)bp,bsz); break;
			case mxUINT8_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz); break;
			case mxINT16_CLASS		:	plhs[0] = SetDiffSorted(classid,(const short *)ap,asz,(const short*)bp,bsz); break;
			case mxUINT16_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz); break;
			case mxINT32_CLASS		:	plhs[0] = SetDiffSorted(classid,(const int*)ap,asz,(const int*)bp,bsz); break;
			case mxUINT32_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz); break;
			case mxINT64_CLASS		:	plhs[0] = SetDiffSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz); break;
			case mxUINT64_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
	else {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = SetDiffSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz,plhs[1]); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = SetDiffSorted(classid,ap,asz,bp,bsz,plhs[1]); break;
			case mxSINGLE_CLASS		:	plhs[0] = SetDiffSorted(classid,(const float*)ap,asz,(const float*)bp,bsz,plhs[1]); break;
			case mxINT8_CLASS		:	plhs[0] = SetDiffSorted(classid,(const char*)ap,asz,(const char*)bp,bsz,plhs[1]); break;
			case mxUINT8_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz,plhs[1]); break;
			case mxINT16_CLASS		:	plhs[0] = SetDiffSorted(classid,(const short *)ap,asz,(const short*)bp,bsz,plhs[1]); break;
			case mxUINT16_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz,plhs[1]); break;
			case mxINT32_CLASS		:	plhs[0] = SetDiffSorted(classid,(const int*)ap,asz,(const int*)bp,bsz,plhs[1]); break;
			case mxUINT32_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz,plhs[1]); break;
			case mxINT64_CLASS		:	plhs[0] = SetDiffSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz,plhs[1]); break;
			case mxUINT64_CLASS		:	plhs[0] = SetDiffSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz,plhs[1]); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
}

bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[])
{
	if (!mxIsEmpty(ap) && !mxIsEmpty(bp)) { return false; }
	if (mxIsEmpty(ap)) { // a is empty
		 plhs[0] = mxCreateNumericMatrix(0,0,mxLOGICAL_CLASS,mxREAL);
		 if (nlhs>1) {
			 #ifdef _M_X64
				plhs[1] = mxCreateNumericMatrix(0,0,mxUINT64_CLASS,mxREAL); 
			#else  // 32 bit compilation
			  plhs[1] = mxCreateNumericMatrix(0,0,mxUINT32_CLASS,mxREAL); 
			#endif
		 }
	}
	else { // if (mxIsEmpty(bp)) {
		 plhs[0] = mxDuplicateArray(ap);
		#ifdef _M_X64
			plhs[1] = mxCreateNumericMatrix(mxGetM(ap),mxGetN(ap),mxUINT64_CLASS,mxREAL); 
			unsigned __int64* pplhs_1 = (unsigned __int64*)mxGetPr(plhs[1]);
			for (unsigned __int64 i = 0; i < mxGetNumberOfElements(ap); ++i) {
				pplhs_1[i] = (i+1);
			}
		#else  // 32 bit compilation
			plhs[1] = mxCreateNumericMatrix(mxGetM(ap),mxGetN(ap),mxUINT32_CLASS,mxREAL); 
			unsigned int* pplhs_1 = (unsigned int*)mxGetPr(plhs[1]);
			for (unsigned int i = 0; i < mxGetNumberOfElements(ap); ++i) {
				pplhs_1[i] = (i+1);
			}
		#endif
	}
	return true;
}



template <typename T> mxArray* SetDiffSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz)
{
	if (asz==0 && bsz==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); }
	unsigned int ai = 0, bi = 0;
	T* ResultsBuffer = new T[asz];   // allocate maximal 
	mwSize CurrentBufferSize = 0;
	while (ai<asz && bi <bsz) {
		if (ap[ai]<bp[bi]) { ResultsBuffer[CurrentBufferSize++] = ap[ai++]; }
		else if (ap[ai]>bp[bi]) { bi++;	}
		else { ai++; ++bi; }
	}
	while (ai<asz) { ResultsBuffer[CurrentBufferSize++] = ap[ai++]; }
	mxArray* Result = mxCreateNumericMatrix(1,CurrentBufferSize,classid,mxREAL);
	if (CurrentBufferSize!=0) { memcpy((void*)mxGetPr(Result),ResultsBuffer,sizeof(T)*CurrentBufferSize); }
	delete ResultsBuffer;
	return Result;
}

template <typename T> mxArray* SetDiffSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz, mxArray*& pai)
{
	if (asz==0 && bsz==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); }
	
	unsigned int ai = 0, bi = 0;
	T* ResultsBuffer = new T[asz];   // allocate maximal 
	mwSize *ais = new mwSize[asz];
	mwSize CurrentBufferSize = 0;
	while (ai<asz && bi <bsz) {
		if (ap[ai]<bp[bi]) { ResultsBuffer[CurrentBufferSize] = ap[ai++]; ais[CurrentBufferSize++] = ai; } // notice, we record next index as C++ is 0-based. 
		else if (ap[ai]>bp[bi]) { bi++; 	}
		else { ai++; ++bi; } 
	}
	while (ai<asz) { ResultsBuffer[CurrentBufferSize] = ap[ai++]; ais[CurrentBufferSize++] = ai;}
	mxArray* Result = mxCreateNumericMatrix(1,CurrentBufferSize,classid,mxREAL);
	if (CurrentBufferSize!=0) {memcpy((void*)mxGetPr(Result),ResultsBuffer,sizeof(T)*CurrentBufferSize);}

	#ifdef _M_X64
		pai = mxCreateNumericMatrix(1,CurrentBufferSize,mxUINT64_CLASS,mxREAL);
		memcpy((void*)mxGetPr(pai),ais,sizeof(unsigned __int64)*CurrentBufferSize);
	#else  // 32 bit compilation
			pai = mxCreateNumericMatrix(1,CurrentBufferSize,mxUINT32_CLASS,mxREAL);
		memcpy((void*)mxGetPr(pai),ais,sizeof(unsigned int)*CurrentBufferSize);
	#endif

	delete ResultsBuffer;
	delete ais;
	return Result;
}