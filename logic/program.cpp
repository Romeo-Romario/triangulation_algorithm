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
    Triangle t(Point(0, 0), Point(0, 2), Point(2, 0));
    Point p1(1.5, 2.0);
    Point p2(1.5, -1);

    cout << t << " " << p1 << " " << t.is_point_in_circle(p1) << endl;
    cout << t << " " << p2 << " " << t.is_point_in_circle(p2);
}