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

Finally, the reference time for orbital motion calculation is by default $t_{0,orb}=t_0$, i.e. the time of closest approach of the source to the center of mass. If you want to specify a different time, you can do it through $t_{0,par}$ (see [Parallax](Parallax.md#reference-time-for-parallax-t_0par)). There is no possibility to set two different reference times $t_{0,orb} \neq t_{0,par}$.

## Circular orbital motion

Here is an example of use of `BinaryLightCurveOrbital`:

```
VBBinaryLensing VBBL; // Declare instance to VBBinaryLensing

double pr[9]; // Array of parameters
double s, q, u0, alpha, rho, tE, t0, paiN, paiE, g1, g2, g3, t;

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

g1 = 0.001; // Orbital component gamma1
g2 = -0.002; // Orbital component gamma2
g3 = 0.0011; // Orbital component gamma3

pr[0] = log(s);
pr[1] = log(q);
pr[2] = u0;
pr[3] = alpha;
pr[4] = log(rho);
pr[5] = log(tE);
pr[6] = t0;
pr[7] = paiN;
pr[8] = paiE;
pr[9] = g1;
pr[10] = g2;
pr[11] = g3;

t = 7551.6; // Time at which we want to calculate the magnification

Mag = VBBL.BinaryLightCurveOrbital(pr, t); // Calculates the Binary Lens magnification at time t with parameters in pr
printf("Binary Light Curve with Parallax at time t: %lf", Mag); // Output should be 30.92...
```

A circular orbital motion is completely specified by the three components of the angular velocity $\vec \gamma$ of the secondary mass with respect to the first mass. We have

$\gamma_1 \equiv \frac{1}{s} \frac{ds}{dt}$, this is the component along the lens axis;

$\gamma_2 \equiv \frac{d\alpha}{dt}$, this is the component orthogonal to the lens axis;

$\gamma_3 \equiv \frac{1}{s}\frac{ds_z}{dt}$, this is the component along the line of sight.

All values are specified at time $t_{0,orb}=t_{0,par}$. The units are $day^{-1}$.

For more details, you might see the appendix of [Skowron et al. (2011)](https://ui.adsabs.harvard.edu/abs/2011ApJ...738...87S/abstract). In general, the component $\gamma_3$ is poorly constrained by the data, but it is important to stress that setting $\gamma_3=0$ is NOT equivalent to the linear approximation. Since microlensing is only sensitive to the projected distance, orbits with $\gamma_3 \rightarrow - \gamma_3$ are indistinguishable.

Conventional orbital elements can be easily recovered from the component of $\vec \gamma$. In particular, we have

$$\omega= \frac{2\pi}{T} = \frac{\gamma_3}{\sqrt{\gamma_1^2 + \gamma_3^2}}  |\vec \gamma |$$

$$ \cos i = \frac{\gamma_3}{\sqrt{\gamma_1^2 + \gamma_3^2}} \frac{\gamma_2}{ |\vec \gamma|}$$

$$ \tan \phi_0 =- \frac{\gamma_1 |\vec \gamma|}{\gamma_3 \sqrt{\gamma_1^2 + \gamma_3^2}} $$

where $T$ is the orbital period in days, $i$ is the inclination with respect to the sky plane, $\phi_0$ is the phase angle from the line of nodes of the orbit with the sky plane.

[Go to **Binary Sources**](BinarySources.md)
