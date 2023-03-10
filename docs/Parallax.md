[Back to **Light Curve Functions**](LightCurves.md)

# Parallax

In the basic light curve functions discussed in the [Light Curve Functions](LightCurves.md) section, we assumed that observer, lens and source move rectilineraly. Therefore, the relative lens-source angular motion is rectilinear and described by the two parameters $u_0$ and $\alpha$.

In reality, the observer motion is not rectilinear as the Earth orbits the Sun. For satellite observations, the situation is similar, since all spacecraft will described curved orbits. In this section we will introduce a set of functions similar to the "static" ones discussed before, but including the observer motion.

First we will treat geocentric observations and then we will move to observations from space.

## Coordinate systems

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





[Go to **Orbital motion**](OrbitalMotion.md)
