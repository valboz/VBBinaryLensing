[Back to **Single lenses**](SingleLenses.md)


# Binary lenses

The binary lens equation reads

$$ \vec{y} = \vec{x} - m_A \frac{\vec{x}- \vec{x}_A}{|\vec{x}- \vec{x}_A|^2} - m_B \frac{\vec{x}- \vec{x}_B}{|\vec{x}- \vec{x}_B|^2}$$

Here $\vec{y}\equiv (y_1,y_2)$ is the source position, $\vec{x}\equiv (x_1,x_2)$ is the image position, $\vec{x}_A$ and $\vec{x}_B$ are the positions of the two lenses, $m_A$ and $m_B$ are the mass fractions of the two lenses. All angular coordinates are in units of the total Einstein radius, defined in terms of the total mass of the system.

The convention we use in VBBinaryLensing is that the origin is placed in the barycenter of the system and that the two lenses are along the $x_1$ axis. Introducing the mass ratio $q\equiv m_B/m_A$, we have that all quantities are expressed in terms of two parameters: **the mass ratio $q$ and the separation between the two lenses $s$**:

$$ m_A= \frac{1}{1+q}$$

$$ m_B= \frac{q}{1+q}$$

$$ \vec{x}_A= \left( -\frac{q s}{1+q}, 0 \right)$$

$$ \vec{x}_B= \left( \frac{s}{1+q}, 0 \right)$$

## Binary lensing with point sources

For point sources, we can get the magnification with the `BinaryMag0` function. This depends on the separation $s$, the mass ratio $q$ and the source position $y_1$, $y_2$. Here is an example:

```
VBBinaryLensing VBBL;
double Mag, s, q, y1, y2;

s = 0.8; //separation between the two lenses
q = 0.1; // mass ratio
y1 = 0.01; // y1 is the source coordinate along the axis parallel to the line joining the two lenses 
y2 = 0.01; // y2 is the source coordinate orthogonal to the first one

Mag = VBBL.BinaryMag0(s, q, y1, y2); // Call to the BinaryMag0 function with these parameters
printf("Magnification of a point-source = %lf\n", Mag);  // Output should be 18.18.....
```

The resolution of the lens equation is obtained by recasting the lens equation as a fifth order complex polynomial, whose roots are found by the [Skowron & Gould algorithm](http://www.astrouw.edu.pl/~jskowron/cmplx_roots_sg/), as discussed in the introduction.

## Binary lensing with extended sources

For extended sources, our recommended general purpose function is `BinaryMag2`, as shown in the quick start section. This function also depends on $\rho$, the source radius in units of the total Einstein angle:

```
VBBinaryLensing VBBL;

double Mag, s, q, y1, y2,rho;

s = 0.8; //separation between the two lenses
q = 0.1; // mass ratio
y1 = 0.01; // y1 is the source coordinate along the axis parallel to the line joining the two lenses 
y2 = 0.01; // y2 is the source coordinate orthogonal to the first one
rho = 0.01; // Source radius in Einstein radii

Mag = VBBL.BinaryMag2(s, q, y1, y2,rho); // Call to the BinaryMag2 function with these parameters
printf("Binary lens Magnification = %lf\n", Mag); // Output should be 18.28....
```

By default the `BinaryMag2` function works with uniform-brightness sources. Any possible Limb Darkening laws can be implemented in VBBinaryLensing, as shown in the [next section](LimbDarkening.md) of the documentation.

The `BinaryMag2` function has a quite complicated flow that optimizes the calculation according to several tests. Users interested to discover more about its internal structure are invited to read until the end of this documentation.

## Astrometry

Astrometry in binary lensing is obtained in the same way as for single lenses. We repeat the steps here outlining the differences.

If you need astrometry calculations together with magnification, you have to turn astrometry on by ```VBBL.astrometry = true``` and read the results in ```VBBL.astrox1``` and ```VBBL.astrox2```. This works in the same way for ```BinaryMag0``` and ```BinaryMag2```.

```
VBBinaryLensing VBBL;

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

We note that ```VBBL.astrox1``` and ```VBBL.astrox2``` express the centroid position in the **frame centered in the barycenter of the lenses**. In order to obtain the **centroid with respect to the source position**, we just have to subtract `y1` and `y2` respectively.

[Go to **Critical curves and caustics**](CriticalCurvesAndCaustics.md)
