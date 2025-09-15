#pragma once
#include <vector>
#include <algorithm>
#include "figures.hpp"

Triangle initial_super_triangle(const std::vector<Point> &points);
bool check_edge(const std::vector<Triangle> &all_triangels, const int &current_edge_triangle_index, const Edge &current_edge);
std::vector<Triangle> clean_triangulation(const std::vector<Triangle> &triangulation_res, const std::vector<int> &remove_indexes);
std::vector<Triangle> generate_triangles(const std::vector<Point> &points);
std::vector<Triangle> check_triangulation(const std::vector<Triangle> &traingulation);
std::vector<Triangle> triangulation(const std::vector<Point> &points);