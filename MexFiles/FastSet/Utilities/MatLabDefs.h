/*
	To create a mex-File
	1. Create empty C++ DLL. (If dllmain.cpp is created, remove it from the project and the disk (mex does not need WinMain)
	2. Change Project Properties (for both Debug & Release configurations)
		a. "Project->Properties->Linker->General->Output File" Change output file extention  to .mexw64 for x64 or .mexw32 for 32 bit DLLs
		b. "Project->Properties->Linker->General->Command Line": /def:".\mexFunction.def"
		c. Create and place the def file "mexFunction.def" in the project folder. Notice that the first line must contain the name of the desired DLL.
	3. Include this file: 
		a. Put #include "..\Utilities\MatLabDefs.h" at the top of each of your CPP files
		b. Make sure, all paths in MatLabDefs.h are OK
	4. Implement mexFunction in your main CPP file:
		void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {}

*/
#pragma once

#ifdef _M_X64
#define MATLAB_PATH "c:/Program Files/MATLAB/R2018b/"
#define MATLAB_INCLUDE_MEX_H <c:\\Program Files\\MATLAB\\R2018b\\extern\\include\\mex.h>
#define MATLAB_INCLUDE_TMWTYPES_H <c:\\Program Files\\MATLAB\\R2018b\\extern\\include\\tmwtypes.h>
#else
#define MATLAB_PATH "c:/Program Files (x86)/MATLAB/R2018b/"
#define MATLAB_INCLUDE_MEX_H <c:\\Program Files (x86)\\MATLAB\\R2018b\\extern\\include\\mex.h>
#define MATLAB_INCLUDE_TMWTYPES_H <c:\\Program Files (x86)\\MATLAB\\R2018b\\extern\\include\\tmwtypes.h>

#endif
#pragma include_alias( <mex.h>,MATLAB_INCLUDE_MEX_H)
#pragma include_alias( <tmwtypes.h>,MATLAB_INCLUDE_TMWTYPES_H)
#include <mex.h>

#ifdef _M_X64
	#pragma comment(lib,MATLAB_PATH "extern/lib/win64/microsoft/libeng.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win64/microsoft/libmat.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win64/microsoft/libmex.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win64/microsoft/libmwblas.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win64/microsoft/libmwlapack.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win64/microsoft/libmwmathutil.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win64/microsoft/libmx.lib")
#else // _M_X64
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libeng.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libfixedpoint.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libmat.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libmex.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libmwservices.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libmx.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libut.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/mclcommain.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/mclmcr.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/mclmcrrt.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/mclxlmain.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libeng.lib")
	#pragma comment(lib,MATLAB_PATH "extern/lib/win32/microsoft/libeng.lib")
#endif // _M_X64

#define _CRT_SECURE_DEPRECATE_MEMORY
#define _SCL_SECURE_NO_WARNINGS