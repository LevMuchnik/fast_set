
#include "..\Utilities\MatLabDefs.h"
#include <memory.h>
#include <algorithm>


template <typename T> mxArray* FindRangeSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz_m,  const mwSize bsz_n);
template <typename T> mxArray* FindRangeSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz_m,  const mwSize bsz_n, mxArray*& pai);
bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[]);

void __cdecl mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
#pragma region check input validity
	if (nrhs!=2) { mexErrMsgTxt("Wrong number of input parameters"); }
	if (nlhs>2) { mexErrMsgTxt("Wrong number of output parameters"); }
	if (mxGetNumberOfDimensions(prhs[0])!=2 || mxGetNumberOfDimensions(prhs[1])!=2) { mexErrMsgTxt("Inputs must have 1 or 2 dimensions"); }
	if ( (mxGetM(prhs[0])>1 && mxGetN(prhs[0])>1)) { mexErrMsgTxt("First Input must be vector, not matrix"); }
	if ( (mxGetN(prhs[1])!=2 ) ) { mexErrMsgTxt("Second index must be sized nx2"); }
	if ( mxIsComplex(prhs[0]) || mxIsComplex(prhs[1]) ) { mexErrMsgTxt("Complex types are not supported"); }
	if (ProcessEmptyInput(prhs[0],prhs[1],nlhs,plhs)) { return ; }
	if (mxGetClassID(prhs[0])!=mxGetClassID(prhs[1]) ) { mexErrMsgTxt("Both vectors must be of the same data type"); }
