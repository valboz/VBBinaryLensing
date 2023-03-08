[Back to **Accuracy Control**](AccuracyControl.md)

# Light Curve Functions

VBBinaryLensing offers ready-to-use functions to calculate full microlensing light curves with standard parameters. There are functions for single and binary lenses, single and binary sources, for light curves including parallax, orbital motion or xallarap.

Each of these light curve functions accepts an array of parameters as first argument. The second argument is the time at which we want the magnification.

## Point-Lens-Point-Source light curve

```
double pr[3]; // Array of parameters
double u0, t0, tE, t, Mag;

u0 = 0.01; // Impact parameter
t0 = 7550.4; // Time of closest approach to the center of mass
tE = 100.3; // Einstein time

pr[0] = log(u0); 
pr[1] = log(tE);
pr[2] = t0;

t=7551.6; // Time at which we want to calculate the magnification

Mag = PSPLLightCurve(pr, t); // Calculates the PSPL magnification at time t with parameters in pr
```



[Go to **Parallax**](Parallax.md)
