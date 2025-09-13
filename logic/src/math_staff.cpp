#include "../headers/math_staff.hpp"

/*
Need info about pair

std::pair<int, std::string> student1(101, "Alice");

auto student2 = std::make_pair(102, "Bob");

std::cout << "Student 1 ID: " << student1.first << ", Name: " << student1.second << std::endl;
std::cout << "Student 2 ID: " << student2.first << ", Name: " << student2.second << std::endl;
*/

std::pair<double, double> solve_2_x_2_matrix(const std::vector<std::vector<double>> &matrix, const std::vector<double> &b)
{
    /*
    Currently it's 0:31am
    I am not in best shape to write this kind of staff
    so I will keep it as simple as possible
    */

    double divider = matrix[0][0] / matrix[1][0];

    std::vector<double> second_row_matrix = {};
    double second_row_b;

    for (int i = 0; i < matrix[1].size(); i++)
    {
        second_row_matrix.push_back(matrix[0][i] - (matrix[1][i] * divider));
    }

    second_row_b = b[0] - (b[1] * divider);

    double y = second_row_b / second_row_matrix[1];
    double x = (b[0] - matrix[0][1] * y) / matrix[0][0];

    return std::make_pair(x, y);
}