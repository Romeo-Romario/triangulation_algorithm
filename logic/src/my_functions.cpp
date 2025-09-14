#include "../headers/my_functions.hpp"

Triangle initial_super_triangle(const std::vector<Point> &points)
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

std::vector<Triangle> triangulation(const std::vector<Point> &points)
{
    Triangle super_triangle = initial_super_triangle(points);

    std::vector<Triangle> triangulation_res = {super_triangle};

    for (const auto &point : points)
    {
        std::vector<Triangle> bad_triangles = {};

        for (const auto &triangle : triangulation_res)
        {
            // if ()
            continue;
        }
    }
    return {};
}