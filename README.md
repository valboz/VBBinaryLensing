[![Build Status](https://travis-ci.org/valboz/VBBinaryLensing.svg?branch=python_implementation)](https://travis-ci.org/valboz/VBBinaryLensing)
[![Join the chat at https://gitter.im/VBBinaryLensing/Lobby](https://badges.gitter.im/VBBinaryLensing/Lobby.svg)](https://gitter.im/VBBinaryLensing/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)



# VBBinaryLensing
Microlensing light curve calculation using the advanced contour integration method

- This code has been developed by Valerio Bozza, University of Salerno.
- The root finding algorithm has been adopted from Jan Skowron & Andy Gould
(http://www.astrouw.edu.pl/~jskowron/cmplx_roots_sg/)
and translated to C++ by Tyler M. Heintz and Ava R. Hoag.
- The new Python wrapper has been created by Fran Bartolic in collaboration with Etienne Bachelet and Markus Hundertmark.
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
- `LICENSE.txt` // GNU LESSER GENERAL PUBLIC LICENSE Version 3

!!! Please follow `instructions.cpp` to learn how to use all functions !!!

# License
VBBinaryLensing is provided under the GNU Lesser General Public License Version 3

# Python wrapper
Currently supported is Linux, MacOs and python >= 2.7. 
In order to construct the python wrapper, please install pybind11 :

pip install pybind11

Then clone the repository. Finally, install :

python setup.py install

To check the installation, try :

```python
>>>import VBBinaryLensing

>>>VBBL = VBBinaryLensing.VBBinaryLensing()

>>>s = 1.
>>>q = 0.02
>>>y1 = 0.5 
>>>y2 = 0.5 
>>>rho = 0.0033


>>>magnification = VBBL.BinaryMag2(s, q, y1, y2, rho)
>>>print(magnification)
>>>1.6310924403681109
```
