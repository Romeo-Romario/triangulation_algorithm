#pragma once
#include <iostream>
#include <vector>
#include "headers/figures.hpp"
#include <cmath>

using std::vector;

double distance(const Point &p1, const Point &p2)
{
    return std::sqrt(std::pow((p2.x - p1.x), 2) + std::pow((p2.y - p1.y), 2));
}

Triangle initial_super_triangle(const vector<Point> &points)
{
    Point top, left, right, bottom;

    // Values for maximum and minimum per x,y values
    double left_edge{points[0].x}, right_edge{points[0].x},
        bottom_edge{points[0].y}, top_edge{points[0].y};

    for (const auto &point : points)
    {
        if (left_edge > point.x)
        {
            left_edge = point.x;
            left = point;
        }
        if (right_edge < point.x)
        {
            right_edge = point.x;
            right = point;
        }
        if (bottom_edge > point.y)
        {
            bottom_edge = point.y;
            bottom = point;
        }
        if (top_edge < point.y)
        {
            top_edge = point.y;
            top = point;
        }
    }

    double width = distance(left, right);
    double height = distance(bottom, top);

    // Build triangle
    return Triangle(
        Point(left_edge - width, bottom_edge - height),            // triangle_left_bottom
        Point(right_edge + width, bottom_edge - height),           // triangle_right_bottom
        Point((left_edge + right_edge) / 2, top_edge + 2 * height) // triange_top
    );
}

vector<Triangle> triangulation(const vector<Point> &points)
{
    Triangle super_triangle = initial_super_triangle(points);

    vector<Triangle> triangulation_res = {super_triangle};

    for (const auto &point : points)
    {
        vector<Triangle> bad_triangles = {};

        for (const auto &triangle : triangulation_res)
        {
            if ()
        }
    }
}