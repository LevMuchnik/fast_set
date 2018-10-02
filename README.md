# MatLab FastSet package
This package provides functions that perform fast set operations on matlab arrays. Depending on the circumstances, computation times can be reduced by orders of magnitude comparing to the built-in MatLab methods. 
The functions are implemented in C++ and parallelized. 
## Getting Started
Windows mex files are provided in the FastSet folder of this repository. To get started, download them to your local machine and add the folder to MatLab path. 
These methods mimic origila Matlab set routines so that, for instance, *intercect* is mapped onto *fast_intersect_sorted*. 
The two sets of functions are nearly perfectly interchangable. 
Note that:
* fast_set functions **assume that they receive sets** (i.e. the received vectors are sorted and unique). 
Use MatLab unique or fast_unique to sort arrays. 
* fast_set methods **preserve types**. They leverage type information (e.g. int16, int32, int64, uint* and float) to run faster and consume less RAM. 


### Prerequisites
I used MS Visual Studio to build the code. The package is implemented as pure C++ and can be built on MacOS or Linux with any standard compiler. 
It does depend on the MatLab mex library. Set path to MatLab install folder in MexFiles/FastSet/Utilities/MatLabDefs.h 

