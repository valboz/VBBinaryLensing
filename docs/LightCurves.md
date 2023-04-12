[Back to **Accuracy Control**](AccuracyControl.md)

# Light Curve Functions

VBBinaryLensing offers ready-to-use functions to calculate full microlensing light curves with standard parameters. There are functions for single and binary lenses, single and binary sources, for light curves including parallax, orbital motion or xallarap.

Each of these functions comes in two flavors: calculation of a single point in the light curve with standard parameters; calculation of the whole light curve on an array of times with a single function call.

We start by explaining the single-point versions for each physical case and then we discuss the full light curve calculation in the end.

## Point-Source-Point-Lens light curve

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

The use of logarithms for some parameters is useful e.g. in Markov chains or other fitting algorithms when the possible values that occur in real cases may span several orders of magnitudes.

To make contact with the section [Single lenses](SingleLenses.md), we also report how the source position is calculated with our standard parameters:

$$y_1=-\frac{t-t_0}{t_E}$$

$$y_2=-u_0$$

$$u=\sqrt{y_1^2+y_2^2}$$

$u$ is the source angular separation relative to the lens in Einstein radii, as discussed in the section [Single lenses](SingleLenses.md).

The coordinates of the source at time $t$ as found by these formulae are stored in the public properties `VBBL.y_1` and `VBBL.y_2` of the VBBinaryLensing class. For a PSPL model there is rotational symmetry, so we do not care too much about the role of y1 and y2, but this notation is consistent with that used for binary lenses. The information on the source position can be useful to draw plots with the source trajectory relative to the caustics.

## Extended-Source-Point-Lens light curve

Everything is similar to what we already discussed before. We just have the source radius as an additional parameter

```
VBBinaryLensing VBBL;

double pr[4]; // Array of parameters
double u0, t0, tE, rho;
double t, Mag;

u0 = 0.01; // Impact parameter
tE = 100.3; // Einstein time
t0 = 7550.4; // Time of closest approach to the center of mass
rho = 0.01; // Source radius

pr[0] = log(u0); // Note that we give some parameters in log scale
pr[1] = log(tE);
pr[2] = t0;
pr[3] = log(rho);

t=7551.6; // Time at which we want to calculate the magnification

VBBL.LoadESPLTable("ESPL.tbl"); // Do not forget to load the pre-calculated tables before the first ESPL calculation!

Mag = VBBL.ESPLLightCurve(pr, t); // Calculates the ESPL magnification at time t with parameters in pr
printf("ESPL Light Curve at time t: %lf", Mag); // Output should be 68.09...
```

The source position is calculated in the same way as for the `PSPLLightCurve` function. All considerations about [Limb Darkening](LimbDarkening.md) apply to this function as well.


## Binary Lens light curve

A minimum set of parameters in binary lensing also includes the mass ratio q, the separation s and the angle $\alpha$ between the source trajectory and the binary lens axis. We remind that our coordinate system has its origin in the center of mass, with the first lens on the left and the second lens on the right (see [BinaryLenses](BinaryLenses.md)). The source trajectory is parameterized as follows:

$$ \hat t = \frac{t-t_0}{t_E} $$

$$ y_1 = u_0 ~ \sin(\alpha) - \hat t ~ \cos(\alpha) $$

$$ y_2 = -u_0 ~ \cos(\alpha) - \hat t ~ \sin(\alpha) $$ 

<img src="sourcetrajconvention.png" width = 600>

Let us see an example:

```
VBBinaryLensing VBBL;

double pr[7]; // Array of parameters
double u0, t0, tE, rho, alpha, s, q;
double t, Mag;

u0 = -0.01; // Impact parameter
t0 = 7550.4; // Time of closest approach to the center of mass
tE = 100.3; // Einstein time
rho = 0.01; // Source radius
s = 0.8; // Separation between the two lenses
q = 0.1; // Mass ratio
alpha = 0.53; // Angle of the source trajectory

pr[0] = log(s); 
pr[1] = log(q);
pr[2] = u0;
pr[3] = alpha;
pr[4] = log(rho);
pr[5] = log(tE);
pr[6] = t0;

t=7551.6; // Time at which we want to calculate the magnification

Mag = VBBL.BinaryLightCurve(pr, t); // Calculates the Binary Lens magnification at time t with parameters in pr
printf("Binary Light Curve at time t: %lf", Mag); // Output should be 31.00...
```

As before, the coordinates of the source are stored in the public properties `VBBL.y_1` and `VBBL.y_2` of the VBBinaryLensing class. These can be useful to draw the source trajectory relative to the caustics.

[Limb Darkening](LimbDarkening.md) and [accuracy goal](AccuracyControl.md) can be specified as shown in the respective sections.

We finally mention a possible variant in the parameterization. With the function `BinaryLightCurveW` the time of closest approach `t0` and the impact parameter `u0` are relative to the position of the caustic of the mass on the right, whose center lies at coordinates 

$$\left(\frac{1}{1+q} \left( s - \frac{1}{s} \right), 0 \right)$$

This parameterization is useful for fitting wide binary models.

## Full light curve with one call

We may want to calculate the full light curve on an array of times. For example if we have a set of observations taken by a given telescope or if we want to simulate a light curve with a given time sampling. All light curve functions in VBBinaryLensing have an overload in which the time `t` is replaced by an array of times as additional argument. Furthermore, we also need to give the locations where the outputs must be stored. This means that the function expects an array for the magnification, an array for the source coordinate y1 and one more for the coordinate y2, as shown in the following example, which refers to the PSPL light curve.

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

// Let's print the results
for (int i = 0; i < np; i++) {
  printf("\n%lf %lf %lf %lf", times[i], mags[i], y2a[i], y2s[i]);
}
```

Now the array `mags` contains the magnification for each time specified in the array `times`.

Moreover, we also have the source trajectory relative to the lens in the arrays `y1s` and `y2s`, which can be useful to draw plots with the source trajectory as discussed before.

Apart from the compactness of the code, some computational advantage of the use of the single-call light curve function emerges with higher order effects, in which some calculations are re-used and not repeated at every function call.

The full light curve calculation is offered for each physical case (PSPL, ESPL, Binary) with a syntax identical to the example for the PSPL light curve shown explicitly here.

[Go to **Parallax**](Parallax.md)
