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
    Triangle t1(Point(0.0, 0.0), Point(0.0, 4.0), Point(4.0, 0.0));
    Point p1(3.0, 4.0);
    Point p2(6.0, 3.0);

    cout << t1;
    cout << p1 << " " << t1.is_point_in_circle(p1) << endl;
    cout << p2 << " " << t1.is_point_in_circle(p2) << endl;
}