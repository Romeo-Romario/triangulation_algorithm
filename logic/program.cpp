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
    Triangle t1(Point(0, 5), Point(0, -5), Point(1, 0));
    Triangle t2(Point(0, 5), Point(0, -5), Point(-1, 0));

    vector<Triangle> tt = {t1, t2};

    vector<Triangle> result = check_triangulation(tt);

    cout << "Result\n";
    for (const auto &t : result)
    {
        cout << t;
    }
}