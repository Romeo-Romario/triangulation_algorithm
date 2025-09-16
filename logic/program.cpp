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

    for (const auto &point : r)
    {
        cout << point.a << " " << point.b << endl;
    }
}