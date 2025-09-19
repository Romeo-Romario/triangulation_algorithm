#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "headers/figures.hpp"
#include "headers/my_functions.hpp"

namespace py = pybind11;

// Expose Entities and functions to python
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

    py::class_<Circle>(m, "Circle")
        .def(py::init<Point, double>())
        .def_readwrite("center", &Circle::center)
        .def_readwrite("radius", &Circle::radius)
        .def("calculate_circumscribed_circle", &Circle::calculate_circumscribed_circle)
        .def("__repr__", [](const Circle &c)
             { return "<Circle center: x= " + std::to_string(c.center.x) + " y= " + std::to_string(c.center.y) + " radius= " + std::to_string(c.radius) + ">"; });

    m.def("get_start_triangle", &initial_super_triangle, "Generate the starting triangle from a set of points");
    m.def("triangulation", &triangulation, "Runs the generate_triangles algorithm");
    m.def("generate_grid", &insert_grid, "Generate grid of additional vericies");
    m.def("get_circles", &get_circumscribed_circles, "Returns circumscribed circles of traingulation");
}
