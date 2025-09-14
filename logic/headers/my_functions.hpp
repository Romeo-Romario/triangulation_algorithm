#pragma once
#include <vector>
#include "figures.hpp"

Triangle initial_super_triangle(const std::vector<Point> &points);
std::vector<Triangle> triangulation(const std::vector<Point> &points);