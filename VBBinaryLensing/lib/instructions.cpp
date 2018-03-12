// Instructions for VBBinaryLensing v2.0.1 (2018)
//
// This code has been developed by Valerio Bozza, University of Salerno.
// Any use of this code for scientific publications should be acknowledged by a citation to
// V. Bozza, MNRAS 408 (2010) 2188
// Check the repository at http://www.fisica.unisa.it/GravitationAstrophysics/VBBinaryLensing.htm
// for the newest version.
//
// The code relies on the root solving algorithm by Jan Skworon and Andy Gould
// described in Skowron & Gould arXiv:1203.1034.
// Please also cite this paper if specifically relevant in your scientific publication.
// The original Fortran code available on http://www.astrouw.edu.pl/~jskowron/cmplx_roots_sg/
// has been translated to C++ by Tyler M. Heintz and Ava R. Hoag (2017)
//
// GNU Lesser General Public License applies to all parts of this code.
// Please read the separate LICENSE.txt file for more details.

#include <stdio.h>
#include <math.h>
#include "VBBinaryLensingLibrary.h"

//////////////////////////////////////////
// Summary
//////////////////////////////////////////

// - Declaration of VBBinaryLensing
// - Quick start for binary lens magnification with BinaryMag2
// - Accuracy control
// - Limb darkening
// - Point-source binary magnification
// - Implementation notes on BinaryMag2
// - Multi-band observations
// - Extended-source-point-lens magnification
// - Calculation of full light curves
// - Parallax calculation
// - Magnification as seen by a satellite
// - Other functions implemented in VBBinaryLensing
// - Obtaining image contours
// - Critical curves and caustics


int main()
{

//////////////////////////////////////////
// Declaration of an instance to VBBinaryLensing class. 

	VBBinaryLensing VBBL;

	// This can be done once in your code and then you can refer to this instance 
	// whenever you need to use the binary magnification calculation


//////////////////////////////////////////
// Quick start for binary magnification with BinaryMag2

	double Mag, s, q, y1, y2, Rs;

	s = 0.8; //separation between the two lenses
	q = 0.1; // mass ratio: mass of the lens on the right divided by mass of the lens on the left

			 // Position of the center of the source with respect to the center of mass.
	y1 = 0.01; // y1 is the source coordinate along the axis parallel to the line joining the two lenses 
	y2 = 0.01; // y2 is the source coordinate orthogonal to the first one
	Rs = 0.01; // Source radius in Einstein radii of the total mass.

	Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); // Call to the BinaryMag2 function with these parameters
	printf("Binary lens Magnification = %lf\n", Mag); // Output should be 18.28....


//////////////////////////////////////////
// Accuracy control

	VBBL.Tol = 1.e-3; // By default, the accuracy is 1.e-2. 
	Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); // The result will be Mag +- VBBL.Tol (absolute accuracy)
	printf("Magnification (accuracy at 1.e-3) = %lf\n", Mag); // Output should be 18.283....

	VBBL.Tol = 1.e-4;  
	Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); // The result will be Mag +- VBBL.Tol (absolute accuracy)
	printf("Magnification (accuracy at 1.e-4) = %lf\n", Mag); // Output should be 18.2833....
	// In general, 1.e-2 is largely sufficient (and faster).
	VBBL.Tol = 1.e-2;

	// In general, the photometric precision will not be better than 0.001;
	// You might want to set a relative precision goal, instead of an asbolute accuracy.
	// For example, let us set a poor 10% precision, just to see the difference
	VBBL.RelTol = 1.e-1;
	Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); // The result will be Mag*(1 +- VBBL.RelTol) (relative precision)
	printf("Magnification (relative precision at 1.e-1) = %lf\n", Mag); // Output should be 18.36.... (matching the required precision)
	// If you do not want to use relative precision anymore, just set
	VBBL.RelTol = 0; 
	// In practice, the calculation stops when the first of the two goals is reached 
	// (either absolute accuracy or relative precision).


