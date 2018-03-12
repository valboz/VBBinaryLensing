#include <pybind11/pybind11.h>
#include "VBBinaryLensingLibrary.h"

namespace py = pybind11;

PYBIND11_MODULE(VBBinaryLensingLibrary, m) {
    py::class_<VBBinaryLensing>(m, "VBBinaryLensing")
        .def(py::init())
        .def("LoadESPLTable", &VBBinaryLensing::LoadESPLTable)
        .def_readwrite("Tol", &VBBinaryLensing::Tol)
        .def_readwrite("RelTol", &VBBinaryLensing::RelTol)
        .def_readwrite("a1", &VBBinaryLensing::a1)
        .def("ESPLMag2", &VBBinaryLensing::ESPLMag2,
            py::return_value_policy::reference)
        .def("BinaryMag0",
            (double (VBBinaryLensing::*)(double, double, double, double)) &VBBinaryLensing::BinaryMag0)
        .def("BinaryMag2", &VBBinaryLensing::BinaryMag2,
            py::return_value_policy::reference)
        .def("PlotCrit", &VBBinaryLensing::PlotCrit,
            py::return_value_policy::reference);
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
