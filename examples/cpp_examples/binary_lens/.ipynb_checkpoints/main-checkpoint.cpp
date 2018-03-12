#include <stdio.h>
#include <cmath>
#include "VBBinaryLensingLibrary.h"
#include <vector>
#include <fstream>

int main()
{

    // Declaration of an instance to VBBinaryLensing class. 
	VBBinaryLensing VBBL;

    int n_points = 500;
    std::vector<double> mag(n_points);
    std::vector<double> y1(n_points);
    std::vector<double> y2(n_points);
    std::vector<double> t(n_points);
    for (int i=0; i < n_points; ++i) {
        t[i] = 7200. + double(i);
    }

	double s = 0.8; //separation between the two lenses
	double q = 0.1; // mass ratio: mass of the lens on the right divided by mass of the lens on the left
	double Rs = 0.01; // Source radius in Einstein radii of the total mass.
    double alpha = 0.53; // Angle between lens axis and source trajectory
    double tE = 100.3;
    double t0 = 7554.;
    double u0 = 0.01;
    double tau;

    // Position of the center of the source with respect to the center of mass.
    double cosalpha = cos(alpha);
    double sinalpha = sin(alpha);

    for (int i = 0; i < n_points; ++i) {
		tau = (t[i] - t0)*tE;
		y1[i] = -u0*cosalpha + tau*cosalpha;
		y2[i] = u0*cosalpha + tau*sinalpha;
		mag[i] = VBBL.BinaryMag2(s, q, y1[i], y2[i], Rs);
    }

    std::ofstream ofile("output.csv");

    for (int i = 0; i < n_points; ++i) {
        ofile <<y1[i]<<","<<y2[i]<<","<<mag[i]<<std::endl;
    }
    ofile.close();
    
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
