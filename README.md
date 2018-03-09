Fork of VBBinaryLensing code for calculating microlensing lightcurves,
developed by Valerio Bozza. The code is freely available for download at http://www.fisica.unisa.it/gravitationAstrophysics/VBBinaryLensing.htm. 

# VBBinaryLensing v2.0.1 (released 2018-02-05)
- This code has been developed by Valerio Bozza, University of Salerno.
- The root finding algorithm has been adopted from Jan Skowron & Andy Gould
(http://www.astrouw.edu.pl/~jskowron/cmplx_roots_sg/)
and translated to C++ by Tyler M. Heintz and Ava R. Hoag.
- Any use of this code for scientific publications should be acknowledged by citations to: 
V. Bozza, MNRAS 408 (2010) 2188.
If specifically relevant to your work, please also cite
J. Skowron and A. Gould, arXiv:1203.1034
- The code is freely available to the community under the 
GNU LESSER GENERAL PUBLIC LICENSE Version 3
included in this package.

The package contains the following files:
- `instructions.cpp` // Contains working examples and specific instructions for all functions.
- `VBBinaryLensingLibrary.h` // Header for the library
- `VBBinaryLensingLibrary.cpp` // Source code for the library
- `ESPL.tbl` // Pre-calculated table for Extended-source-point-lens
- `Makefile` // A sample makefile for compiling the library
- `OB151212coords.txt` // Sample file with event coordinates
- `satellite1.txt` // Sample table for satellite position (Spitzer)
- `satellite2.txt` // Sample table for satellite position (Kepler)
- `howtopython.txt` // Instructions for linking VBBinaryLensing in Python (kindly provided by Markus Hundertmark)
- `VBBinaryLensingLibrary.i` // Sample swig configuration file for Python
- `LICENSE.txt` // GNU LESSER GENERAL PUBLIC LICENSE Version 3

!!! Please follow `instructions.cpp` to learn how to use all functions !!!
