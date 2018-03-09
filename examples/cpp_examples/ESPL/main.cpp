#include <stdio.h>
#include <math.h>
#include "VBBinaryLensingLibrary.h"

int main()
{

    // Declaration of an instance to VBBinaryLensing class. 
	VBBinaryLensing VBBL;

    // Extended-source-point-lens

	VBBL.LoadESPLTable("../../ESPL.tbl"); // Load the pre-calculated table (you only have to do this once and for all)

    // Specify parameters
	double u = 0.1; // Source-lens separation in Einstein radii.
    double Rs = 0.01; // Source radius in Einstein radii of the total mass.

	VBBL.a1 = 0.51; // Linear limb darkening coefficient. I(r)=I(0)(1-a1(1-\sqrt{1-r^2/\rho^2}))

	double Mag = VBBL.ESPLMag2(u, Rs); // Call to the ESPLMag2 function with these parameters
	printf("\nMagnification of Extended-source-point-lens = %lf\n", Mag);  // Output should be 10.05.....

	// Implementation notes:
	// ESPLMag2 works the same way as BinaryMag2. It checks whether we are far enough to use the point-source approximation.
	// If necessary, it goes for the full computation by calling ESPLMagDark(double u, double rho, double a1);
	// ESPLMagDark divides the source disk in annuli. 
	// Each annulus is calculated by a call to ESPLMag(double u, double rho), which uses a pre-calculated table (extremely fast).

    // Critical curves and caustics

	// If you want the critical curves and caustics for a particular s,q configuration, the function you need is PlotCrit.
	// Here is an example of use with the results printed in an ASCII file.
	//_sols *Mycurves;
	//FILE *f;
	//
	//Mycurves=VBBL.PlotCrit(s,q);
	//f=fopen("outcrits.txt","w");
	//fprintf(f,"c\n");
	//for(_curve *c=Mycurves->first;c;c=c->next){
	//	for(_point *p=c->first;p;p=p->next){
	//		fprintf(f,"%.10lf %.10lf\n",p->x1,p->x2);
	//	}
	//	fprintf(f,"c\n");
	//}
	//fclose(f);
	// Note that critical curves and caustics are in the same list Mycurves. 
	// If the list contains 2n curves, the first n are the critical curves and the second n curves are the caustics.

}
