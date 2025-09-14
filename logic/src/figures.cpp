#include "../headers/figures.hpp"

double distance(const Point &p1, const Point &p2)
{
    return std::sqrt(std::pow((p2.x - p1.x), 2) + std::pow((p2.y - p1.y), 2));
}

double Edge::length() const
{
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Triangle::area() const
{
    return 0.5 * std::abs(
                     a.x * (b.y - c.y) +
                     b.x * (c.y - a.y) +
                     c.x * (a.y - b.y));
}

bool Triangle::isValid() const
{
    return area() > 0.0;
}

double Triangle::perimeter() const
{
    Edge ab(a, b);
    Edge bc(b, c);
    Edge ca(c, a);
    return ab.length() + bc.length() + ca.length();
}

Circle Circle::calculate_circumscribed_circle(const Triangle &triangle)
{
    // x1(x1, y1), x2(x2, y2), p1(p1, q1), p2(p2,q2)
    /*
    x1 -> a
    x2 -> b
    p1 -> b
    p2 -> c
    x1,y1 = ...
    x2,y2 = ...
    p1,q1 = ...
    p2,q2 = ...
    A = np.array([[y1 - y2,    x2 - x1],
          [q1 - q2,    p2 - p1]], dtype=float)
    b = np.array([
        (y1-y2)*(x1+x2)/2 + (x2-x1)*(y1+y2)/2,
        (q1-q2)*(p1+p2)/2 + (p2-p1)*(q1+q2)/2
    ], dtype=float)
    */
    std::vector<std::vector<double>> matrix_A = {
        {triangle.a.y - triangle.b.y, triangle.b.x - triangle.a.x},
        {triangle.b.y - triangle.c.y, triangle.c.x - triangle.b.x}};
    std::vector<double> b = {
        (triangle.a.y - triangle.b.y) * (triangle.b.x + triangle.a.x) / 2 + (triangle.b.x - triangle.a.x) * (triangle.a.y + triangle.b.y) / 2,
        (triangle.b.y - triangle.c.y) * (triangle.c.x + triangle.b.x) / 2 + (triangle.c.x - triangle.b.x) * (triangle.b.y + triangle.c.y) / 2};
    auto result = solve_2_x_2_matrix(matrix_A, b);
    Point center = Point(result.first, result.second);
    double radius = distance(center, triangle.a);
    return Circle(center, radius);
}
