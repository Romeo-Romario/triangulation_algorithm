#include <iostream>
#include <vector>
#include <utility>
#include "headers/figures.hpp"
#include "headers/math_staff.hpp"
#include "headers/my_functions.hpp"

/*
Purpose of this file is to test functions
*/
using std::cout;
using std::endl;
using std::vector;
int main()
{
    Triangle triangle = Triangle(Point(-11.661904, -10.0), Point(17.661904, -10.0), Point(3.0, 30.0));

    Circle circle = Circle::calculate_circumscribed_circle(triangle);

    cout << "Circle center: " << circle.center.x << " " << circle.center.y << " radius: " << circle.radius << endl;
}