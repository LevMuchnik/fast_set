
#include "..\Utilities\MatLabDefs.h"

#include <memory.h>
#include <set>
#include <vector>
#include <algorithm>


template <typename T> mxArray* Unique( mxClassID classid,const T* ap,  const mwSize asz,bool IsVertical);
template <typename T> mxArray* Unique( mxClassID classid,const T* ap,  const mwSize asz, mxArray*& pm,mxArray*& pn,bool IsVertical);
bool ProcessEmptyInput(const mxArray* ap,int nlhs, mxArray *plhs[]);

void __cdecl mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
#pragma region check input validity
	if (nrhs!=1) { mexErrMsgTxt("Wrong number of input parameters"); }
	//if (nlhs==2 || nlhs>3) { mexErrMsgTxt("Wrong number of output parameters"); }
	if (nlhs>1 && nlhs!=3 ) { mexErrMsgTxt("Wrong number of output parameters"); }
	if (mxGetNumberOfDimensions(prhs[0])!=2 ) { mexErrMsgTxt("Inputs must be vectors"); }
	if (mxGetM(prhs[0])>1 && mxGetN(prhs[0])>1)  { mexErrMsgTxt("Inputs must be vectors, not matrices"); }
	if (ProcessEmptyInput(prhs[0],nlhs,plhs)) { return ; }
	if ( mxIsComplex(prhs[0]) ) { mexErrMsgTxt("Complex types are not supported"); }
