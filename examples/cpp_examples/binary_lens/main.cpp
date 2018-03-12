#include <stdio.h>
#include <iostream>
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
        t[i] = 7000. + double(i)/double(n_points)*300;
    }

	double s = 1.2; //separation between the two lenses
	double q = 0.5; // mass ratio: mass of the lens on the right divided by mass of the lens on the left
	double Rs = 0.01; // Source radius in Einstein radii of the total mass.
    double alpha = 0.93; // Angle between lens axis and source trajectory
    double tE = 100.3;
    double t0 = 7154.;
    double u0 = 0.2;
    double tau;

    // Position of the center of the source with respect to the center of mass.
    double cosalpha = cos(alpha);
    double sinalpha = sin(alpha);

    for (int i = 0; i < n_points; ++i) {
		tau = (t[i] - t0)/tE;
		y1[i] = -u0*cosalpha + tau*cosalpha;
		y2[i] = u0*cosalpha + tau*sinalpha;
		mag[i] = VBBL.BinaryMag2(s, q, y1[i], y2[i], Rs);
    }

    std::ofstream file1("output.csv");

    for (int i = 0; i < n_points; ++i) {
        file1 <<t[i]<<","<<y1[i]<<","<<y2[i]<<","<<mag[i]<<std::endl;
    }
    file1.close();
    // Critical curves and caustics

	// If you want the critical curves and caustics for a particular s,q configuration, the function you need is PlotCrit.
	// Here is an example of use with the results printed in an ASCII file.
    // Initialize an instance of the _sols class
	_sols *Mycurves;
	
    std::ofstream file2("caustics.csv");

    // This lists stores both the crit. curves and the caustics, if the list contains 2n curves the first n curves
    // are the cirt. curves and the second n curves are the caustics
	Mycurves = VBBL.PlotCrit(s, q);

    // Iterate over all the curves (both critical and caustics) given by PlotCrit 
    int n_curves = 0;
	for(_curve *c=Mycurves->first; c; c=c->next){
        n_curves++;
    }

    int i = 0;
    // Save all caustic curves to file
	for(_curve *c=Mycurves->first; c; c=c->next){
        if(i >= n_curves/2){
            for(_point *p=c->first; p; p=p->next){
                file2<<p->x1<<","<<p->x2<<std::endl;
                }
		}
        i++;
	}
	file2.close();

	 //Note that critical curves and caustics are in the same list Mycurves. 
	// If the list contains 2n curves, the first n are the critical curves and the second n curves are the caustics.

	// Implementation notes:
	// ESPLMag2 works the same way as BinaryMag2. It checks whether we are far enough to use the point-source approximation.
	// If necessary, it goes for the full computation by calling ESPLMagDark(double u, double rho, double a1);
    
}