//////////////////////////////////////////
// Limb darkening

	VBBL.a1 = 0.51; // Linear limb darkening coefficient. I(r)=I(0)(1-a1(1-\sqrt{1-r^2/\rho^2}))
	Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); // Call to the BinaryMag2
	printf("Magnification with limb darkened source = %lf\n", Mag);  // Output should be 18.27.....
	
	// Note that the limb darkening coefficient is set as a property of VBBL. 
	// It does not appear in the parameters of BinaryMag2.
	// If you want to go back to uniform source, you should set 
	VBBL.a1 = 0;
	// In general, a calculation including limb darkening is slower than for a uniform source,
	// since the calculation is repeated on more annuli.

	// After each calculation, the number of annuli used is available in VBBL.nannuli.
	// If you are probing extremely tiny caustics with very large sources, you may impose a minimum number of annuli.
	// Before your calculation, just set
	// VBBL.minannuli=2; //or whatever you need 
	// The total number of points used is available in VBBL.NPS
	printf("Annuli used: %d\nTotal number of points: %d\n", VBBL.nannuli, VBBL.NPS);

//////////////////////////////////////////
// Finally, let us give the binary magnification of a point-source

	Mag = VBBL.BinaryMag0(s, q, y1, y2); // Call to the BinaryMag0 function with these parameters
	printf("Magnification of a point-source = %lf\n", Mag);  // Output should be 18.18.....


//////////////////////////////////////////
// Implementation notes on BinaryMag2 (new in v2.0)

	// BinaryMag2 first calculates the point-source magnification through BinaryMag0
	// Then it evaluates the quadrupole correction. If it is too high, it goes for the full computation.
	// This is performed by calling BinaryMagDark. This function is also directly available to the user (as it was in v1.0).
	// Mag = VBBL.BinaryMagDark(s, q, y1, y2, Rs, a1, accuracy); // Note that the limb darkening and the accuracy are required parameters.
	
	// BinaryMagDark performs contour integration on several annuli. The number and radii of annuli is determined dynamically.
	// Each contour is treated as a uniform source by a call to the function BinaryMag (also directly available to the user).
	// Mag = VBBL.BinaryMag(s, q, y1, y2, Rs, accuracy); // Magnification of a uniform source.

	// The use of BinaryMag2 is strongly recommended, since it may save computational time by a factor ranging from 10 to 100.
	// Useless contour integrations are avoided if the required precision and accuracy are already met 
	// by the point-source computation.

//////////////////////////////////////////
// Multi-band observations

	// If you are analyzing multi-band observations, 
	// you might want the magnification for several values of a1 at the same time (one for each band).
	// In this case, you can use BinaryMagMultiDark.
	double a1_list[4] = { 0.2,0.3,0.51,0.6 }; // list of limb darkening coefficients
	double mag_list[4]; // array where to store the output
	VBBL.BinaryMagMultiDark(s, q, y1, y2, Rs, a1_list, 4, mag_list, 1.e-3);
	for (int i = 0; i < 4; i++) {
		printf("BinaryMagMultiDark at band %d: %lf\n", i, mag_list[i]);
	}


//////////////////////////////////////////
// Extended-source-point-lens

	VBBL.LoadESPLTable("ESPL.tbl"); // Load the pre-calculated table (you only have to do this once and for all)

	double u = 0.1; // Source-lens separation in Einstein radii.
	Mag = VBBL.ESPLMag2(u, Rs); // Call to the ESPLMag2 function with these parameters
	printf("\nMagnification of Extended-source-point-lens = %lf\n", Mag);  // Output should be 10.05.....

	// Implementation notes:
	// ESPLMag2 works the same way as BinaryMag2. It checks whether we are far enough to use the point-source approximation.
	// If necessary, it goes for the full computation by calling ESPLMagDark(double u, double rho, double a1);
	// ESPLMagDark divides the source disk in annuli. 
	// Each annulus is calculated by a call to ESPLMag(double u, double rho), which uses a pre-calculated table (extremely fast).


