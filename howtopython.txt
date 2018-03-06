Some advice how to use VBB fom python (M. Hundertmark 28 June, including suggestions from Wei Zhu 13 July please also have a look on Wei's makefile)

In order to bind the VBBinaryLensingLibrary efficiently together with python, which is useful for combining it with high-level optimizing and resampling tools such as scipy.optimize or emcee, one can install and use swig to compile a directly callable module. For that purpose, one can define the methods (functions) of VBBinaryLensingLibrary in a swig configuration file which should be called VBBinaryLensingLibrary.i. As a minimal example, it could contain the call to BinaryMag but if required all other methods can be included, too. An example should look like:

%module VBBinaryLensingLibrary
%include "carrays.i"
%array_class(double,doubleArray);
%{
#include "VBBinaryLensingLibrary.h"
%}
%include "VBBinaryLensingLibrary.h"

The wrapper swig can be called via:

swig -c++ -python VBBinaryLensingLibrary.i

Now we can compile all corresponding codes:

g++ --fast-math -fPIC -O3 -lm -c VBBinaryLensingLibrary.cpp

#Optional: if you are using anaconda, replace Python.h via sed
#sed -i 's/Python.h/\/home\/youruser\/anaconda2\/include\/python2.7\/Python.h/g' 
Now we can compile the wrapped version
g++ --fast-math -O3 -fPIC -lm -c VBBinaryLensingLibrary_wrap.cxx

Finally we create a shared object and the python module:

g++ --fast-math -O3 -fPIC -shared VBBinaryLensingLibrary.o VBBinaryLensingLibrary_wrap.o -o _VBBinaryLensingLibrary.so

Copying *.* to your site-packages makes it globally callable.

As a quick test:

import VBBinaryLensingLibrary

c=VBBinaryLensingLibrary.VBBinaryLensing()
#NB: in order to achieve consistent numerical results, please cast all parameters to double, i.e. using "float()" in python.

c.BinaryMag(float(1),float(0.02),float(0.5),float(0.5),float(0.0033),float(0.001))
#1.631172486811772

print c.B
pr=VBBinaryLensingLibrary.doubleArray(9)
pr[0]=float(log(float(1.)))
pr[1]=float(log(float(0.02)))
pr[2]=float(0.09)
pr[3]=float(0.5)
pr[4]=float(log(float(0.0033)))
pr[5]=float(log(float(30.)))
pr[6]=float(7550.4.)
pr[7]=float(0.15)
pr[8]=float(0.25)
c.Tol=0.001
c.SetObjectCoordinates('OB131125coords.txt','.',float(2013))

