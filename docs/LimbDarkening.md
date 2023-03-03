[Back to **Critical curves and caustics**](CriticalCurvesAndCaustics.md)

# Limb darkening

Real stars are not uniform disks. The intensity declines from the center to the edge of the source, as described by limb darkening laws. VBBinaryLensing has several built-in limb darkening laws and allows the user to specify an arbitrary law.

## Linear limb darkening

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

If you want to go back to linear limb darkening,  you may use ```VBBL.SetLDprofile(VBBL.LDlinear);```

## Square root limb darkening

$$I(\nu) = I(0) \left[1 - a1 (1 - \nu)- a2 (1-\sqrt{\nu}) \right]$$

This law has two parameters that are given through `VBBL.a1` and `VBBL.a2`:

```
VBBL.SetLDprofile(VBBL.LDsquareroot); 
VBBL.a1 = 0.51;
VBBL.a2 = 0.3;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification with square root limb darkened source = %lf\n", Mag);  // Output should be 18.2712.....
```

## Quadratic limb darkening

$$I(\nu) = I(0) \left[1 - a1 (1 - \nu)- a2 (1-\nu)^2 \right]$$

```
VBBL.SetLDprofile(VBBL.LDquadratic); 
VBBL.a1 = 0.51;
VBBL.a2 = 0.3;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification with quadratic limb darkened source = %lf\n", Mag);  // Output should be 18.2709.....
```

## Logarithmic limb darkening

$$I(\nu) = I(0) \left[ 1 - a1 (1 - \nu)- a2 ~ \nu \ln{\nu} \right]$$

```
VBBL.SetLDprofile(VBBL.LDlog); 
VBBL.a1 = 0.51;
VBBL.a2 = 0.3;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification with logarithmic limb darkened source = %lf\n", Mag);  // Output should be 18.2779.....
```

## User-defined limb darkening

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

[Go to: **Accuracy control**](AccuracyControl.md)