//////////////////////////////////////////
// Calculation of full light curves

	// These functions calculate the full light curve for a given set of parameters and an array of time stamps.
	// The output is stored in several arrays that are passed to the functions as parameters:
	// one array for magnifications, two arrays for source coordinates.
	
	double pr[15]; // Array of parameters
	double u0, t0, tE, alpha;

	u0 = -0.01; // Impact parameter
	alpha = 0.53; // Angle between a vector pointing to the left and the source velocity
	t0 = 7550.4; // Time of closest approach to the center of mass
	tE = 100.3; // Einstein time

	// Putting all parameters in the array
	pr[0] = log(s); // Note that log_s is used as an input parameter to BinaryLightCurve.
	pr[1] = log(q);
	pr[2] = u0;
	pr[3] = alpha;
	pr[4] = log(Rs);
	pr[5] = log(tE);
	pr[6] = t0;

	VBBL.Tol = 1.e-2; // Setting accuracy 
	VBBL.a1 = 0; // Setting limb darkening coefficient (0 for uniform source)

	// Now let us calculate the light curve on np points equally spaced between t0-3tE and t0+3tE:
	const int np = 601;
	double t_array[np], mag_array[np], y1_array[np], y2_array[np]; // Declare arrays for times, magnifications and source coordinates
	
	for (int i = 0; i < np; i++) {
		t_array[i] = t0 - 3 * tE + i*(6*tE/(np-1));
	}

	VBBL.BinaryLightCurve(pr, t_array, mag_array, y1_array, y2_array, np);
	printf("\nLight curve calculations\n");

	// If you want to see the output, uncomment these lines

	//for (int i = 0; i < np; i++) {
	//	printf("t: %lf Mag: %lf y1: %lf y2: %lf\n", t_array[i], mag_array[i],y1_array[i],y2_array[i]);
	//}

//////////////////////////////////////////
// Parallax calculation

	// First you need to initialize the event coordinates
	char coordinatefile[256] = "OB151212coords.txt"; // Text file containing the event coordinates in J2000.0
	 // The format should be HH:MM:SS.SSS +DD:MM:SS.SSS (see the sample file provided)
	
	char sattabledir[256] = "."; // Directory where satellite positions tables lie
	// Only important if you are using spacecraft observations (see below).

	VBBL.SetObjectCoordinates(coordinatefile, sattabledir);
	// The SetObjectCoordinates function sets the event coordinates in the VBBL library and 
	// loads the satellite position tables (if present).
	// You should call it only at the begginning of your analysis or when you move to another event.

	double pai1, pai2;
	pai1 = 0.3; // Parallax component parallel to the Earth acceleration (let us call it \alpha).
	pai2 = 0.13; // Parallax component orthogonal to the Earth acceleration (directed toward \alpha \wedge Object direction)

	pr[7] = pai1; // Include these two additional parameters in the parameter array
	pr[8] = pai2;

	// Let us re-calculate the light curve including parallax

	double mag_par_array[np]; // Declare a different array to store new magnifications.

	VBBL.BinaryLightCurveParallax(pr, t_array, mag_par_array, y1_array, y2_array, np);

	// Let us compare the magnification without and with parallax at one point.
	int ichosen = 150;
	printf("\nAt time %lf\nMmagnification without parallax: %lf.\nMagnification with parallax: %lf\n", t_array[ichosen], mag_array[ichosen], mag_par_array[ichosen]);
	// Output should be 1.12... without parallax and 1.05... with parallax.

	// In alternative, you can use the parallax North and East components.
	// If you prefer this coordinate system, set
	VBBL.parallaxsystem = 1;
	// Now pr[7] and pr[8] are the North and East components respectively.
	VBBL.BinaryLightCurveParallax(pr, t_array, mag_par_array, y1_array, y2_array, np);

	printf("Magnification with parallax with North/East components: %lf\n", mag_par_array[ichosen]); // Output should be 1.06....

	// The reference time for parallax is by default t0.
	// This means that the position of the source at t0 will be kept fixed whatever pai1 and pai2.
	// If you prefer to keep the position of the source fixed at a different time, set
	VBBL.t0_par_fixed = 1;
	// and choose the new t0_par to be kept fixed:
	VBBL.t0_par = 7530;

	VBBL.BinaryLightCurveParallax(pr, t_array, mag_par_array, y1_array, y2_array, np);
	printf("Magnification with parallax and t0_par= %lf: %lf\n", VBBL.t0_par,mag_par_array[ichosen]); // Output should be 1.07....


