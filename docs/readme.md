
# Documentation

**Warning: This documentation is still provisional. We hope to conclude it by mid-March 2023.**

In this document we will describe all use cases of the VBBinaryLensing library and provide ready-to-use examples that you can copy/paste to your code. 

## Quick start

In a typical C++ code, you will include the VBBinaryLensingLibrary.h in your project. 

An instance to the ```VBBinaryLensing``` class should be declared in your program. The ```VBBinaryLensing``` class contains all the properties and methods that the user needs to call for any microlensing computations. Here is a basic start up example:

```
#include <stdio.h>
#include "VBBinaryLensingLibrary.h"

int main()
{
  // Declaration of an instance to VBBinaryLensing class.
  VBBinaryLensing VBBL;
  
  double Mag, s, q, y1, y2, Rs;
  s = 0.8; //separation between the two lenses
  q = 0.1; // mass ratio: mass of the lens on the right divided by mass of the lens on the left
  
  // Position of the center of the source with respect to the center of mass.
  y1 = 0.01; // y1 is the source coordinate along the axis parallel to the line joining the two lenses 
  y2 = 0.01; // y2 is the source coordinate orthogonal to the first one
  Rs = 0.01; // Source radius in Einstein radii of the total mass.
  
  Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); // Call to the BinaryMag2 function with these parameters
  printf("Binary lens Magnification = %lf\n", Mag); // Output should be 18.28....
  
  return 0;
}
```

In this example we have declared an instance to the ```VBBinaryLensing``` class, assigned values to some parameters and then we have called ```VBBL.BinaryMag2``to perform a computation of magnification by a binary lens with these parameters. 

## Summary

In the following pages, we will describe all functionalities of VBBinaryLensing in detail.

[Single lenses](SingleLenses.md)

[Binary lenses](BinaryLenses.md)

[Limb Darkening](SingleLenses.md)

[Accuracy Control](SingleLenses.md)

[Light Curve Functions](LightCurves.md)

[Parallax](Parallax.md)

[Orbital Motion](OrbitalMotion.md)

[Binary Sources](BinarySources.md)

[Advanced Control](AdvancedControl.md)
