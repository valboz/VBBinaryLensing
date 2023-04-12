
**Work in progress here**

# Advanced control

In this section we discuss some technical aspects that can be controlled by an advanced user.

## Implementation notes on BinaryMag2 and ESPLMag2

Throughout our documentation we have recommended the use of `BinaryMag2` and `ESPLMag2`. These two functions start with a point-source calculation and evaluate the quadrupole correction. If this exceeds a dynamically calculated threshold, then the full extended-source calculation with contour integration is performed. All details about the quadrupole correction and the thresholds to switch from point-source to extended-source are illustrated in [V. Bozza et al., MNRAS 479 (2018) 5157](https://ui.adsabs.harvard.edu/abs/2018MNRAS.479.5157B/abstract). 

We already presented the `BinaryMag0` and `PSPLMag` functions for point-source calculations. 

The extended-source calculations are performed by the functions `BinaryMagDark` and `ESPLMagDark`. These functions are called by the parent functions `BinaryMag2` and `ESPLMag2` to perform the contour integration including limb darkening if the quadrupole test indicates that the point-source magnification is inaccurate. Actually, these functions are also directly available to the user who might be interested in them for several reasons. The syntax is very simple:

```
Mag = VBBL.BinaryMagDark(s, q, y1, y2, rho, accuracy); // Magnification of a limb-darkened source by a binary lens.
Mag = VBBL.ESPLMagDark(u, rho); // Magnification of a uniform source by a single lens.
```




```
Mag = VBBL.BinaryMag(s, q, y1, y2, rho, accuracy); // Magnification of a uniform source by a binary lens.
Mag = VBBL.ESPLMag(u, rho); // Magnification of a uniform source by a single lens.
```



first calculates the point-source magnification through BinaryMag0
	// Then it evaluates the quadrupole correction. If it is too high, it goes for the full computation.
	// This is performed by calling BinaryMagDark. This function is also directly available to the user (as it was in v1.0).
	// Mag = VBBL.BinaryMagDark(s, q, y1, y2, Rs, a1, accuracy); // Note that the limb darkening and the accuracy are required parameters.

	// BinaryMagDark performs contour integration on several annuli. The number and radii of annuli is determined dynamically.
	// Each contour is treated as a uniform source by a call to the function BinaryMag (also directly available to the user).
	// Mag = VBBL.BinaryMag(s, q, y1, y2, Rs, accuracy); // Magnification of a uniform source.

	// The use of BinaryMag2 is strongly recommended, since it may save computational time by a factor ranging from 10 to 100.
	// Useless contour integrations are avoided if the required precision and accuracy are already met 
	// by the point-source computation.



## Number of annuli in limb darkening calculation

The functions ```ESPLMag2``` and ```BinaryMag2``` are designed 

	// After each calculation, the number of annuli used is available in VBBL.nannuli.
	// If you are probing extremely tiny caustics with very large sources, you may impose a minimum number of annuli.
	// Before your calculation, just set
	// VBBL.minannuli=2; //or whatever you need 
	// The total number of points used is available in VBBL.NPS
	printf("Annuli used: %d\nTotal number of points: %d\n", VBBL.nannuli, VBBL.NPS);


	//////////////////////////////////////////
	// Parameters range
	//////////////////////////////////////////

	// Testing has been performed with 1.e-9 <= q <= 1
	// Failures (errors larger than declared Tolerance) are below 1 in 1000 caustic crossings in the ranges
	// 0.01< s < 10 for q=1.0
	// 0.1 < s < 4 for q=1.e-9
	// y1 and y2 may vary from 0 to 500 without any failures.
	// Above ranges apply to source radius between 1.e-3 to 1.0. 
	// Outside this range the robustness gradually degrades, 
	// but we typically obtain very good results for reasonable values of s and q.
	
	
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
