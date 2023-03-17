[Back to **Orbital motion**](OrbitalMotion.md)

# Binary sources

Binary sources just give the superposition of two single-source microlensing light curves. In VBBinaryLensing we have the `BinSourceLightCurve` function, illustrated in the following example:

```
VBBinaryLensing VBBL; // Declare instance to VBBinaryLensing

double pr[6]; // Array of parameters
double tE, FR, u01, u02, t01, t02, t;

u01 = 0.01; // Impact parameter for source 1
u02 = 0.03; // Impact parameter for source 2
t01 = 7550.4; // Time of closest approach to source 1
t02 = 7551.8; // Time of closest approach to source 2
tE = 37.3; // Einstein time
FR = 0.1; // Flux ratio of the second source to the first

// Let us put all parameters in our array
pr[0] = log(tE);
pr[1] = log(FR);
pr[2] = u01;
pr[3] = u02;
pr[4] = t01;
pr[5] = t02;

t = 7551.6; // Time at which we want to calculate the magnification

Mag = VBBL.BinSourceLightCurve(pr, t); // Calculates the Binary Source magnification at time t with parameters in pr
printf("Binary Source Light Curve at time t: %lf", Mag); // Output should be 29.97...
```

The output of BinSourceLightCurve is a magnification compared to the baseline flux. Therefore, it is the sum of two Paczynsky light curves weighted by 1/(1+FR) and FR/(1+FR) respectively.

Parallax is included in the `BinSourceLightCurveParallax` function, which accepts two more parameters for the parallax components, as illustrated in the [Parallax](Parallax.md) section.


[Go to **Advanced control**](AdvancedControl.md)
