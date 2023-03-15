[Back to **Parallax**](Parallax.md)

# Orbital motion

Binary lenses orbit around the common center of mass. If the microlensing event is long enough, we cannot neglect this effect. However, if the effect is small, most orbital parameters remain unconstrained. Rather than adding too many dimensions to our parameter space, it can be sufficient to restric to circular orbits to describe the subtle deviations in our microlensing event.

VBBinaryLensing offers two functions:

```
BinaryLightCurveOrbital
BinaryLightCurveKepler
```

The first function describes circular orbital motion, while the second considers elliptic Keplerian orbital motion. Note that we deprecate the "linear approximation", which is popular in many microlensing papers, since it does not correspond to any physical trajectories and may lead to unphysical solutions.

Both functions discussed here include the parallax calculation. Therefore, a preliminary call to `VBBL.SetObjectCoordinates` is mandatory (see [Parallax](Parallax.md)). If you want to fit orbital motion without parallax, you must set the two components of the parallax to zero.

Finally, the reference time for orbital motion calculation is by default $t_0$, the time of closest approach of the source to the center of mass. If you want to specify a different time, you should to it through $t_{0,par}$ (see [Parallax](Parallax.md#reference-time-for-parallax-t_0par))

## Circular orbital motion

[Go to **Binary Sources**](BinarySources.md)
