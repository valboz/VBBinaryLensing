
# Documentation

**Warning: This documentation file is still provisional. We hope to conclude it by mid-March 2023.**

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

For extended sources, the magnification depends on $\rho$, the **source radius** normalized to the Einstein angle, and can be calculated through elliptic integrals. In order to make VBBinaryLensing as fast as possible, we provide **pre-calculated tables** in the file "ESPL.tbl". This file should be loaded before any calculations involving Extended-Source-Point-Lenses (ESPL).

```
VBBL.LoadESPLTable("ESPL.tbl"); // Load the pre-calculated table (you only have to do this once)

double u = 0.1; // Source-lens separation in Einstein radii
double rho = 0.01; // Source radius in units of the Einstein angle

Mag = VBBL.ESPLMag2(u, rho); // Call to the ESPLMag2 function with these parameters
printf("\nMagnification of Extended-source-point-lens = %lf\n", Mag);  // Output should be 10.050.....
```

The current range for the pre-calculated table is 1.e-4 < rho < 1.e+2. Sources smaller than the minimum are considered equal to the minimum. Sources larger than the maximum generate an error message. 

By default, VBBinaryLensing works with **uniform sources**. We will come to **Limb Darkening** [later on](https://github.com/valboz/VBBinaryLensing/blob/master/docs/documentation.md#limb-darkening): arbitrary Limb Darkening laws can be implemented in VBBinaryLensing.

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

The binary lens equation reads

$$ \vec{y} = \vec{x} - m_1 \frac{\vec{x}- \vec{x}_1}{|\vec{x}- \vec{x}_1|^2} - m_2 \frac{\vec{x}- \vec{x}_2}{|\vec{x}- \vec{x}_2|^2}$$

Here $\vec{y}\equiv (y_1,y_2)$ is the source position, $\vec{x}\equiv (x_1,x_2)$ is the image position, $\vec{x}_1$ and $\vec{x}_2$ are the positions of the two lenses, $m_1$ and $m_2$ are the mass fractions of the two lenses. All angular coordinates are in units of the total Einstein radius, defined in terms of the total mass of the system.

The convention we use in VBBinaryLensing is that the origin is placed in the barycenter of the system and that the two lenses are along the $x_1$ axis. Introducing the mass ratio $q\equiv m_2/m_1$, we have that all quantities are expressed in terms of two parameters: **the mass ratio $q$ and the separation between the two lenses $s$**:

$$ m_1= \frac{1}{1+q}$$

$$ m_2= \frac{q}{1+q}$$

$$ \vec{x}_1= \left( -\frac{q s}{1+q}, 0 \right)$$

$$ \vec{x}_2= \left( \frac{s}{1+q}, 0 \right)$$

### Binary lensing with point sources

For point sources, we can get the magnification with the `BinaryMag0` function. This depends on the separation $s$, the mass ratio $q$ and the source position $y_1$, $y_2$. Here is an example:

```
double Mag, s, q, y1, y2;
s = 0.8; //separation between the two lenses
q = 0.1; // mass ratio
y1 = 0.01; // y1 is the source coordinate along the axis parallel to the line joining the two lenses 
y2 = 0.01; // y2 is the source coordinate orthogonal to the first one

Mag = VBBL.BinaryMag0(s, q, y1, y2); // Call to the BinaryMag0 function with these parameters
printf("Magnification of a point-source = %lf\n", Mag);  // Output should be 18.18.....
```

### Binary lensing with extended sources

For extended sources, the correct function is `BinaryMag2`, as shown in the quick start section. This also depends on the source radius $\rho$:

```
double Mag, s, q, y1, y2,rho;
s = 0.8; //separation between the two lenses
q = 0.1; // mass ratio
y1 = 0.01; // y1 is the source coordinate along the axis parallel to the line joining the two lenses 
y2 = 0.01; // y2 is the source coordinate orthogonal to the first one
rho = 0.01; // Source radius in Einstein radii

Mag = VBBL.BinaryMag2(s, q, y1, y2,rho); // Call to the BinaryMag2 function with these parameters
printf("Binary lens Magnification = %lf\n", Mag); // Output should be 18.28....
```

The `BinaryMag2` function has a quite complicated flow that optimizes the calculation according to several tests. Users interested to discover more about its internal structure are invited to read until the end of this document.

### Astrometry

Astrometry in binary lensing is obtained in the same way as for single lenses. We repeat the steps here outlining the differences.

If you need astrometry calculations together with magnification, you have to turn it on by ```VBBL.astrometry = true``` and read the results in ```VBBL.astrox1``` and ```VBBL.astrox2```. This works in the same way for ```BinaryMag0``` and ```BinaryMag2```.

```
double Mag, s, q, y1, y2,rho;
s = 0.8; //separation between the two lenses
q = 0.1; // mass ratio
y1 = 0.01; // y1 is the source coordinate along the axis parallel to the line joining the two lenses 
y2 = 0.01; // y2 is the source coordinate orthogonal to the first one
rho = 0.01; // Source radius in Einstein radii

VBBL.astrometry = true; // We want astrometry
Mag = VBBL.BinaryMag2(s, q, y1, y2,rho); // Call to the BinaryMag2 function with these parameters
printf("Binary lens Magnification = %lf\n", Mag); // Output should be 18.28....
printf("\nCentroid shift = (%lf,%lf)\n", VBBL.astrox1 - y1, VBBL.astrox2 - y2);  // Output should be (-0.164...,-0.074...)
```

As before, we note that ```VBBL.astrox1``` and ```VBBL.astrox2``` express the centroid position in the frame centered in the barycenter of the lenses. In order to obtain the centroid with respect to the source position, we just have to subtract `y1` and `y2` respectively.


## Limb darkening

Real stars are not uniform disks. The intensity declines from the center to the edge of the source, as described by limb darkening laws. VBBinaryLensing has several built-in limb darkening laws and allows the user to specify an arbitrary law.

The default limb darkening profile is linear, according to

$$ I(\nu) = I(0) \left[1 - a1 (1 - \nu)\right] $$

with $\nu=\sqrt{1-r^2/\rho^2}$.

The coefficient `VBBL.a1` specifies the linear limb darkening coefficient. We note that there are other popular expressions for linear limb darkening that can be reduced to the one adopted in VBBinaryLensing through simple transformations (e.g. for $\Gamma_1$ see [An et al. ApJ 572:521 (2002)](https://ui.adsabs.harvard.edu/abs/2002ApJ...572..521A/abstract), Eq. (11)).

In order to use linear limb darkening in all calculations with extended sources in VBBinaryLensing, it is sufficient to give a non-vanishing value to `VBBL.a1`:

```
VBBL.a1 = 0.51; // Linear limb darkening coefficient. 
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); // Call to the BinaryMag2
printf("Magnification with limb darkened source = %lf\n", Mag);  // Output should be 18.27.....
```

In order to go back to uniform sources, just set `VBBL.a1 = 0`. In general, a calculation with limb darkening is slower than a calculation with a uniform source, because it is repeated on several concentric annuli.

There are three more limb darkening laws that are already available in VBBinaryLensing. You may switch from one to another using the function `VBBL.SetLDprofile`.

**Square root limb darkening**

$$I(\nu) = I(0) \left[1 - a1 (1 - \nu)- a2 (1-\sqrt{\nu}) \right]$$

This law has two parameters that are given through `VBBL.a1` and `VBBL.a2`:

```
VBBL.SetLDprofile(VBBL.LDsquareroot); 
VBBL.a1 = 0.51;
VBBL.a2 = 0.3;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification with square root limb darkened source = %lf\n", Mag);  // Output should be 18.2712.....
```

**Quadratic limb darkening**

$$I(\nu) = I(0) \left[1 - a1 (1 - \nu)- a2 (1-\nu)^2 \right]$$

```
VBBL.SetLDprofile(VBBL.LDquadratic); 
VBBL.a1 = 0.51;
VBBL.a2 = 0.3;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification with quadratic limb darkened source = %lf\n", Mag);  // Output should be 18.2709.....
```

**Logarithmic limb darkening**

$$I(\nu) = I(0) \left[ 1 - a1 (1 - \nu)- a2 \nu \ln{\nu} \right]$$

```
VBBL.SetLDprofile(VBBL.LDlog); 
VBBL.a1 = 0.51;
VBBL.a2 = 0.3;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification with logarithmic limb darkened source = %lf\n", Mag);  // Output should be 18.2779.....
```

To go back to linear limb darkening,  you may use ```VBBL.SetLDprofile(VBBL.LDlinear);```

**User-defined limb darkening**

Suppose you have your favorite limb darkening law. Then you should define a function with the syntax `double MyLDprofile(double r);`

If there are any parameters, they must be defined as external variables accessible in the scope in which you use your profile. For example, you may define them as global variables. Here is an example of a valid limb darkening function:

```
double MyLDprofile(double r) {
	double costh;
	costh = sqrt(1 - r * r);
	return (1 - u1 * (1 - costh) - u2 * (1 - sqrt(costh))); // square root
}
```

This is just a square root limb darkening law depending on two parameters `u1` and `u2`, which must be defined as global.

At this point, in order to adopt this user-defined function as the current limb darkening law, you must still use the ```VBBL.SetLDprofile``` function as follows:

```
u1 = 0.51;
u2 = 0.3;
VBBL.SetLDprofile(&MyLDprofile, 1000); // The limb darkening law is pre-calculated on a grid of 1000 points.
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification with user-defined LD profile = %lf\n", Mag);  // Output should be 18.2712.....
```

```VBBL.SetLDprofile``` with two parameters requires the location of the function as the first parameter and the number of points in the grid as the second parameter. The limb darkening law is then pre-calculated on this grid in order to perform all subsequent extended source calculations.

**Warning**: the user-defined limb darkening is not available in the Python version of VBBinaryLensing.

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
  
	// After each calculation, the number of annuli used is available in VBBL.nannuli.
	// If you are probing extremely tiny caustics with very large sources, you may impose a minimum number of annuli.
	// Before your calculation, just set
	// VBBL.minannuli=2; //or whatever you need 
	// The total number of points used is available in VBBL.NPS
	printf("Annuli used: %d\nTotal number of points: %d\n", VBBL.nannuli, VBBL.NPS);
  
  
## Light curve calculation

