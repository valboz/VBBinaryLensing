[Back to **Binary lenses**](BinaryLenses.md)

# Critical curves and caustics

The gravitational lensing phenomenology is strictly related to the existence of critical curves and caustics (see the recommended [reviews](reviews.md) for a full treatment).

VBBinaryLensing offers the calculation of critical curves and caustics with an arbitrary number of points through the function ```PlotCrit```.

The result is an instance to a ```_sols``` object, which is a collection of ```_curve``` objects.

A ```_curve``` object is a collection of ```_point``` objects. 

The use of these objects is very intuitive, as illustrated by this example, which prints the points of the critical curves and caustics to two different ASCII files:

```
VBBinaryLensing VBBL; // Instance to VBBinaryLensing
double s,q;
_sols* Mycurves;  // Declaration of a _sols pointer
_curve* c;  // Declaration of a _curve pointer
FILE* f;

s=2.5;  // Parameters of our binary lens
q=0.1;

Mycurves = VBBL.PlotCrit(s, q);  // Calculation of the critical curves. The result is stored in Mycurves.
                                  // Mycurves is a list of _curve objects
                                  // There are n critical curves and n caustics in this list, with n=1,2,3 depending on the caustic topology.
                                  // Mycurves->length will be therefore equal to 2n.

f = fopen("CriticalCurves.txt", "w"); // Let us write the result in an ASCII file
c = Mycurves->first;
        // Loop over the critical curves, which are the first n _curve objects in the list, with n = Mycurves->length /2.
for (int curvenumber = 1; curvenumber <= Mycurves->length / 2; curvenumber++) {  
  fprintf(f, "Critical curve #%d\n", curvenumber);
  for (_point* p = c->first; p; p = p->next) {    // Each _curve is a list of _point objects
    fprintf(f, "%lf %lf\n", p->x1, p->x2);      // We just write p->x1 and p->x2 to a file.
  }
  c = c->next;
}
fclose(f);
        // Loop over the caustics, which are the remaining n _curve objects in the list, with n = Mycurves->length /2.
f = fopen("Caustics.txt", "w");
for (int curvenumber = 1; curvenumber <= Mycurves->length / 2; curvenumber++) {
  fprintf(f, "Caustic #%d\n", curvenumber);
  for (_point* p = c->first; p; p = p->next) {
		fprintf(f, "%lf %lf\n", p->x1, p->x2);
	}
	c = c->next;
}
fclose(f);

delete Mycurves; // Do not forget to free your memory!
```

Critical curves and caustics are calculated through the resolution of a fourth order complex polynomial (see [reviews](reviews.md)) by the [Skowron & Gould algorithm](http://www.astrouw.edu.pl/~jskowron/cmplx_roots_sg/). 

The number of points calculated for the critical curves is controlled by ```VBBL.NPcrit```, which can be changed by the user according to the desired sampling. The default value is 200.

[Go to: **Limb Darkening**](LimbDarkening.md)
