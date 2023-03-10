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







[Go to **Orbital motion**](OrbitalMotion.md)
