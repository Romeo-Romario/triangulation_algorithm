#include <iostream>
#include <vector>
#include <utility>
#include "headers/figures.hpp"
#include "headers/my_functions.hpp"

/*
Purpose of this file is to test functions
*/
using std::cout;
using std::endl;
using std::vector;
int main()
{
    vector<Point> starting_points = {
        Point(-2.0, 0.0),
        Point(0.0, 2),
        Point(2.0, 0),
        Point(0.0, -2.0)};

    // vector<Point> result = insert_grid(starting_points, 3.0);

    // for (const auto &point : result)
    // {
    //     cout << point << endl;
    // }

    vector<Edge> r = points_to_sorted_edges(starting_points);
    Point _1(2.0, 2.0);

    for (const auto &s_edge : r)
    {
        for (const auto &edge : edges_to_point(_1, starting_points))
        {
            cout << "Starting edge: " << s_edge.a << " " << s_edge.b << " point_edge: " << edge.a << " " << edge.b << " intersection:" << intersects(edge, s_edge) << endl;
        }
    }

    Edge e1(Point(2.0, 4.0), Point(5.5, 2.0));
    Edge e2(Point(3.5, 2.0), Point(4.0, 4.0));

    Edge e(Point(3.5, 0.5), Point(5.5, 1.5));
    Point p(4.5, 1.0);

    // cout << "Intersection: " << intersects(e1, e2) << endl;
    // cout << "lays on edge: " << onSegment(e.a, p, e.b) << endl;
    // cout << "No intersects: " << intersects(e1, e) << endl;
}