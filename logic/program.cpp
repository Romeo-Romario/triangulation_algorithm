#include <iostream>
#include <vector>
#include <utility>
// #include "headers/figures.hpp"
#include "headers/math_staff.hpp"

/*
Purpose of this file is to test functions
*/
using std::vector;
int main()
{

    vector<vector<double>> matrix = {{2.0, 3.0}, {4.0, -1.0}};
    vector<double> b = {7.0, 9.0};

    auto result = solve_2_x_2_matrix(matrix, b);
}