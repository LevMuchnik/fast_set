
#include "..\Utilities\MatLabDefs.h"
#include <memory.h>


template <typename T> mxArray* XORSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz);
template <typename T> mxArray* XORSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz, mxArray*& pai,mxArray*& pbi);
bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[]);

void __cdecl mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
#pragma region check input validity
	if (nrhs!=2) { mexErrMsgTxt("Wrong number of input parameters"); }
	if (nlhs==2 || nlhs>3) { mexErrMsgTxt("Wrong number of output parameters"); }
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
			case mxLOGICAL_CLASS	:	plhs[0] = XORSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = XORSorted(classid,ap,asz,bp,bsz); break;
			case mxSINGLE_CLASS		:	plhs[0] = XORSorted(classid,(const float*)ap,asz,(const float*)bp,bsz); break;
			case mxINT8_CLASS		:	plhs[0] = XORSorted(classid,(const char*)ap,asz,(const char*)bp,bsz); break;
			case mxUINT8_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz); break;
			case mxINT16_CLASS		:	plhs[0] = XORSorted(classid,(const short *)ap,asz,(const short*)bp,bsz); break;
			case mxUINT16_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz); break;
			case mxINT32_CLASS		:	plhs[0] = XORSorted(classid,(const int*)ap,asz,(const int*)bp,bsz); break;
			case mxUINT32_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz); break;
			case mxINT64_CLASS		:	plhs[0] = XORSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz); break;
			case mxUINT64_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
	else {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = XORSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz,plhs[1],plhs[2]); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = XORSorted(classid,ap,asz,bp,bsz,plhs[1],plhs[2]); break;
			case mxSINGLE_CLASS		:	plhs[0] = XORSorted(classid,(const float*)ap,asz,(const float*)bp,bsz,plhs[1],plhs[2]); break;
			case mxINT8_CLASS		:	plhs[0] = XORSorted(classid,(const char*)ap,asz,(const char*)bp,bsz,plhs[1],plhs[2]); break;
			case mxUINT8_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz,plhs[1],plhs[2]); break;
			case mxINT16_CLASS		:	plhs[0] = XORSorted(classid,(const short *)ap,asz,(const short*)bp,bsz,plhs[1],plhs[2]); break;
			case mxUINT16_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz,plhs[1],plhs[2]); break;
			case mxINT32_CLASS		:	plhs[0] = XORSorted(classid,(const int*)ap,asz,(const int*)bp,bsz,plhs[1],plhs[2]); break;
			case mxUINT32_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz,plhs[1],plhs[2]); break;
			case mxINT64_CLASS		:	plhs[0] = XORSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz,plhs[1],plhs[2]); break;
			case mxUINT64_CLASS		:	plhs[0] = XORSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz,plhs[1],plhs[2]); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
}

bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[])
{
	if (!mxIsEmpty(ap) && !mxIsEmpty(bp)) { return false; }
	plhs[0] = mxDuplicateArray(mxIsEmpty(bp) ? ap : bp); 
	if (nlhs>1) {
		#ifdef _M_X64
			plhs[1] = mxCreateNumericMatrix(mxGetNumberOfElements(ap),1,mxUINT64_CLASS,mxREAL); 
			unsigned __int64* aip = (unsigned __int64*)mxGetPr(plhs[1]);
			for (unsigned __int64 i = 0; i < mxGetNumberOfElements(plhs[1]); ++i) {
				aip[i] = (i+1);
			}
		#else  // 32 bit compilation
			plhs[1] = mxCreateNumericMatrix(mxGetNumberOfElements(ap),1,mxUINT32_CLASS,mxREAL); 
			unsigned int* aip = (unsigned int*)mxGetPr(plhs[1]);
			for (unsigned int i = 0; i < mxGetNumberOfElements(plhs[1]); ++i) {
				aip[i] = (i+1);
			}
		#endif
		if (nlhs>2) {
			#ifdef _M_X64
			plhs[2] = mxCreateNumericMatrix(mxGetNumberOfElements(bp),1,mxUINT64_CLASS,mxREAL); 
			unsigned __int64* bip = (unsigned __int64*)mxGetPr(plhs[2]);
			for (unsigned __int64 i = 0; i < mxGetNumberOfElements(plhs[2]); ++i) {
				bip[i] = (i+1);
			}
		#else  // 32 bit compilation
			plhs[2] = mxCreateNumericMatrix(mxGetNumberOfElements(bp),1,mxUINT32_CLASS,mxREAL); 
			unsigned int* bip = (unsigned int*)mxGetPr(plhs[2]);
			for (unsigned int i = 0; i < mxGetNumberOfElements(plhs[2]); ++i) {
				bip[i] = (i+1);
			}
		#endif
		}
	}
	return true;
}

