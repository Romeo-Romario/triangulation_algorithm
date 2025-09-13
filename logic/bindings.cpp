#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "headers/figures.hpp"
#include "headers/my_functions.hpp"

namespace py = pybind11;

// Expose Point and Triangle to Python
PYBIND11_MODULE(geometry, m)
{
    py::class_<Point>(m, "Point")
        .def(py::init<double, double>())
        .def_readwrite("x", &Point::x)
        .def_readwrite("y", &Point::y)
        .def("__repr__", [](const Point &p)
             { return "<Point x=" + std::to_string(p.x) +
                      " y=" + std::to_string(p.y) + ">"; });

    py::class_<Triangle>(m, "Triangle")
        .def(py::init<Point, Point, Point>())
        .def_readwrite("a", &Triangle::a)
        .def_readwrite("b", &Triangle::b)
        .def_readwrite("c", &Triangle::c)
        .def("area", &Triangle::area)
        .def("perimeter", &Triangle::perimeter)
        .def("isValid", &Triangle::isValid)
        .def("__repr__", [](const Triangle &t)
             { return "<Triangle area=" + std::to_string(t.area()) + ">"; });

    m.def("get_start_triangle", &initial_super_triangle,
          "Generate the starting triangle from a set of points");
}
