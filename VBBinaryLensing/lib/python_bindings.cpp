#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "VBBinaryLensingLibrary.h"
#include <string>
#include <pybind11/functional.h>




namespace py = pybind11;

// Declaration of an instance to VBBinaryLensing class. 
VBBinaryLensing VBBL;

PYBIND11_MODULE(VBBinaryLensing, m) {
    py::options options;
    options.disable_function_signatures();
    py::class_<VBBinaryLensing> vbb(m, "VBBinaryLensing");
        vbb.def(py::init());
        // Settings
       
        vbb.def_readwrite("Tol", &VBBinaryLensing::Tol,
                "Absolute accuracy goal.");
        vbb.def_readwrite("RelTol", &VBBinaryLensing::RelTol,
                "Relative precision goal.");
        vbb.def_readwrite("a1", &VBBinaryLensing::a1,
                "Linear limb darkening coefficient. I(r)=I(0)(1-a1(1-\sqrt{1-r^2/\rho^2}))");
        vbb.def_readwrite("a2", &VBBinaryLensing::a2,
                "Secontd limb darkening coefficient.");
        vbb.def_readwrite("NPcrit", &VBBinaryLensing::NPcrit,
            "Number of points in critical curves or caustics.");
        vbb.def_readwrite("minannuli", &VBBinaryLensing::minannuli,
                "Minimum number of annuli to calculate for limb darkening.");
        vbb.def_readwrite("parallaxsystem", &VBBinaryLensing::parallaxsystem,
                "0 for parallel-perpendicular, 1 for North-Eeast.");
        vbb.def_readwrite("t0_par_fixed", &VBBinaryLensing::t0_par_fixed,
                "Set to 1 if you want to specify a constant t_{0,par}.");
        vbb.def_readwrite("t0_par", &VBBinaryLensing::t0_par,
                "Reference time for parallax t_{0,par}. Only used if t0_par_fixed=1.");
        vbb.def_readwrite("satellite", &VBBinaryLensing::satellite,
                "Specifies the satellite number for the next calculation \
                (0 for observations from the ground);.");
        vbb.def_readwrite("astrometry", &VBBinaryLensing::astrometry,
                "Unlock astrometry centroid calculation.");
        vbb.def_readwrite("astrox1", &VBBinaryLensing::astrox1,
                "The x component of the light centroid.");
        vbb.def_readwrite("astrox2", &VBBinaryLensing::astrox2,
                "The y component of the light centroid.");
        vbb.def_readwrite("mass_luminosity_exponent", &VBBinaryLensing::mass_luminosity_exponent,
            "Exponent for the mass-luminosity relation: L = M^q; default value is q=4.0");
        vbb.def_readwrite("mass_radius_exponent", &VBBinaryLensing::mass_radius_exponent,
            "Exponent for the mass-radius relation: R = M^q; default value is q=0.89");

        vbb.def("LoadESPLTable", &VBBinaryLensing::LoadESPLTable,
            """Loads a pre calculated binary table for extended source calculation.""");
        // Maginfication calculations
        vbb.def("ESPLMag", &VBBinaryLensing::ESPLMag,
            py::return_value_policy::reference,
            R"mydelimiter(
            Extended Source Point Lens magnification calculation.

            Magnification of a uniform brightness-source by a single lens.
            This uses the pre-calculated table which has to be loaded before
            calling this function.

            Parameters
            ----------
            u : float 
                Distance of source from the center of the lens.
            rho : float 
                Source radius in units of the Einstein radius of the lens.

            Returns
            -------
            float
                Magnification.
            )mydelimiter");
       vbb.def("ESPLMag2", &VBBinaryLensing::ESPLMag2,
            R"mydelimiter(
            Extended Source Point Lens magnification calculation v2.0.

            ESPLMag2 works the same way as BinaryMag2. It checks whether we are
            far enough to use the point-source approximation and if necessary,
            it goes for the full computation by calling ESPLMagDark
            
            Parameters
            ----------
            u : float 
                Distance of source from the center of the lens.
            rho : float 
                Source radius in units of the Einstein radius of the lens.

            Returns
            -------
            float
                Magnification.
            )mydelimiter");
        vbb.def("ESPLMagDark", &VBBinaryLensing::ESPLMagDark,
            py::return_value_policy::reference,
            R"mydelimiter(
            Extended Source Point Lens magnification calculation v2.0. 
            including limb darkening.

            Parameters
            ----------
            u : float 
                Distance of source from the center of the lens.
            rho : float 
                Source radius in units of the Einstein radius of the lens.
            a1 : float 
                Linear limb darkening coefficient. 

            Returns
            -------
            float
                Magnification.
            )mydelimiter");
        vbb.def("BinaryMag0",
            (double (VBBinaryLensing::*)(double, double, double, double)) 
            &VBBinaryLensing::BinaryMag0,
            py::return_value_policy::reference,
            R"mydelimiter(
            Magnification of a point-source by a binary lens.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 s.t. m1<m2 
            y1 : float 
                x-position of the source in the source plane.
            y2 : float 
                y-position of the source in the source plane.

            Returns
            -------
            float
                Magnification.
            )mydelimiter");

        vbb.def("BinaryMag", 
            (double (VBBinaryLensing::*)(double, double, double, double, double, double))
            &VBBinaryLensing::BinaryMag,
            py::return_value_policy::reference,
            R"mydelimiter(
            Magnification of a uniform brightness finite source 
            by a binary lens.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 s.t. m1<m2 
            y1 : float 
                x-position of the source in the source plane.
            y2 : float 
                y-position of the source in the source plane.
            rho : float 
                Source angular radius in units of the Einstein radius 
                corresponding to the total mass.
            accuracy : float 
                Absolute accuracy goal for the magnification calculation. 

            Returns
            -------
            float
                Magnification.
            )mydelimiter");
        vbb.def("BinaryMagDark", 
            &VBBinaryLensing::BinaryMagDark,
            py::return_value_policy::reference,
            R"mydelimiter(
            Magnification of a limb-darkened finite source 
            by a binary lens.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 s.t. m1<m2 
            y1 : float 
                x-position of the source in the source plane.
            y2 : float 
                y-position of the source in the source plane.
            rho : float 
                Source angular radius in units of the Einstein radius 
                corresponding to the total mass.
            a1 : float 
                Source angular radius in units of the Einstein radius 
                corresponding to the total mass.

            accuracy : float 
                Absolute accuracy goal for the magnification calculation. 

            Returns
            -------
            float
                Magnification.
            )mydelimiter");
        vbb.def("BinaryMagMultiDark", 
            (void (VBBinaryLensing::*)(double, double, double, double, double, double *, int, double *, double)) 
            &VBBinaryLensing::BinaryMagMultiDark,
            py::return_value_policy::reference,
            R"mydelimiter(
            Magnification of a limb-darkened source by a binary lens in \
            different filters with different limb darkening coefficients.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 s.t. m1<m2 
            y1 : float 
                x-position of the source in the source plane.
            y2 : float 
                y-position of the source in the source plane.
            rho : float 
                Source angular radius in units of the Einstein radius 
                corresponding to the total mass.
            a1_list : ndarray 
                Array of linear limb darkening coefficients.    
            n_filters : int 
                Number of filters. 
            mag_list : ndarray 
                Array of magnifications to be calculated by the function. 
            accuracy : float 
                Absolute accuracy goal for the magnification calculation. 

            Returns
            -------
            void
            )mydelimiter");

        vbb.def("BinaryMag2", &VBBinaryLensing::BinaryMag2,
            py::return_value_policy::reference,
            R"mydelimiter(
            Magnification of a uniform brightness finite source 
            by a binary lens. New in v2.0, implements test described
            in VBBinaryLensing 2.0 paper.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 s.t. m1<m2 
            y1 : float 
                x-position of the source in the source plane.
            y2 : float 
                y-position of the source in the source plane.
            rho : float 
                Source angular radius in units of the Einstein radius 
                corresponding to the total mass.
            accuracy : float 
                Absolute accuracy goal for the magnification calculation. 

            Returns
            -------
            float
                Magnification.
            )mydelimiter");

        vbb.def("SetObjectCoordinates", (void (VBBinaryLensing::*)(char *, char *)) &VBBinaryLensing::SetObjectCoordinates,
            R"mydelimiter(
            Sets the astronomical coordinates of the microlensing target.            
            
            Parameters
            ----------
            CoordinateString : string 
                Format \"hr:mn:sc +deg:pr:sc\".
            )mydelimiter");

        vbb.def("SetObjectCoordinates", (void (VBBinaryLensing::*)(char*)) &VBBinaryLensing::SetObjectCoordinates,
            R"mydelimiter(
            Sets the astronomical coordinates of the microlensing target and 
            specifies the path where to look for the position tables 
            of the satellites (if any).            
            
            Parameters
            ----------
            modelfile : string 
                Output filename.
            sattabledir : string 
                Name of the directory containing the position tables of the satellites. 
            )mydelimiter");

        // Light curve calculations
        vbb.def("PSPLLightCurve",
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.PSPLLightCurve(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
            },
            R"mydelimiter(
            PSPL light curve for a full array of observations.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_u0, log_tE, t0].
            times : list[float] 
                Array of times at which the magnification is calculated.

            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");

        vbb.def("PSPLLightCurveParallax", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.PSPLLightCurveParallax(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
           },
            R"mydelimiter(
            PSPL light curve for a full array of observations including parallax.

            Parameters
            ----------
            params : list[float]
                List of parameters [u0, log_tE, t0, pai1, pai2] where pai1 and 
                pai2 are the components of parallax parallel and orthogonal 
                to the Earth's acceleration.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");

        vbb.def("ESPLLightCurve", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.ESPLLightCurve(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
            },
            R"mydelimiter(
            ESPL light curve for a full array of observations.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_u0, log_tE, t0, log_rho] 
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");
        vbb.def("ESPLLightCurveParallax", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.ESPLLightCurveParallax(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
             },
            R"mydelimiter(
            ESPL light curve for a full array of observations including parallax.

            Parameters
            ----------
            params : list[float]
                List of parameters [u0, log_tE, t0, pai1, pai2] where pai1 and pai2 
                are the two components of the parallax.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");
        vbb.def("BinaryLightCurve", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.BinaryLightCurve(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
            },
            R"mydelimiter(
            Static binary lens light curve for a given set of parameters.
            Uses the BinaryMag2 function.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_s, log_q, u0, alpha, log_rho, log_tE, t0]
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");

        vbb.def("BinaryLightCurveW", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.BinaryLightCurveW(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
            },
            R"mydelimiter(
            Static binary lens light curve for a given set of parameters 
            using the center of the caustic of the lens on the right as 
            a reference point for the trajectory.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_s, log_q, u0_c, alpha, log_rho, log_tE, t0_c]
                where u0_c and t0_c are defined with respect to the center of the caustic.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");
        vbb.def("BinaryLightCurveParallax", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.BinaryLightCurveParallax(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
             },
            R"mydelimiter(
            Static binary lens light curve for a given set of parameters including parallax.
            Uses the BinaryMag2 function.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_s, log_q, u0, alpha, log_rho, log_tE, t0, pai1, pai2]
                where pai1 and pai2 are the components of parallax parallel and orthogonal to the
                Earth's acceleration.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");

        vbb.def("BinaryLightCurveOrbital", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                std::vector<double> separations(times.size());
                self.BinaryLightCurveOrbital(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), separations.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s, separations };
                return results;
            },
            R"mydelimiter(
            Static binary lens light curve for a given set of parameters including parallax.
            Uses the BinaryMag2 function.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_s, log_q, u0, alpha_0, log_rho, log_tE, 
                t0, pai1, pai2, w1, w2, w3] where pai1 and pai2 are the 
                components of parallax parallel and orthogonal to the Earth's 
                acceleration. w1, w2 and w3 are the orbital parameters (assuming
                circular motion), defined as w1=(ds/dt)/s, w2=dalpha/dt, w3=(dsz/dt)/s.
            times : list[float] 
                Array of times at which the magnification is calculated.

            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array, separation-between-lenses array]
            )mydelimiter");
            
        vbb.def("BinaryLightCurveKepler", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                std::vector<double> separations(times.size());
                self.BinaryLightCurveKepler(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), separations.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s, separations };
                return results;
            },
            R"mydelimiter(
             binary lens light curve for a given set of parameters including keplerian orbital motion.
            Uses the BinaryMag2 function.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_s, log_q, u0, alpha_0, log_rho, log_tE, 
                t0, pai1, pai2, w1, w2, w3] where pai1 and pai2 are the 
                components of parallax parallel and orthogonal to the Earth's 
                acceleration. w1, w2 and w3 are the orbital parameters (assuming
                circular motion), defined as w1=(ds/dt)/s, w2=dalpha/dt, w3=(dsz/dt)/s.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array, separation-between-lenses array]
            )mydelimiter");

            vbb.def("BinSourceLightCurve", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.BinSourceLightCurve(params.data(), times.data(), mags.data(),
                        y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
            },
            R"mydelimiter(
            Light curve for a single lens and a binary source. Sources are 
            treated as point-like.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_tE, log_fluxratio, u0_1, u0_2, t0_1, t0_2]
            times : list[float] 
                Array of times at which the magnification is calculated.
 
           Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");

            vbb.def("BinSourceLightCurveParallax", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                self.BinSourceLightCurveParallax(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s };
                return results;
            },
            R"mydelimiter(
            Light curve for a single lens and a binary source including parallax.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_tE, log_fluxratio, u0_1, u0_2, t0_1, t0_2, pai1, pai2}
                where pai1 and pai2 are the components of parallax parallel and orthogonal to the
                Earth's acceleration.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");

            vbb.def("BinSourceSingleLensXallarap",
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s1(times.size());
                std::vector<double> y2s1(times.size());
                std::vector<double> y1s2(times.size());
                std::vector<double> y2s2(times.size());
                self.BinSourceSingleLensXallarap(params.data(), times.data(), mags.data(),
                    y1s1.data(), y2s1.data(), y1s2.data(), y2s2.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s1,y2s1,y1s2,y2s2 };
                return results;
            },
            R"mydelimiter(
            Binary source Single Lens Xallarap light curve.

            Parameters
            ----------
            params : list[float] 	
                List of parameters [log_tE, log_qs, u0, t0, xi1, xi2, 
                rho, omega, inc, phi, w2, w3] where xi1 and xi2 are the 
                components of xallarap parallel and orthogonal to the  
                seperation between the sources.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float],list[float],list[float]] 
                [Magnification array, source 1 position y1 array, source 1 position y2 array, source 2 position y1 array, source 2 position y2 array]
             )mydelimiter");

            vbb.def("BinSourceExtLightCurve",
                [](VBBinaryLensing& self, std::vector<double> params, std::vector<double> times)
                {
                    std::vector<double> mags(times.size());
                    std::vector<double> y1s(times.size());
                    std::vector<double> y2s(times.size());
                    self.BinSourceExtLightCurve(params.data(), times.data(), mags.data(),
                        y1s.data(), y2s.data(), times.size());
                    std::vector< std::vector<double> > results{ mags,y1s,y2s };
                    return results;
                },
                R"mydelimiter(
            Light curve for a single lens and a binary source. Sources are 
            treated as point-like.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_tE, log_fluxratio, u0_1, u0_2, t0_1, t0_2, rho]
            times : list[float] 
                Array of times at which the magnification is calculated.
 
           Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, source position y1 array, source position y2 array]
            )mydelimiter");


            vbb.def("BinSourceBinLensXallarap",
                [](VBBinaryLensing& self, std::vector<double> params, std::vector<double> times)
                {
                    std::vector<double> mags(times.size());
                    std::vector<double> y1s(times.size());
                    std::vector<double> y2s(times.size());
                    self.BinSourceBinLensXallarap(params.data(), times.data(), mags.data(),
                        y1s.data(), y2s.data(), times.size());
                    std::vector< std::vector<double> > results{ mags,y1s,y2s };
                    return results;
                },
                R"mydelimiter(
            Binary source Single Lens Xallarap light curve.

            Parameters
            ----------
            params : list[float] 	
                List of parameters [log_s, log_q, u0, alpha, log_rho, log_tE, t0, xi1, xi2, 
                omega, inc, phi, log_qs] where xi1 and xi2 are the 
                components of xallarap parallel and orthogonal to the  
                separation between the sources.
            times : list[float] 
                Array of times at which the magnification is calculated.
  
            Returns
            -------
            results: list[list[float],list[float],list[float]] 
                [Magnification array, y1 array, y2 array]
            )mydelimiter");


            vbb.def("BinSourceLightCurveXallarap", 
            [](VBBinaryLensing &self, std::vector<double> params, std::vector<double> times)
            {
                std::vector<double> mags(times.size());
                std::vector<double> y1s(times.size());
                std::vector<double> y2s(times.size());
                std::vector<double> separations(times.size());
                self.BinSourceLightCurveXallarap(params.data(), times.data(), mags.data(),
                    y1s.data(), y2s.data(), separations.data(), times.size());
                std::vector< std::vector<double> > results{ mags,y1s,y2s, separations };
                return results;
            },
            R"mydelimiter(
            Binary source light curve.

            Note that the mass ratio q between the two sources is required 
            to calculate orbital motion. Orbital motion is assumed without 
            eccentricity (see before). The parameters u0_1, u0_2, t0_1, 
            t0_2 specify the configuration at time t0 calculated as the 
            closest approach of the center of mass.

            Parameters
            ----------
            params : list[float]
                List of parameters [log_tE, log_fluxratio, u0_1, u0_2, t0_1, t0_2, 
                pai1, pai2, q, w1, w2, w3] where pai1 and pai2 are the 
                components of parallax parallel and orthogonal to the Earth's 
                acceleration. w1, w2 and w3 are the orbital parameters (assuming
                circular motion), defined as w1=(ds/dt)/s, w2=dalpha/dt, w3=(dsz/dt)/s.
            times : list[float] 
                Array of times at which the magnification is calculated.
 
            Returns
            -------
            results: list[list[float],list[float],list[float],list[float]] 
                [Magnification array, y1 array, y2 array, separation-between-lenses array]
            )mydelimiter");



        // Other functions
        vbb.def("PlotCrit", &VBBinaryLensing::PlotCrit,
            py::return_value_policy::reference,
            R"mydelimiter(
            Critical curves and caustics for given separation and mass ratio.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 such that m1<m2 

            Returns
            -------
            solutions : _sols
                List of critical curves and caustics.
            )mydelimiter");

        vbb.def("Caustics",
            [](VBBinaryLensing& self, double s, double q)
            {
                _sols *critcau;
        
                critcau = self.PlotCrit(s,q);
                int ncaus = critcau->length / 2;
                std::list <std::vector<std::vector<double>>> caustics{};
                _curve* c = critcau->first;
                for (int i = 0; i < ncaus; i++) c = c->next;
                for (int i = 0; i < ncaus; i++) {
                    std::vector<double> y(c->length);
                    std::vector<std::vector<double>> cau(2, y);
                    _point* p = c->first;
                    for (int j = 0; j < c->length; j++) {
                        cau[0][j] = p->x1;
                        cau[1][j] = p->x2;
                        p = p->next;
                    }
                    caustics.push_back(cau);
                    c = c->next;
                }
                delete critcau;
                return caustics;
            },
            R"mydelimiter(
            Caustics for given separation and mass ratio.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 such that m1<m2 

            Returns
            -------
            solutions : _sols
                List of caustics.
            )mydelimiter");

        vbb.def("CriticalCurves",
            [](VBBinaryLensing& self, double s, double q)
            {
                _sols* critcau;

                critcau = self.PlotCrit(s, q);
                int ncrits = critcau->length / 2;
                std::list <std::vector<std::vector<double>>> criticalcurves{};
                _curve* c = critcau->first;
                for (int i = 0; i < ncrits; i++) {
                    std::vector<double> y(c->length);
                    std::vector<std::vector<double>> crit(2, y);
                    _point* p = c->first;
                    for (int j = 0; j < c->length; j++) {
                        crit[0][j] = p->x1;
                        crit[1][j] = p->x2;
                        p = p->next;
                    }
                    criticalcurves.push_back(crit);
                    c = c->next;
                }
                delete critcau;
                return criticalcurves;
            },
            R"mydelimiter(
            Critical curves for given separation and mass ratio.

            Parameters
            ----------
            s : float 
                The projected separation of the binary lens in units of the 
                Einstein radius corresponding to the total mass.
            q : float 
                Binary lens mass fraction q = m1/m2 such that m1<m2 

            Returns
            -------
            solutions : _sols
                List of critical curves.
            )mydelimiter");

        // Limb darkening
         
        //vbb.def("SetLDprofile", 
        //    &VBBinaryLensing::SetLDprofile,
        //    "User choice of LD profile");
  
         //vbb.def("SetUserLDprofile", 
         //  []( VBBinaryLensing &self, py::function f) {
         //   self.SetUserLDprofile(f,1000);
         //   });

     
       
        
        
    //LDlinear, LDquadratic, LDsquareroot, LDlog, LDuser
    py::enum_<VBBinaryLensing::LDprofiles>(vbb, "LDprofiles")
        .value("LDlinear", VBBinaryLensing::LDprofiles::LDlinear)
        .value("LDquadratic", VBBinaryLensing::LDprofiles::LDquadratic)
        .value("LDsquareroot", VBBinaryLensing::LDprofiles::LDsquareroot)
        .value("LDlog", VBBinaryLensing::LDprofiles::LDlog)
        .value("LDuser", VBBinaryLensing::LDprofiles::LDuser)
        .export_values();
   


    py::class_<_theta>(m, "_theta")
        .def(py::init<double>()); //constructor 

    py::class_<_point>(m, "_point")
        .def(py::init<double, double, _theta *>()) 
        .def_readwrite("next", &_point::next)
        .def_readwrite("prev", &_point::prev)
        .def_readonly("x1", &_point::x1)
        .def_readonly("x2", &_point::x2);

    py::class_<_curve>(m, "_curve")
        .def(py::init<_point*>()) //constructor 1
        .def(py::init()) //constructor 2
        .def_readwrite("first", &_curve::first)
        .def_readwrite("last", &_curve::last)
        .def_readwrite("next", &_curve::next)
        .def_readwrite("prev", &_curve::prev);

    py::class_<_sols>(m, "_sols")
        .def(py::init()) //constructor
        .def_readwrite("first", &_sols::first)
        .def_readwrite("last", &_sols::last);
}