//////////////////////////////////////////
// Calculation of magnification as seen by a satellite

	// The satellite position table should be in the format generated by http://ssd.jpl.nasa.gov/horizons.cgi
	// In particular, we assume five columns:
	// JD
	// RA (degrees)
	// Dec (degrees)
	// Distance from Earth (AU)
	// Distance rate change (not really needed but included by default in Horizons).

	// See the satellite tables attached as examples.
	// The table file names should be "satellite*.txt" (with * replaced by a single character). 
	// These tables are sorted alphabetically and assigned a satellite number.

	// If you want the magnification as seen from satellite 1, then just set VBBL.satellite to 1 before the calculation.

	VBBL.satellite = 1;
	VBBL.BinaryLightCurveParallax(pr, t_array, mag_par_array, y1_array, y2_array, np);
	printf("Magnification as seen from satellite 1: %lf\n", mag_par_array[ichosen]); // Output should be 1.04....

	// If you want to return to the ground do not forget to set VBBL.satellite back to 0
	VBBL.satellite = 0;


//////////////////////////////////////////
// Other functions also implemented in VBBL:

	// PSPLLightCurve(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, int np);
	// Parameters are {log_u0, log_tE, t0}

	// PSPLLightCurveParallax(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, int np);
	// Parameters are {u0, log_tE, t0, pai1, pai2}

	// ESPLLightCurve(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, int np);
	// Parameters are {log_u0, log_tE, t0, logRs}

	// ESPLLightCurveParallax(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, int np);
	// Parameters are {u0, log_tE, t0, log_Rs, pai1, pai2}

	// BinaryLightCurveW(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, int np);
	// Parameters are {log_s, log_q, u0_c, alpha_0, log_Rs, log_tE, t0_c}
	// u0_c and t0_c are closest approach parameters with respect to the center of the caustic on the right in a wide
	// configuration. It can be useful in fitting.

	// BinaryLightCurveOrbital(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, double *sep_array, int np);
	// Parameters are {log_s, log_q, u0, alpha_0, log_Rs, log_tE, t0, pai1, pai2, w1, w2, w3}
	// Orbital parameters are in the hypothesis of circular motion (no eccentricity)
	// w1=(ds/dt)/s
	// w2=dalpha/dt
	// w3=(dsz/dt)/s
	// Note that an additional array sep_array is required to store the separation between the two components as a function 
	// of time.

	// BinSourceLightCurve(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, int np);
	// Parameters are {log_tE, log_fluxratio, u0_1, u0_2, t0_1, t0_2}

	// BinSourceLightCurveParallax(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, int np);
	// Parameters are {log_tE, log_fluxratio, u0_1, u0_2, t0_1, t0_2, pai1, pai2}

	// BinSourceLightCurveXallarap(double *parameters, double *t_array, double *mag_array, double *y1_array, double *y2_array, double *sep_array, int np);
	// Parameters are {log_tE, log_fluxratio, u0_1, u0_2, t0_1, t0_2, pai1, pai2, q, w1, w2, w3}
	// Note that the mass ratio q between the two sources is required to calculate orbital motion.
	// Orbital motion is assumed without eccentricity (see before).
	// The parameters u0_1, u0_2, t0_1, t0_2 specify the configuration at time t0 calculated as the closest approach of the
	// center of mass.

	// Old (v1) light curve functions calculating the magnitude at one specific time

	//double BinaryLightCurve(double *parameters, double t);
	//double BinaryLightCurveW(double *parameters, double t);
	//double BinaryLightCurveParallax(double *parameters, double t);
	//double BinaryLightCurveOrbital(double *parameters, double t);
	//double PSPLLightCurve(double *parameters, double t);
	//double PSPLLightCurveParallax(double *parameters, double t);
	//double ESPLLightCurve(double *parameters, double t);
	//double ESPLLightCurveParallax(double *parameters, double t);
	//double BinSourceLightCurve(double *parameters, double t);
	//double BinSourceLightCurveParallax(double *parameters, double t);
	//double BinSourceLightCurveXallarap(double *parameters, double t);

	// These functions work as the new ones but for a single time t at once. 
	// The magnification is returned through the function name.
	// The calculated source coordinate is available through VBBL.y_1 and VBBL.y_2.
	// The separation between the two lenses or sources in orbital motion is available through VBBL_av.

//////////////////////////////////////////
// Image contours

	// If you want the shapes of the contours of the images there are low-level versions of BinaryMag and BinaryMag0.
	// This examples calculates the magnification and stores the contours in Images. Then the cycle exports the contours in a ASCII file.
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

//////////////////////////////////////////
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


	//////////////////////////////////////////

	getchar();

	return 0;
}