template <typename T> mxArray* XORSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz)
{
	if (asz==0 && bsz==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); }
	unsigned int ai = 0, bi = 0;
	T* ResultsBuffer = new T[ asz + bsz ];   // allocate maximal 
	mwSize CurrentBufferSize = 0;
	while (ai<asz && bi <bsz) {
		if (ap[ai]<bp[bi]) { ResultsBuffer[CurrentBufferSize++] = ap[ai++]; }
		else if (ap[ai]>bp[bi]) { ResultsBuffer[CurrentBufferSize++] = bp[bi++];}
		else { ai++; ++bi; }
	}
	while (ai<asz) { ResultsBuffer[CurrentBufferSize++] = ap[ai++]; }
	while (bi <bsz) { ResultsBuffer[CurrentBufferSize++] = bp[bi++]; }
	mxArray* Result = mxCreateNumericMatrix(1,CurrentBufferSize,classid,mxREAL);
	if (CurrentBufferSize!=0) { memcpy((void*)mxGetPr(Result),ResultsBuffer,sizeof(T)*CurrentBufferSize); }
	delete ResultsBuffer;
	return Result;
}

template <typename T> mxArray* XORSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz, mxArray*& pai,mxArray*& pbi)
{
	if (asz==0 && bsz==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); }
	
	unsigned int ai = 0, bi = 0;
	T* ResultsBuffer = new T[ asz + bsz];   // allocate maximal 
	mwSize *ais = new mwSize[asz], *bis = new mwSize[bsz];
	mwSize ais_i = 0, bis_i = 0;
	mwSize CurrentBufferSize = 0;
	while (ai<asz && bi <bsz) {
		if (ap[ai]<bp[bi]) { ResultsBuffer[CurrentBufferSize++] = ap[ai++]; ais[ais_i++] = ai; } 
		else if (ap[ai]>bp[bi]) {  ResultsBuffer[CurrentBufferSize++] = bp[bi++]; bis[bis_i++] = bi;  	}
		else { ai++; ++bi; } 
	}
	while (ai<asz) { ResultsBuffer[CurrentBufferSize++] = ap[ai++]; ais[ais_i++] = ai; }
	while (bi <bsz) { ResultsBuffer[CurrentBufferSize++] = bp[bi++]; bis[bis_i++] = bi; }
	mxArray* Result = mxCreateNumericMatrix(1,CurrentBufferSize,classid,mxREAL);
	memcpy((void*)mxGetPr(Result),ResultsBuffer,sizeof(T)*CurrentBufferSize);

	#ifdef _M_X64
		pai = mxCreateNumericMatrix(1,ais_i,mxUINT64_CLASS,mxREAL);
		if (CurrentBufferSize!=0) { memcpy((void*)mxGetPr(pai),ais,sizeof(unsigned __int64)*ais_i); }
		pbi = mxCreateNumericMatrix(1,bis_i,mxUINT64_CLASS,mxREAL);
		if (CurrentBufferSize!=0) {memcpy((void*)mxGetPr(pbi),bis,sizeof(unsigned __int64)*bis_i); }
	#else  // 32 bit compilation
		pai = mxCreateNumericMatrix(1,ais_i,mxUINT32_CLASS,mxREAL);
		if (CurrentBufferSize!=0) { memcpy((void*)mxGetPr(pai),ais,sizeof(unsigned int)*ais_i); }
		pbi = mxCreateNumericMatrix(1,bis_i,mxUINT32_CLASS,mxREAL);
		if (CurrentBufferSize!=0) {memcpy((void*)mxGetPr(pbi),bis,sizeof(unsigned int)*bis_i); }
	#endif

	delete ResultsBuffer;
	delete ais;
	delete bis;
	return Result;
}