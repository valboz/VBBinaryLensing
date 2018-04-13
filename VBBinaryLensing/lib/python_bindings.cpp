#include <pybind11/pybind11.h>
#include "VBBinaryLensingLibrary.h"

namespace py = pybind11;

PYBIND11_MODULE(VBBinaryLensing, m) {
    py::class_<VBBinaryLensing>(m, "VBBinaryLensing")
        .def(py::init())

        // Settings
        .def("LoadESPLTable", &VBBinaryLensing::LoadESPLTable,
                "Loads pre-calculated table needed for ESPL light curve computation")
        .def_readwrite("Tol", &VBBinaryLensing::Tol,
                "Absolute accuracy")
        .def_readwrite("RelTol", &VBBinaryLensing::RelTol,
                "Relative accuracy")
        .def_readwrite("a1", &VBBinaryLensing::a1,
                "Linear limb darkening coefficient. I(r)=I(0)(1-a1(1-\sqrt{1-r^2/\rho^2}))")
        .def_readwrite("minannuli", &VBBinaryLensing::minannuli,
                "Minimum number of annuli to calculate for limb darkening.")
         .def_readwrite("parallaxsystem", &VBBinaryLensing::parallaxsystem,
                "0 for parallel-perpendicular, 1 for North-Eeast.")
        .def_readwrite("t0_par_fixed", &VBBinaryLensing::t0_par_fixed,
                "Set to 1 if you want to specify a constant t_{0,par}.")
        .def_readwrite("t0_par", &VBBinaryLensing::t0_par,
                "Reference time for parallax t_{0,par}. Only used if t0_par_fixed=1.")
        .def_readwrite("satellite", &VBBinaryLensing::satellite,
                "Specifies the satellite number for the next calculation \
                (0 for observations from the ground).")

        // Maginfication calculations
        .def("ESPLMag", &VBBinaryLensing::ESPLMag,
            py::return_value_policy::reference,
            "Magnification of a uniform brightness source by a single lens.\
            This uses the pre-calculated table.")
        .def("ESPLMag2", &VBBinaryLensing::ESPLMag2,
            py::return_value_policy::reference,
            "ESPLMag2 works the same way as BinaryMag2. It checks whether we are\
            far enough to use the point-source approximation and if necessary,\
            it goes for the full computation by calling\
            ESPLMagDark(double u, double rho, double a1)")
        .def("ESPLMagDark", &VBBinaryLensing::ESPLMagDark,
            py::return_value_policy::reference,
            "Magnification of a limb-darkened source by a single lens.")
        .def("BinaryMag0",
            (double (VBBinaryLensing::*)(double, double, double, double)) 
            &VBBinaryLensing::BinaryMag0,
            py::return_value_policy::reference,
            "Magnification of a point-source by a binary lens.")
        .def("BinaryMag", 
            (double (VBBinaryLensing::*)(double, double, double, double, double, double))
            &VBBinaryLensing::BinaryMag,
            py::return_value_policy::reference,
            "Full binary light curve computation.")     
        .def("BinaryMagDark", &VBBinaryLensing::BinaryMagDark,
            py::return_value_policy::reference,
            "Magnification of a limb-darkened source by a binary lens.")
        .def("BinaryMagMultiDark", &VBBinaryLensing::BinaryMagMultiDark,
            py::return_value_policy::reference,
            "Magnification of a limb-darkened source by a binary lens in \
            different filters with different limb darkening coefficients. ")
        .def("BinaryMag2", &VBBinaryLensing::BinaryMag2,
            py::return_value_policy::reference,
            "Magnification of a generic source by a binary lens. New in\
            v2.0, implements tests described in paper.")     

        // Light curve calculations
        .def("PSPLLightCurve",
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::PSPLLightCurve,
            py::return_value_policy::reference,
            "PSPL light curve for a given set of parameters. This and all light curve\
            functions are available for a single epoch or for a full array of \
            observation epochs.")
        .def("PSPLLightCurveParallax", 
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::PSPLLightCurveParallax,
            py::return_value_policy::reference,
            "PSPL light curve including parallax.")
        .def("SetObjectCoordinates", &VBBinaryLensing::SetObjectCoordinates,
            py::return_value_policy::reference,
            "Sets the astronomical coordinates of the microlensing target \
            and specifies the path where to look for the position tables\
            of the satellites (if any).")
        .def("ESPLLightCurve", 
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::ESPLLightCurve,
            py::return_value_policy::reference,
            "ESPL light curve, uses the ESPLMag2 function..")
        .def("ESPLLightCurveParallax", 
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::ESPLLightCurveParallax,
            py::return_value_policy::reference,
            "ESPL light curve including parallax.")
        .def("BinaryLightCurve", 
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::BinaryLightCurve,
            py::return_value_policy::reference,
            "Static binary lens light curve for a given set of parameters. \
            This uses the BinaryMag2 function.")
        .def("BinaryLightCurveW", 
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::BinaryLightCurveW,
            py::return_value_policy::reference,
            "Static binary lens light curve for a given set of parameters \
            using the center of the caustic of the lens on the right as a\
            reference point for the trajectory.")
        .def("BinaryLightCurveParallax", 
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::BinaryLightCurveParallax,
            py::return_value_policy::reference,
            "Binary lens light curve including parallax for a given set of\
            parameters.")
        .def("BinaryLightCurveOrbital", 
            (void (VBBinaryLensing::*)(double *, double *, double *, double *, double *, double *, int))
            &VBBinaryLensing::BinaryLightCurveOrbital,
            py::return_value_policy::reference,
            "Binary lens light curve including parallax for a single lens\
            and a binary source including parallax and circular orbital \
            motion.")

        // Other functions
        .def("PlotCrit", &VBBinaryLensing::PlotCrit,
            py::return_value_policy::reference,
            "Returns critical curves and caustic curves.");

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
