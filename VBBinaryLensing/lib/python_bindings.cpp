#include <pybind11/pybind11.h>
#include "VBBinaryLensingLibrary.h"

namespace py = pybind11;

PYBIND11_MODULE(VBBinaryLensing, m) {
    py::class_<VBBinaryLensing>(m, "VBBinaryLensing")
        .def(py::init())
        .def("LoadESPLTable", &VBBinaryLensing::LoadESPLTable,
                "Loads pre-calculated table needed for ESPL light curve computation")
        .def_readwrite("Tol", &VBBinaryLensing::Tol,
                "Absolute accuracy")
        .def_readwrite("RelTol", &VBBinaryLensing::RelTol,
                "Relative accuracy")
        .def_readwrite("a1", &VBBinaryLensing::a1,
                "Linear limb darkening coefficient. I(r)=I(0)(1-a1(1-\sqrt{1-r^2/\rho^2}))")
        .def("ESPLMag2", &VBBinaryLensing::ESPLMag2,
            py::return_value_policy::reference,
            "ESPLMag2 works the same way as BinaryMag2. It checks whether we are\
            far enough to use the point-source approximation and if necessary,\
            it goes for the full computation by calling\
            ESPLMagDark(double u, double rho, double a1)")
        .def("BinaryMag0",
            (double (VBBinaryLensing::*)(double, double, double, double)) &VBBinaryLensing::BinaryMag0,
            "Binary light curve computation assuming a point source")
        .def("BinaryMag2", &VBBinaryLensing::BinaryMag2,
            py::return_value_policy::reference,
            "Full binary light curve computation")     
        .def("BinaryMagDark", &VBBinaryLensing::BinaryMagDark,
            py::return_value_policy::reference,
            "Linear limb darkening")
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
