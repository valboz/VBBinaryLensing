[Back to **Light Curve Functions**](LightCurves.md)

# Parallax

In the basic light curve functions discussed in the [Light Curve Functions](LightCurves.md) section, we assumed that observer, lens and source move rectilineraly. Therefore, the relative lens-source angular motion is rectilinear and described by the two parameters $u_0$ and $\alpha$.

In reality, the observer motion is not rectilinear as the Earth orbits the Sun. For satellite observations, the situation is similar, since all spacecraft will described curved orbits. In this section we will introduce a set of functions similar to the "static" ones discussed before, but including the observer motion.

First we will treat geocentric observations and then we will move to observations from space.

## Target coordinates

We need to specify J2000.0 equatorial coordinates for our microlensing target. This can be done by preparing a text file containing R.A. and Dec., similar to the following example:

```
17:57:05 -30:22:59
```

Then we inform VBBinaryLensing of these coordinates by the function `SetObjectCoordinates`

```
VBBinaryLensing VBBL;

VBBL.SetObjectCoordinates("OB151212coords.txt",".");
```

The first argument is the name of the file we have just prepared (these are the coordinates of the event [OGLE-2015-BLG-1212](https://ui.adsabs.harvard.edu/abs/2016ApJ...820...79B/abstract)). The second argument will only be used in case of observations from space (see below).

## Parallax system

Then we should decide in which coordinates we want to express the parallax vector $\vec \pi_E$. In the literature, there are two popular choices: North-East system $(\pi_{E_,N},\pi_{E,E})$ and parallel/orthogonal to the Earth acceleration direction $(\pi_{E,\parallel},\pi_{E,\perp})$. In VBBinaryLensing you have both possibilities by setting `VBBL.parallaxsystem` to 1 or 0 respectively. The default value is 0, corresponding to the parallel/orthogonal system.

## Reference time for parallax $t_{0,par}$

Finally, we have to decide the reference time for the parallax effect $t_{0,par}$. Whatever the values of the parallax components, the source position at $t=t_{0,par}$ remains fixed. By default, VBBinaryLensing uses $t_{0,par}=t_0$, so that the light curve is unchanged at the time of closest approach to the center of mass of the lens. However, if you want to keep the source position at another time fixed, you can set `VBBL.t0_par_fixed = 1;` and choose your reference time via `VBBL.t0_par`.

## Light curve functions with parallax

All light curve functions defined in the [Light Curves](LightCurves.md) section have their corresponding counterpart including the parallax effect:

```
PSPLLightCurveParallax
ESPLLightCurveParallax
BinaryLightCurveParallax
```

The only difference is that the array of parameters must include two more entries for the components of the parallax vector. Here is a full example demonstrating the use of `BinaryLightCurveParallax`:

```
VBBinaryLensing VBBL; // Declare instance to VBBinaryLensing

double pr[9]; // Array of parameters
double s, q, u0, alpha, rho, tE, t0, paiN, paiE, t;

VBBL.SetObjectCoordinates("OB151212coords.txt", ".");  // Read target coordinates in file
VBBL.parallaxsystem = 1; // Here we use North-East components for parallax

u0 = -0.01; // Impact parameter
t0 = 7550.4; // Time of closest approach to the center of mass
tE = 100.3; // Einstein time
rho = 0.01; // Source radius
s = 0.8; // Separation between the two lenses
q = 0.1; // Mass ratio
alpha = 0.53; // Angle between a vector pointing to the left and the source velocity
paiN = 0.3; // Parallax component in the North direction
paiE = 0.13; // Parallax component in the East direction

// Let us put all parameters in our array
pr[0] = log(s);
pr[1] = log(q);
pr[2] = u0;
pr[3] = alpha;
pr[4] = log(rho);
pr[5] = log(tE);
pr[6] = t0;
pr[7] = paiN;
pr[8] = paiE;

t = 7551.6; // Time at which we want to calculate the magnification

Mag = VBBL.BinaryLightCurveParallax(pr, t); // Calculates the Binary Lens magnification at time t with parameters in pr
printf("Binary Light Curve with Parallax at time t: %lf", Mag); // Output should be 31.01...

```

In this example we have not set `VBBL.t0_par`, which means that $t_{0,par}=t_0$ here.

Finally, we add that all light curve functions are available in two versions as explained in [Light Curves](LightCurves.md): the version performing a single calculation of the magnification at time t (as in the example above) and the version calculating the full light curve with one single call (see [Light Curves](LightCurves.md) for details).

[Go to **Orbital motion**](OrbitalMotion.md)
