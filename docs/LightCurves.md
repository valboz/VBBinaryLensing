[Back to **Accuracy Control**](AccuracyControl.md)

# Light Curve Functions

VBBinaryLensing offers ready-to-use functions to calculate full microlensing light curves with standard parameters. There are functions for single and binary lenses, single and binary sources, for light curves including parallax, orbital motion or xallarap.

Each of these functions comes in two flavors: calculation of a single point in the light curve with standard parameters; calculation of the whole light curve on an array of times with a single function call.

## Point-Lens-Point-Source light curve

Let us start with the Paczynski curve (see [Single lenses](SingleLenses.md) section). 

For the calculation of the light curve at one time `t`, we just need to define the array of standard parameters as shown in the following example and call the function `PSPLLightCurve`:

```
VBBinaryLensing VBBL;

double pr[3]; // Array of parameters
double u0, t0, tE;
double t, Mag;

u0 = 0.01; // Impact parameter
tE = 100.3; // Einstein time
t0 = 7550.4; // Time of closest approach to the center of mass

pr[0] = log(u0); // Note that we give some parameters in log scale
pr[1] = log(tE);
pr[2] = t0;

t=7551.6; // Time at which we want to calculate the magnification

Mag = VBBL.PSPLLightCurve(pr, t); // Calculates the PSPL magnification at time t with parameters in pr
printf("PSPL Light Curve at time t: %lf", Mag); // Output should be 64.13...
```

The use of logarithms for some parameters is useful e.g. in Markov chains or fitting when the possible values may span several orders of magnitudes.

## Full light curve with one call

We may want to calculate the full light curve on an array of times. For example if we have a set of observations taken by a given telescope or if we want to simulate a light curve with a given time sampling. This is possible if we also give the arrays of time as additional argument. Furthermore, we also need to give the locations where the outputs must be stored. This means that the function expects an array for the magnification, an array for the source coordinate y1 and one more for the coordinate y2, as shown in the example.

```
VBBinaryLensing VBBL;

double pr[3]; // Array of parameters

const int np=100; // Number of points in the light curve
double times[np]; // Array of times 
double mags[np]; // Array of magnifications where to store the output
double y1s[np]; // Array of source coordinates y1 for each time
double y2s[np]; // Array of source coordinates y2 for each time

double u0, t0, tE;
double t, Mag;

u0 = 0.01; // Impact parameter
tE = 100.3; // Einstein time
t0 = 7550.4; // Time of closest approach to the center of mass

pr[0] = log(u0); // Note that we give some parameters in log scale
pr[1] = log(tE);
pr[2] = t0;

// Suppose we want to simulate the light curve with a fixed time sampling
for(int i=0;i<np;i++){
  times[i]=t0-tE+2*tE/np*i;
}

VBBL.PSPLLightCurve(pr, times, mags, y1s, y2s, np); // Calculates the whole light curve and stores the magnifications in the array mags
for (int i = 0; i < np; i++) {
  printf("\n%lf %lf %lf", mags[i], y2a[i], y2s[i]);
}
```

Now the array `mags` contains the magnification for each time specified in the array `times`.

Moreover, we also have the source trajectory relative to the lens in the arrays `y1s` and `y2s`, which can be useful to draw plots with the source trajectory. The convention used here is that the source comes from the right to the left (positive to negative y1) with y2 fixed to -u0. This is consistent with the other light curve calculations where the rotational symmetry is lost. In detail, we have

$$y_1=-\frac{t-t_0}{t_E}$$

$$y_2=-u_0$$

Apart from the compactness of the code, some computational advantage of the use of the single-call light curve function emerges with higher order effects, in which some calculations are re-used and not repeated at every function call.

[Go to **Parallax**](Parallax.md)
