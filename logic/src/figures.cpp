#include "../headers/figures.hpp"
#include <ostream>

using std::cout;
using std::endl;

double distance(const Point &p1, const Point &p2)
{
    return std::sqrt(std::pow((p2.x - p1.x), 2) + std::pow((p2.y - p1.y), 2));
}

bool operator==(const Point &p1, const Point &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator==(const Edge &e1, const Edge &e2)
{
    return (e1.a == e2.a && e1.b == e2.b) || (e1.a == e2.b && e1.b == e2.a);
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << "(x: " << p.x << "; " << p.y << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Triangle &p)
{
    os << "Triangle\n"
       << "a: " << p.a << "b: " << p.b << " c: " << p.c << endl;
    return os;
}

bool check_if_point_inside_circle(const Point &p, const Circle &c)
{
    if (distance(p, c.center) <= c.radius)
    {
        return true;
    }

    return false;
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

std::vector<Edge> Triangle::get_edges() const
{
    return {Edge(a, b), Edge(b, c), Edge(c, a)};
}

bool Triangle::contains_point(const Point &p) const
{
    if (a == p || b == p || c == p)
    {
        return true;
    }
    return false;
}

Circle Circle::calculate_circumscribed_circle(const Triangle &triangle)
{
    // Now it's my time
    double x, y;
    Point center;
    // Find middle points
    Point mid_ab = Point((triangle.a.x + triangle.b.x) / 2.0, (triangle.a.y + triangle.b.y) / 2.0);
    Point mid_bc = Point((triangle.b.x + triangle.c.x) / 2.0, (triangle.b.y + triangle.c.y) / 2.0);

    // Find angle coefficients

    double k_ab = (triangle.b.y - triangle.a.y) / (triangle.b.x - triangle.a.x);
    double k_bc = (triangle.c.y - triangle.b.y) / (triangle.c.x - triangle.b.x);

    // Find angle coefficients of perpendiculars m1 and m2
    double k_m1 = -1.0 / k_ab;
    double k_m2 = -1.0 / k_bc;

    if (k_ab == 0.0)
    {
        ;
        x = mid_ab.x;
        y = k_m2 * (x - mid_bc.x) + mid_bc.y;
        center.x = x;
        center.y = y;
    }
    else if (k_bc == 0.0)
    {
        x = mid_bc.x;
        y = k_m1 * (x - mid_ab.x) + mid_ab.y;
        center.x = x;
        center.y = y;
    }
    else
    {
        std::vector<std::vector<double>> matrix_A = {
            {-k_m1, 1.0},
            {-k_m2, 1.0}};

        std::vector<double> b = {
            mid_ab.y - k_m1 * mid_ab.x,
            mid_bc.y - k_m2 * mid_bc.x};

        auto result = solve_2_x_2_matrix(matrix_A, b);
        center.x = result.first;
        center.y = result.second;
    }

    double radius = distance(center, triangle.a);
    return Circle(center, radius);
}
