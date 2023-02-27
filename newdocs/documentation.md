# Documentation

In this document we will describe all use cases of the VBBinaryLensing library and provide ready-to-use examples that you can copy/paste to your code. 

## Quick start

In a typical C++ code, you will include the VBBinaryLensingLibrary.h in your project and then declare an instance to the ```VBBinaryLensing``` class in your program. The ```VBBinaryLensing``` class contains all properties and methods that the user needs for any microlensing computations. In general, you will have to declare one instance to VBBinaryLensing and work with this instance all along your code. Here is a basic start up example:

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

In this example we have declared an instance to the ```VBBinaryLensing``` class, assigned values to some parameters and then performed a computation of magnification by a binary lens with these parameters. 

In the following pages, we will describe all functionalities of VBBinaryLensing in detail.

## Single lenses

The lens equation for a single lens is

$$ u=x-\frac{1}{x}$$

For a given lens-source angular separation $u$ there are two images $x$ solving this equation. We note that all angular distances are in units of the Einstein angle $\theta_E$. 

### Point-Source-Point-Lens

If the source is point-like, the magnification is given by the famous Paczynski formula

$$ \mu = \frac{u^2+2}{u\sqrt{u^2+4}}$$

In VBBinarylensing, this formula is obtained through the function ```PSPLMag``` as follows:

```
VBBinaryLensing VBBL;
double Mag,u;

u=0.1;  // Source-lens separation in Einstein radii
Mag = VBBL.PSPLMag(u);
printf("PSPL Magnification = %lf", Mag); \\ Output should be 10.037...
```

### Extended-Source-Point-Lens

For extended sources, the magnification depends on $\rho$, the source radius normalized to the Einstein angle, and can be calculated through elliptic integrals. In order to make VBBinaryLensing as fast as possible, we provide pre-calculated tables in the file "ESPL.tbl". This file should be loaded before any calculations involving Extended-Source-Point-Lenses (ESPL).

```
VBBL.LoadESPLTable("ESPL.tbl"); // Load the pre-calculated table (you only have to do this once)

double u = 0.1; // Source-lens separation in Einstein radii
double rho = 0.01; // Source radius in units of the Einstein angle

Mag = VBBL.ESPLMag2(u, rho); // Call to the ESPLMag2 function with these parameters
printf("\nMagnification of Extended-source-point-lens = %lf\n", Mag);  // Output should be 10.050.....
```

The current range for the pre-calculated table is 1.e-4 < rho < 1.e+2. Sources smaller than the minimum are considered equal to the minimum. Sources larger than the maximum generate an error message. 

By default, VBBinaryLensing works with uniform sources. We will come to Limb Darkening later on: arbitrary Limb Darkening laws can be implemented in VBBinaryLensing.

### Astrometry

For a Point-Source, in the reference frame in which the lens is in the origin, the centroid of the images is simply

$$ \bar x = \frac{u}{u^2+2} + u$$

If you need astrometry calculations together with magnification, you have to turn it on by ```VBBL.astrometry = true``` and read the results in ```VBBL.astrox1```. This works the same for ```PSPLMag``` and ```ESPLMag2```.

```
VBBL.LoadESPLTable("ESPL.tbl"); // Load the pre-calculated table (you only have to do this once)

double u = 0.1; // Source-lens separation in Einstein radii
double rho = 0.01; // Source radius in units of the Einstein angle

VBBL.astrometry = true; // We want astrometry
Mag = VBBL.ESPLMag2(u, rho); // Call to the ESPLMag2 function with these parameters
printf("\nMagnification of Extended-source-point-lens = %lf\n", Mag);  // Output should be 10.050.....
printf("\nCentroid shift = %lf\n", VBBL.astrox1 - u);  // Output should be 0.0493.....
```

Note that ```VBBL.astrox1``` reports the centroid position with respect to the lens. The centroid position with respect to the source is ```VBBL.astrox1 - u```.

## Binary lenses

## Limb darkening

## Accuracy control

The accuracy goal of the calculation can be controlled by the user through the property ```VBBL.Tol```. In fact, ```BinaryMag2``` will refine its calculations to match the required accuracy goal. The result will be Mag +- VBBL.Tol (absolute accuracy).

Keep in mind that the computational time typically scales as ```VBBL.Tol^(-1/2)```. By default ```VBBL.Tol``` is set to 1.e-2.

Here are some examples with the same parameters as before:

```
VBBL.Tol = 1.e-3; 
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); 
printf("Magnification (accuracy at 1.e-3) = %lf\n", Mag); // Output should be 18.283....

VBBL.Tol = 1.e-4;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification (accuracy at 1.e-4) = %lf\n", Mag); // Output should be 18.2833....
```

In general, the photometric precision of ground observatories is around 0.001. Therefore, it makes sense to set a relative precision goal, instead of an asbolute accuracy goal. This is set by ```VBBL.RelTol```. The result will be Mag*(1 +- VBBL.RelTol) (relative precision).

For example, let us set a poor 10% precision, just to see the difference:

```
VBBL.RelTol = 1.e-1;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); 
printf("Magnification (relative precision at 1.e-1) = %lf\n", Mag); // Output should be 18.24.... (matching the required precision)
```

If you do not want to use relative precision, just set ```VBBL.RelTol = 0;``` which is the default value.

In general, the calculation stops when the first of the two goals is reached, either absolute accuracy or relative precision.
  
## Light curve calculation

