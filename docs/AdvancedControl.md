
**Work in progress here**

# Advanced control

In this section we discuss some technical aspects that can be controlled by an advanced user.

## Implementation notes on BinaryMag2 and ESPLMag2

Throughout our documentation we have recommended the use of `BinaryMag2` and `ESPLMag2`. These two functions start with a point-source calculation and evaluate the quadrupole correction. If this exceeds a dynamically calculated threshold, then the full extended-source calculation with contour integration is performed. All details about the quadrupole correction and the thresholds to switch from point-source to extended-source are illustrated in [V. Bozza et al., MNRAS 479 (2018) 5157](https://ui.adsabs.harvard.edu/abs/2018MNRAS.479.5157B/abstract). 

## Lower level functions for basic magnification calculations

We already presented the `BinaryMag0` and `PSPLMag` functions for point-source calculations. 

The extended-source calculations are performed by the functions `BinaryMagDark` and `ESPLMagDark`. These functions are called by the parent functions `BinaryMag2` and `ESPLMag2` to perform the contour integration including limb darkening if the quadrupole test indicates that the point-source magnification is inaccurate. Actually, these functions are also directly available to the user who might be interested in them for several reasons. The syntax is very simple:

```
Mag = VBBL.BinaryMagDark(s, q, y1, y2, rho, accuracy); // Magnification of a limb-darkened source by a binary lens.
Mag = VBBL.ESPLMagDark(u, rho); // Magnification of a limb-darkened source by a single lens.
```

As explained in the corresponding section, [Limb Darkening](LimbDarkening.md) is obtained by repeating contour integration on concentric annuli. The number and location of the annuli is decided dynamically comparing the accuracy goal with the difference in the results obtained on different contours. 

The magnification for a uniform circular source is obtained by the `BinaryMag` and `ESPLMag` functions, which also have a similar syntax

```
Mag = VBBL.BinaryMag(s, q, y1, y2, rho, accuracy); // Magnification of a uniform source by a binary lens.
Mag = VBBL.ESPLMag(u, rho); // Magnification of a uniform source by a single lens.
```

## Advanced contol in limb darkening

The number of annuli used in any magnification calculation in VBBinaryLensing is reported through the property `VBBL.nannuli`. This can be a useful diagnostics to know how deep had to go the calculation to meet the required accuracy.

Furthermore, there are exceptional situations in which huge sources cover tiny caustics. If both the center and the margin of the source are far from the caustic, there is a chance that `BinaryMag2` does not judge worthwhile to insert any annuli in-between, therefore missing the subtle perturbation by the caustic. In these cases, the user may force VBBinaryLensing to use a minimum number of annuli by changing  `VBBL.minannuli`. 

For example, by setting 

`VBBL.minannuli = 2;`

there will always be one annulus between the center and the boundary of the source.

## Advanced control in contour integration

As metioned before, the basic function for contour integration of a uniform source in binary lensing is `BinaryMag`. The inversion of the lens equation is performed on a sample of points on the source boundary. The number and location of points on the source boundary is optimized by a careful estimate of the errors committed in the magnification calculation (see  [V. Bozza, MNRAS 408 (2010) 2188](https://ui.adsabs.harvard.edu/abs/2010MNRAS.408.2188B/abstract) for all details about the algorithm).

### Total number of points in contours

The total number of points on which the lens equation inversion is performed is reported by `VBBL.NPS`. This diagnostics gives the possibility to quantify the computational load of a particular calculation. After a call to `BinaryMag`, `VBBL.NPS` reports the number of points on the source boundary. After a call to `BinaryMagDark`, `VBBL.NPS` reports the total number of points on all annuli used for the limb darkened magnification. After a call to `BinaryMag2`, `VBBL.NPS` reports the total number of points used: either 1 for a point-source or the total number needed for the extended-source calculation.

### Setting the total number of points

`BinaryMag` increases the number of points in the sampling of the source boundary until the estimated error falls below the accuracy or precision thresholds fixed by `VBBL.Tol` and `VBBL.RelTol` (see [Accuracy Control](AccuracyControl.md)). Actually, the accuracy also appear as an explicit parameter in the function syntax:

```
Mag = VBBL.BinaryMag(s, q, y1, y2, rho, accuracy); // Magnification of a uniform source by a binary lens to the specified accuracy.
```

After the function call, `VBBL.Tol` is updated to the accuracy specified in the call.

However, the behavior of the function changes if an accuracy greater than 1 is specified. In this case, the accuracy value becomes the number of points to be used in the sampling of the source boundary. For example,  `VBBL.BinaryMag(s, q, y1, y2, rho, 100);` will calculate the magnification on a boundary with 100 sampling points. The location of the points is still chosen so as to minimize the total error. 

This variant of `BinaryMag` can be useful to check how the algorithm proceeds up to a given density of the sampling and identify possible sources of errors.

### Estimated error

Another important diagnostics only available with `BinaryMag` is the error estimate `VBBL.therr`. The sampling on the source boundary is increased until the estimated error falls below the accuracy or precision thresholds fixed by `VBBL.Tol` and `VBBL.RelTol` (see [Accuracy Control](AccuracyControl.md)). However, when the input parameters are pushed to extreme values, numerical errors will eventually dominate and preclude any possibilities to meet the desired accuracy. `BinaryMag` will always try to return a reasonable estimate of the magnification by discarding problematic points on the source boundary. This comes to the cost of leaving irreducible errors in the final result. Therefore, `VBBL.therr` can track such occurrences and report an error estimate that can be useful in these particular situations.

## Parameters range

VBBinaryLensing has been widely tested with particular attention on caustic crossings and all source positions close to caustics. Here we report the recommended ranges of parameters for `BinaryMag2`.

Mass ratio: testing has been performed with $10^{-9} \leq q \leq 1$.

	// 
	// Failures (errors larger than declared Tolerance) are below 1 in 1000 caustic crossings in the ranges
	// 0.01< s < 10 for q=1.0
	// 0.1 < s < 4 for q=1.e-9
	// y1 and y2 may vary from 0 to 500 without any failures.
	// Above ranges apply to source radius between 1.e-3 to 1.0. 
	// Outside this range the robustness gradually degrades, 
	// but we typically obtain very good results for reasonable values of s and q.

Note that lower level functions such as `BinaryMag` and `BinaryMagDark` may have local failures which do not appear in `BinaryMag2`, which takes care of these particular cases.


		//////////////////////////////////////////
	// Image contours
	//////////////////////////////////////////

	// If you want the shapes of the contours of the images there are low-level versions of BinaryMag and BinaryMag0.
	// This example calculates the magnification and stores the contours in Images. Then the cycle exports the contours in a ASCII file.
	//_sols *Images;
	//FILE *f;
	//
	//Mag=VBBL.BinaryMag(s,q,y1,y2,Rs,accuracy,&Images);
	//f=fopen("outcurves.txt","w");
	//for(_curve *c=Images->first;c;c=c->next){
	//	for(_point *p=c->first;p;p=p->next){
	//		fprintf(f,"%.16lf %.16lf\n",p->x1,p->x2);
	//	}
	//	fprintf(f,"c\n");
	//}
	//fclose(f);
	//delete Images;
