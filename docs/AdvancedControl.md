# Advanced control

In this section we discuss some technical aspects that can be controlled by an advanced user.

## Implementation notes on BinaryMag2 and ESPLMag2

Throughout our documentation we have recommended the use of `BinaryMag2` and `ESPLMag2`. These two functions start with a point-source calculation and evaluate the quadrupole correction. If this exceeds a dynamically calculated threshold, then the full extended-source calculation with contour integration is performed. All details about the quadrupole correction and the thresholds to switch from point-source to extended-source are illustrated in [V. Bozza et al., MNRAS 479 (2018) 5157](https://ui.adsabs.harvard.edu/abs/2018MNRAS.479.5157B/abstract). 

## Lower level functions for basic magnification calculations

The parent functions `BinaryMag2` and `ESPLMag2` call lower level functions for individual calculations. We already presented the `BinaryMag0` ([Binary Lenses section](BinaryLenses.md)) and `PSPLMag` ([Single Lenses section](SingleLenses.md)) functions for point-source calculations. 

Whenever the quadrupole test indicates that the point-source is inaccurate, the functions `BinaryMagDark` or `ESPLMagDark` are called to perform extended-source calculations including limb darkening. Also these functions are directly available to the user who might be interested in them for several reasons. The syntax is very simple:

```
Mag = VBBL.BinaryMagDark(s, q, y1, y2, rho, accuracy); // Magnification of a limb-darkened source by a binary lens.
Mag = VBBL.ESPLMagDark(u, rho); // Magnification of a limb-darkened source by a single lens.
```

As explained in the corresponding section, [Limb Darkening](LimbDarkening.md) is obtained by repeating contour integration on concentric annuli. The number and location of the annuli is decided dynamically comparing the accuracy goal with the difference in the results obtained on different contours. 

Both functions `BinaryMagDark` and `ESPLMagDark` call lower level functions to perform each individual contour integration on a uniform disk source. Such lower level functions are `BinaryMag` and `ESPLMag`, which are also accessible to the user and have a similar syntax

```
Mag = VBBL.BinaryMag(s, q, y1, y2, rho, accuracy); // Magnification of a uniform source by a binary lens.
Mag = VBBL.ESPLMag(u, rho); // Magnification of a uniform source by a single lens.
```

These functions are particularly useful for diagnostics on particular cases and for overriding the high-level control offered by `BinaryMag2` and `ESPLMag2`, if necessary. 

## Advanced contol in limb darkening

The number of annuli used in any magnification calculation on a limb-darkened source in VBBinaryLensing is reported through the property `VBBL.nannuli`. This can be a useful diagnostics to know how deep the calculation had to go in order to meet the required accuracy.

Furthermore, there are exceptional situations in which huge sources cover tiny caustics. If both the center and the margin of the source are far from the caustic, there is a chance that `BinaryMag2` does not judge worthwhile to insert any annuli in-between, thereby missing the subtle perturbation by the caustic. In these cases, the user may force VBBinaryLensing to use a minimum number of annuli by changing  `VBBL.minannuli`. 

For example, by setting 

`VBBL.minannuli = 2;`

there will always be one annulus between the center and the boundary of the source.

## Advanced control in contour integration

As metioned before, the basic function for contour integration of a uniform source in binary lensing is `BinaryMag`. The inversion of the lens equation is performed on a sample of points on the source boundary. The number and location of points on the source boundary is optimized by a careful estimate of the errors committed in the magnification calculation (see  [V. Bozza, MNRAS 408 (2010) 2188](https://ui.adsabs.harvard.edu/abs/2010MNRAS.408.2188B/abstract) for all details about the algorithm).

### Total number of points in contours

The total number of points on which the lens equation inversion is performed is reported by `VBBL.NPS`. This diagnostics gives the possibility to quantify the computational load of a particular calculation. After a call to `BinaryMag`, `VBBL.NPS` reports the number of points on the source boundary. After a call to `BinaryMagDark`, `VBBL.NPS` reports the total number of points on all annuli used for the limb darkened magnification. After a call to `BinaryMag2`, `VBBL.NPS` reports the total number of points used: either 1 for a point-source or the total number needed for the extended-source calculation.

### Setting the total number of points

`BinaryMag` increases the number of points in the sampling of the source boundary until the estimated error falls below the accuracy or precision thresholds fixed by `VBBL.Tol` and `VBBL.RelTol` (see [Accuracy Control](AccuracyControl.md)). Actually, the accuracy also appear as an explicit parameter in the function syntax
`VBBL.BinaryMag(s, q, y1, y2, rho, accuracy);` After the function call, `VBBL.Tol` is updated to the accuracy specified in the call.

However, the behavior of the function changes if an accuracy greater than 1 is specified. In this case, the accuracy parameter becomes the number of points to be used in the sampling of the source boundary. For example,  `VBBL.BinaryMag(s, q, y1, y2, rho, 100);` will calculate the magnification on a boundary with 100 sampling points. The location of the points is still chosen so as to minimize the total error. 

This variant of `BinaryMag` can be useful to check how the algorithm proceeds up to a given density of the sampling and identify possible sources of errors.

### Estimated error

Another important diagnostics only available with `BinaryMag` is the error estimate `VBBL.therr`. As said before, the sampling on the source boundary is increased until the estimated error falls below the accuracy or precision thresholds fixed by `VBBL.Tol` and `VBBL.RelTol` (see [Accuracy Control](AccuracyControl.md)). However, when the input parameters are pushed to extreme values, numerical errors will eventually dominate and preclude any possibilities to meet the desired accuracy. `BinaryMag` will always try to return a reasonable estimate of the magnification by discarding problematic points on the source boundary. This comes to the cost of leaving irreducible errors in the final result. Therefore, `VBBL.therr` can track such occurrences and report an error estimate that can be useful in these particular situations.

## Parameters range

VBBinaryLensing has been widely tested with particular attention on caustic crossings and all source positions close to caustics. Here we report the recommended ranges of parameters for `BinaryMag2`.

Mass ratio: testing has been performed with $10^{-9} \leq q \leq 1$.

Failures (errors larger than accuracy goal specified by `VBBL.Tol`) are below 1 in 1000 caustic crossings in the following ranges

$0.01< s < 10$ for $q = 1.0$

$0.1 < s < 4$ for $q=10^{-9}$

For intermediate mass ratios, these ranges can be easily interpolated.

Concerning the source coordinates $y_1$ and $y_2$, we have found no restrictions.

Above ranges apply to source radii $10^{-3}\leq \rho \leq 1.0$. Outside this range, the robustness slowly degrades.

Finally, we note that lower level functions such as `BinaryMag` and `BinaryMagDark` may have local failures which do not appear in `BinaryMag2`, which takes care of these particular cases.

## Image contours

In classical microlensing, only the total magnification and the astrometric centroid are of interest. However, for illustration purposes or for particular diagnostics, we may be interested in the individual image contours. These can be retrieved by the lowest level versions of `BinaryMag` and `BinaryMag0`, as shown in this example, which prints the points on the image boundaries to an ASCII file.

```
_sols *Images;
FILE *f;

Mag=VBBL.BinaryMag(s,q,y1,y2,Rs,accuracy,&Images);
f=fopen("outcurves.txt","w");
for(_curve *c=Images->first;c;c=c->next){
   for(_point *p=c->first;p;p=p->next){
      fprintf(f,"%.16lf %.16lf\n",p->x1,p->x2);
   }
   fprintf(f,"c\n");
}
fclose(f);
delete Images;
```

The `_sols`, `_curve` and `_point` classes have been already introduced in the [Critical Curves](CriticalCurvesAndCaustics.md) section. Each curve is an image boundary with a given parity. Merging images at caustic crossings will thus be described by two curves, one for the positive parity side and one for the negative parity side.