#pragma endregion // check input validity
	mxClassID classid = mxGetClassID(prhs[0]);
	const double *ap = mxGetPr(prhs[0]);
	const mwSize asz = mxGetNumberOfElements(prhs[0]);
	const double *bp = mxGetPr(prhs[1]);
	const mwSize bsz_m = mxGetM(prhs[1]);
	const mwSize bsz_n = mxGetN(prhs[1]);
	
	if (nlhs<2) {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = FindRangeSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz_m,bsz_n); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = FindRangeSorted(classid,ap,asz,bp,bsz_m,bsz_n); break;
			case mxSINGLE_CLASS		:	plhs[0] = FindRangeSorted(classid,(const float*)ap,asz,(const float*)bp,bsz_m,bsz_n); break;
			case mxINT8_CLASS		:	plhs[0] = FindRangeSorted(classid,(const char*)ap,asz,(const char*)bp,bsz_m,bsz_n); break;
			case mxUINT8_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz_m,bsz_n); break;
			case mxINT16_CLASS		:	plhs[0] = FindRangeSorted(classid,(const short *)ap,asz,(const short*)bp,bsz_m,bsz_n); break;
			case mxUINT16_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz_m,bsz_n); break;
			case mxINT32_CLASS		:	plhs[0] = FindRangeSorted(classid,(const int*)ap,asz,(const int*)bp,bsz_m,bsz_n); break;
			case mxUINT32_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz_m,bsz_n); break;
			case mxINT64_CLASS		:	plhs[0] = FindRangeSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz_m,bsz_n); break;
			case mxUINT64_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz_m,bsz_n); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
	else {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = FindRangeSorted(classid,(const bool*)ap,asz,(const bool*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = FindRangeSorted(classid,ap,asz,bp,bsz_m,bsz_n,plhs[1]); break;
			case mxSINGLE_CLASS		:	plhs[0] = FindRangeSorted(classid,(const float*)ap,asz,(const float*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxINT8_CLASS		:	plhs[0] = FindRangeSorted(classid,(const char*)ap,asz,(const char*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxUINT8_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned char*)ap,asz,(const unsigned char*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxINT16_CLASS		:	plhs[0] = FindRangeSorted(classid,(const short *)ap,asz,(const short*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxUINT16_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned short *)ap,asz,(const unsigned short*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxINT32_CLASS		:	plhs[0] = FindRangeSorted(classid,(const int*)ap,asz,(const int*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxUINT32_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned int*)ap,asz,(const unsigned int*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxINT64_CLASS		:	plhs[0] = FindRangeSorted(classid,(const __int64*)ap,asz,(const __int64*)bp,bsz_m,bsz_n,plhs[1]); break;
			case mxUINT64_CLASS		:	plhs[0] = FindRangeSorted(classid,(const unsigned __int64*)ap,asz,(const unsigned __int64*)bp,bsz_m,bsz_n,plhs[1]); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
	if (nlhs>1) {
		mxArray* Result = mxCreateCellMatrix(bsz_m,bsz_n);
		#ifdef _M_X64
			const __int64 *pIndex = (const  __int64*)mxGetPr(plhs[0]);
		#else
		const int *pIndex = (const int*)mxGetPr(plhs[0]);
		#endif
		for (unsigned __int64 i = 0 ; i < bsz_m; ++i) {
			if (pIndex[i]!=0 && pIndex[i+bsz_m]!=0) {
				mxArray* CurrentResultsSet = mxCreateNumericMatrix(1,pIndex[i+bsz_m]-pIndex[i]+1,mxINT64_CLASS,mxREAL);
			}
		}
	}
}

bool ProcessEmptyInput(const mxArray* ap, const mxArray* bp,int nlhs, mxArray *plhs[])
{
	#ifdef _M_X64
		mxClassID classid = mxUINT64_CLASS;
	#else  // 32 bit compilation
		mxClassID classid = mxUINT32_CLASS;
	#endif
	if (mxIsEmpty(bp)) {
		if (nlhs>1) {		
			plhs[1] = mxCreateNumericMatrix(0,0,classid,mxREAL); 
			if (nlhs>2) {
				plhs[2] = mxCreateNumericMatrix(0,0,classid,mxREAL); 
			}
		}
		return true;
	}
	else if (mxIsEmpty(ap)) {
		if (nlhs>1) {		
			plhs[1] = mxCreateNumericMatrix(mxGetM(bp),mxGetN(bp),classid,mxREAL); 
			if (nlhs>2) {
				plhs[2] = mxCreateCellMatrix(mxGetM(bp),mxGetN(bp));
			}
		}
		return true;
	}	
	else { return false; }	
}


template <typename T> mxArray* FindRangeSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz_m, const mwSize bsz_n)
{
	if (asz==0 || bsz_m==0 || bsz_n==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); } // should never be triggered . see ProcessEmptyInput	
	#ifdef _M_X64
		mxArray* Result = mxCreateNumericMatrix(bsz_m,bsz_n,mxINT64_CLASS,mxREAL);	
		__int64 *pResult =(__int64*)mxGetPr(Result);
		__int64 p_start, p_end;
	#else 
		mxArray* Result = mxCreateNumericMatrix(bsz_m,bsz_n,mxINT32_CLASS,mxREAL);	
		int *pResult =(int*)mxGetPr(Result);
		int p_start, p_end;
	#endif
	for (unsigned __int64 i = 0 ; i < bsz_m; ++i) {
		if (*(bp+i)>*(bp+i+bsz_m)) {
			p_start = 0;  p_end = 0;
		}
		else {
			p_start= std::lower_bound(ap, ap+asz, *(bp+i))-ap;
			if (p_start!=asz) {
				p_end = std::upper_bound(ap, ap+asz, *(bp+i+bsz_m))-ap;
				if (p_end!=0 && p_end>=p_start) { ++p_start; p_end;  } // indeces are 1-based in  MatLab
				// else both p_start & p_end are 0. 
			} 
			else { // not found
				p_start = 0;  p_end = 0;
			}
		}
		pResult[i] = p_start; 
		pResult[i+bsz_m] = p_end; 
	}
	return Result;
}

template <typename T> mxArray* FindRangeSorted( mxClassID classid,const T* ap,  const mwSize asz,const T* bp,  const mwSize bsz_m, const mwSize bsz_n,mxArray*& pIDs)
{
	if (asz==0 || bsz_m==0 || bsz_n==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); } // should never be triggered . see ProcessEmptyInput	
	pIDs = mxCreateCellMatrix(bsz_m,1);
	#ifdef _M_X64
		mxArray* Result = mxCreateNumericMatrix(bsz_m,bsz_n,mxINT64_CLASS,mxREAL);	
		__int64 *pResult =(__int64*)mxGetPr(Result);
		__int64 p_start, p_end;
		unsigned __int64 i;
	#else 
		mxArray* Result = mxCreateNumericMatrix(bsz_m,bsz_n,mxINT32_CLASS,mxREAL);	
		int *pResult =(int*)mxGetPr(Result);
		int p_start, p_end;
		unsigned int i;
	#endif
	for (i = 0 ; i < bsz_m; ++i) {
		if (*(bp+i)>*(bp+i+bsz_m)) {
			p_start = 0;  p_end = 0;
		}
		else {
			p_start= std::lower_bound(ap, ap+asz, *(bp+i))-ap;
			if (p_start!=asz) {
				p_end = std::upper_bound(ap, ap+asz, *(bp+i+bsz_m))-ap;
				if (p_end!=0 && p_end>=p_start) { 
					++p_start; p_end;  
					mxArray* CurrentValues = mxCreateNumericMatrix(1,p_end-p_start+1,classid,mxREAL);	
					memcpy(mxGetPr(CurrentValues),(const void*)(ap+p_start-1),sizeof(T)*(p_end-p_start+1));				
					mxSetCell(pIDs,i,CurrentValues);
				} // indeces are 1-based in  MatLab
				// else both p_start & p_end are 0. 
			} 
			else { // not found
				p_start = 0;  p_end = 0;
			}
		}
		pResult[i] = p_start; 
		pResult[i+bsz_m] = p_end; 
	}
	return Result;
}