#pragma endregion // check input validity
	mxClassID classid = mxGetClassID(prhs[0]);
	const double *ap = mxGetPr(prhs[0]);
	const mwSize asz = mxGetNumberOfElements(prhs[0]);
	bool IsVertical  = (mxGetM(prhs[0]) > mxGetN(prhs[0]));
	if (nlhs<=1) {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = Unique(classid,(const bool*)ap,asz,IsVertical); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = Unique(classid,ap,asz,IsVertical); break;
			case mxSINGLE_CLASS		:	plhs[0] = Unique(classid,(const float*)ap,asz,IsVertical); break;
			case mxINT8_CLASS		:	plhs[0] = Unique(classid,(const char*)ap,asz,IsVertical); break;
			case mxUINT8_CLASS		:	plhs[0] = Unique(classid,(const unsigned char*)ap,asz,IsVertical); break;
			case mxINT16_CLASS		:	plhs[0] = Unique(classid,(const short *)ap,asz,IsVertical); break;
			case mxUINT16_CLASS		:	plhs[0] = Unique(classid,(const unsigned short *)ap,asz,IsVertical); break;
			case mxINT32_CLASS		:	plhs[0] = Unique(classid,(const int*)ap,asz,IsVertical); break;
			case mxUINT32_CLASS		:	plhs[0] = Unique(classid,(const unsigned int*)ap,asz,IsVertical); break;
			case mxINT64_CLASS		:	plhs[0] = Unique(classid,(const __int64*)ap,asz,IsVertical); break;
			case mxUINT64_CLASS		:	plhs[0] = Unique(classid,(const unsigned __int64*)ap,asz,IsVertical); break;
			default					:	mexErrMsgTxt("Unsapported data type");
		}
	}
	else {
		switch (classid) {
			case mxLOGICAL_CLASS	:	plhs[0] = Unique(classid,(const bool*)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxCHAR_CLASS		:	mexErrMsgTxt("Unsapported data type");
			case mxDOUBLE_CLASS		:	plhs[0] = Unique(classid,ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxSINGLE_CLASS		:	plhs[0] = Unique(classid,(const float*)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxINT8_CLASS		:	plhs[0] = Unique(classid,(const char*)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxUINT8_CLASS		:	plhs[0] = Unique(classid,(const unsigned char*)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxINT16_CLASS		:	plhs[0] = Unique(classid,(const short *)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxUINT16_CLASS		:	plhs[0] = Unique(classid,(const unsigned short *)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxINT32_CLASS		:	plhs[0] = Unique(classid,(const int*)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxUINT32_CLASS		:	plhs[0] = Unique(classid,(const unsigned int*)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxINT64_CLASS		:	plhs[0] = Unique(classid,(const __int64*)ap,asz,plhs[1],plhs[2],IsVertical); break;
			case mxUINT64_CLASS		:	plhs[0] = Unique(classid,(const unsigned __int64*)ap,asz,plhs[1],plhs[2],IsVertical); break;
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
		if (nlhs>2) {
			plhs[2] = mxCreateNumericMatrix(0,0,classid,mxREAL); 
		}
	}
	return true;
}
template <typename T> void PerformSort(std::vector<T>& Data)
{
	//Concurrency::samples::parallel_radixsort(Data.begin(), Data.end()); // can't handle floating point types or types larger than size_t (i.e. 64bit ints in 32bit build) 
	//Concurrency::samples::parallel_buffered_sort(Data.begin(), Data.end()); // can't handle floating point types. 
	std::sort(Data.begin(), Data.end());
}
template <> void PerformSort(std::vector<double>& Data) // mxDOUBLE_CLASS - template specialization
{
	//Concurrency::samples::parallel_buffered_sort(Data.begin(), Data.end()); 
	std::sort(Data.begin(), Data.end());
}
template <> void PerformSort(std::vector<float>& Data) // mxSINGLE_CLASS
{
	//Concurrency::samples::parallel_buffered_sort(Data.begin(), Data.end()); 
	std::sort(Data.begin(), Data.end());
}
#ifndef _M_X64
template <> void PerformSort(std::vector<__int64>& Data) // mxINT64_CLASS - template specialization
{
	std::sort(Data.begin(), Data.end());
}
template <> void PerformSort(std::vector<unsigned __int64>& Data) // mxUINT64_CLASS - template specialization
{
	std::sort(Data.begin(), Data.end());
}
#endif
// std::is_integral<_DataType>::value
template <typename T> mxArray* Unique( mxClassID classid,const T* ap,  const mwSize asz, bool IsVertical)
{
	if (asz==0) { return mxCreateNumericMatrix(0,0,classid,mxREAL); }
	//std::set<T> Set(ap,ap+asz);
	//mxArray* Result = mxCreateNumericMatrix( (IsVertical) ? Set.size() : 1,(!IsVertical) ? Set.size() : 1,classid,mxREAL);	
	//if (Set.size()>0) { std::copy(Set.begin(),Set.end(),(T*)mxGetPr(Result)); }
	std::vector<T> V (ap,ap+asz);
	//std::copy(ap,ap+asz,V.begin());
	PerformSort(V);
	std::vector<T> V2; 	
	V2.reserve(V.size());
	V2.push_back(V[0]);
	for (mwSize i =1; i  <V.size(); ++i) {
		if (V[i-1]!=V[i]) { V2.push_back(V[i]); }
	}	
	mxArray* Result = mxCreateNumericMatrix( (IsVertical) ? V2.size() : 1,(!IsVertical) ? V2.size() : 1,classid,mxREAL);	
	std::copy(V2.begin(),V2.end(),(T*)mxGetPr(Result)); 
//	mxArray* Result = mxCreateNumericMatrix(0,0,classid,mxREAL); 
	return Result;
}

template <typename T> mxArray* Unique( mxClassID classid,const T* ap,  const mwSize asz, mxArray*& pm,mxArray*& pn,bool IsVertical)
{
	mxArray* Result = Unique(classid, ap, asz,IsVertical);
	mwSize CurrentSetSize = mxGetM(Result)*mxGetN(Result);
	const T* ai = (const T*)mxGetPr(Result);
	#ifdef _M_X64
		mxClassID MLOutputDataType = mxUINT64_CLASS;
		typedef unsigned __int64 cppOutputDataType;
	#else  // 32 bit compilation
		mxClassID MLOutputDataType = mxUINT32_CLASS;
		typedef  unsigned int cppOutputDataType;
	#endif
	pm = mxCreateNumericMatrix((IsVertical)? CurrentSetSize : 1,(!IsVertical) ? CurrentSetSize : 1 ,MLOutputDataType,mxREAL); 
	cppOutputDataType* ppm = (cppOutputDataType*) mxGetPr(pm);
	pn = mxCreateNumericMatrix((IsVertical)? asz : 1,(!IsVertical) ? asz : 1,MLOutputDataType,mxREAL);
	unsigned __int64* ppn = (unsigned __int64*)mxGetPr(pn);
	
	for (mwSize i = 0; i < asz; ++i) {
		const T* search = std::lower_bound(ai,ai+CurrentSetSize,ap[i]);
		ppn[i] = search-ai+1;
		if (ppm[search-ai]==0) { ppm[search-ai] = i+1; }
	}
	
	/*#ifdef _M_X64
		
		for (mwSize i = 0; i < asz; ++i) {
			const T* search = std::lower_bound(ai,ai+CurrentSetSize,ap[i]);
			ppn[i] = search-ai+1;
			if (ppm[search-ai]==0) { ppm[search-ai] = i+1; }
		}
	#else  // 32 bit compilation
		pm = mxCreateNumericMatrix(1,CurrentBufferSize,mxUINT32_CLASS,mxREAL);
		if (CurrentBufferSize!=0) {memcpy((void*)mxGetPr(pm),ais,sizeof(unsigned int)*CurrentBufferSize);}
		pn = mxCreateNumericMatrix(1,CurrentBufferSize,mxUINT32_CLASS,mxREAL);
		if (CurrentBufferSize!=0) {memcpy((void*)mxGetPr(pn),bis,sizeof(unsigned int)*CurrentBufferSize); }
	#endif*/
	return Result;
}