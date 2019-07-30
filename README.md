[![Build Status](https://travis-ci.org/valboz/VBBinaryLensing.svg?branch=master)](https://travis-ci.org/valboz/VBBinaryLensing)
[![Join the chat at https://gitter.im/VBBinaryLensing/Lobby](https://badges.gitter.im/VBBinaryLensing/Lobby.svg)](https://gitter.im/VBBinaryLensing/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

# VBBinaryLensing
`VBBinaryLensing` is a tool for forward modelling of gravitational 
microlensing events using the advanced contour integration method 
It supports single and binary lenses. 
The code has been developed by Valerio Bozza, University of Salerno.
It is written as a C++ library and wrapped as a Python package, the user
can call the code from either C++ or Python.

The root finding algorithm has been adopted from Jan Skowron & Andy Gould
(http://www.astrouw.edu.pl/~jskowron/cmplx_roots_sg/)
and translated to C++ by Tyler M. Heintz and Ava R. Hoag.
The new Python wrapper has been created by Fran Bartolić in collaboration with Etienne Bachelet and Markus Hundertmark.

## Attribution
Any use of this code for scientific publications should be acknowledged by citations to: [V. Bozza, MNRAS 408 (2010) 2188](https://academic.oup.com/mnras/article/408/4/2188/1420048). 
If specifically relevant to your work, please also cite
[J. Skowron and A. Gould, arXiv:1203.1034](https://arxiv.org/abs/1203.1034).
 

## Installation
The easiest way to install VBBinaryLensing is through `pip`
```
pip install VBBinaryLensing
```
If you want the latest development version from Github, clone this 
repository and run
```
python setup.py install
```
If you just want to use the C++ library, clone this repository, the 
library files `VBBinaryLensingLibrary.cpp` and
`VBBinaryLensing.h` are located in in `VBBinaryLensing/lib`. 
An example usage
of the C++ code is provided in `examples/cpp_examples` together with
a sample `Makefile` for compiling the lia brary.

The package also contains the following files:
- `examples/cpp_examples/instructions.cpp` - Contains working examples and specific instructions for all functions.
- `VBBinaryLensing/data/ESPL.tbl`  - Pre-calculated table for Extended-source-point-lens
- `VBBinaryLensing/data/OB151212coords.txt` - Sample file with event coordinates
- `VBBinaryLensing/data/satellite1.txt` - Sample table for satellite position (Spitzer)
- `VBBinaryLensing/data/satellite2.txt` - Sample table for satellite position (Kepler)


Currently, `VBBinaryLensing` works on Linux, MacOS and python >= 2.7. 
The python package requires `pybind11` which can be installed with
```
pip install pybind11
```
The package requires a C++ compiler supporting C++11.

## Example usage
To check the installation, try :
```python
>>>import VBBinaryLensing

# Initialize the VBBinaryLensing object which contains all functions 
>>>VBBL = VBBinaryLensing.VBBinaryLensing()

>>>s = 1.
>>>q = 0.02
>>>y1 = 0.5 
>>>y2 = 0.5 
>>>rho = 0.0033

# Calculate magnification for a single point in the source plane
>>>magnification = VBBL.BinaryMag2(s, q, y1, y2, rho)
>>>print(magnification)
>>>1.6310924403681109
```

Example Jupyter notebooks are included in `examples/python_examples`.

## Documentation
We are still working on getting the documentation working online. 
For now, the vast majority of functions are documented with Python
docstrings which can be accessed as, for example, `?VBBL.BinaryMag2()` in
a Jupyter notebook.

## License
VBBinaryLensing is freely available to the community under the 
GNU Lesser General Public License Version 3 included in this repository.
