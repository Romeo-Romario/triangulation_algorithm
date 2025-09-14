#include "../headers/my_functions.hpp"

using std::cout;
using std::endl;

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

bool check_edge(const std::vector<Triangle> &all_triangels,
                const int &current_edge_triangle_index,
                const Edge &current_edge)
{
    for (int triangle_index = 0; triangle_index < all_triangels.size(); triangle_index++)
    {
        if (triangle_index == current_edge_triangle_index)
        {
            continue;
        }

        for (const auto &edge : all_triangels[triangle_index].get_edges())
        {
            if (edge == current_edge)
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<Triangle> clean_triangulation_res(const std::vector<Triangle> &triangulation_res, const std::vector<int> &remove_indexes)
{
    std::vector<Triangle> result = triangulation_res;

    std::vector<int> sorted_remove_indexes = remove_indexes;
    std::sort(sorted_remove_indexes.rbegin(), sorted_remove_indexes.rend());

    for (int idx : sorted_remove_indexes)
    {
        result.erase(result.begin() + idx);
    }
    return result;
}

std::vector<Triangle> triangulation(const std::vector<Point> &points)
{
    Triangle super_triangle = initial_super_triangle(points);
    std::vector<Triangle> triangulation_res;
    std::vector<Triangle> triangulation_full = {super_triangle};
    // 3.0
    Circle circumscribed_circle;
    for (const auto &point : points)
    {
        std::vector<Triangle> bad_triangles = {};

        // 3.1
        for (const auto &triangle : triangulation_full)
        {
            circumscribed_circle = Circle::calculate_circumscribed_circle(triangle);
            if (check_if_point_inside_circle(point, circumscribed_circle))
            {
                bad_triangles.push_back(triangle);
            }
        }

        // 3.2
        std::vector<Edge> polygon = {};
        for (int triangle_index = 0; triangle_index < bad_triangles.size(); triangle_index++)
        {
            for (const auto &edge : bad_triangles[triangle_index].get_edges())
            {
                if (check_edge(bad_triangles, triangle_index, edge))
                {
                    polygon.push_back(edge);
                }
            }
        }

        // 3.3
        for (const auto &edge : polygon)
        {
            Triangle new_triangle(edge.a, edge.b, point);
            triangulation_full.push_back(new_triangle);
        }
    }

    std::vector<int> bad_triangles_indexes = {};
    for (int index = 0; index < triangulation_full.size(); index++)
    {
        if (triangulation_full[index].contains_point(super_triangle.a) ||
            triangulation_full[index].contains_point(super_triangle.b) ||
            triangulation_full[index].contains_point(super_triangle.c))
        {
            bad_triangles_indexes.push_back(index);
        }
    }

    triangulation_res = clean_triangulation_res(triangulation_full, bad_triangles_indexes);
    return triangulation_res;
}

std::vector<Triangle> check_triangulation(const std::vector<Triangle> &traingulation)
{
    std::vector<Triangle> oper_triangulation = traingulation;
    int repeat_count = 0;
    // Go by index to make changes of triangles more simple
    for (int external_index = 0; external_index < oper_triangulation.size(); external_index++)
    {
        Circle cir_circle = Circle::calculate_circumscribed_circle(oper_triangulation[external_index]);
        cout << "Triangle for circle :" << oper_triangulation[external_index];
        cout << "Circle " << cir_circle.center << " radius:" << cir_circle.radius << endl;
        for (int internal_index = 0; internal_index < oper_triangulation.size(); internal_index++)
        {
            if (external_index == internal_index)
            {
                continue;
            }

            // TODO: for two or more points

            for (const auto &point : oper_triangulation[internal_index].get_points())
            {
                // cout << "Cycle Point: " << point << endl;
                // cout << "distance(cir_circle.center, point) < cir_circle.radius " << (distance(cir_circle.center, point) < cir_circle.radius) << endl
                //      << endl;
                // cout << "!oper_triangulation[external_index].contains_point(point) " << (!oper_triangulation[external_index].contains_point(point)) << endl
                //      << endl;
                if (distance(cir_circle.center, point) < cir_circle.radius &&
                    !oper_triangulation[external_index].contains_point(point))
                {
                    cout << "In triangles " << oper_triangulation[external_index] << " --- " << oper_triangulation[internal_index] << endl
                         << endl;
                    Point temp = oper_triangulation[external_index].replace_diff_point(point);
                    oper_triangulation[internal_index].replace_diff_point(temp);
                    external_index--;
                    cout << "Point : " << point << " was changed\n";
                    cout << "In triangles " << oper_triangulation[external_index] << " --- " << oper_triangulation[internal_index] << endl
                         << endl;
                }
            }
        }
    }

    return oper_triangulation;
}