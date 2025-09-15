#include "../headers/figures.hpp"
#include <ostream>
#include <cmath>

using std::cout;
using std::endl;

//============================================
// Generall
double distance(const Point &p1, const Point &p2)
{
    return std::sqrt(std::pow((p2.x - p1.x), 2) + std::pow((p2.y - p1.y), 2));
}

void rotate_edge(Triangle &t1, Triangle &t2)
{
    std::vector<Point> common_points = {};
    std::vector<Point> diff_points = {};
    for (const auto &point : t2.get_points())
    {
        if (t1.contains_point(point))
        {
            common_points.push_back(point);
        }
        else
        {
            diff_points.push_back(point);
        }
    }

    if (common_points.size() < 2)
    {
        cout << "Triangles:\n"
             << t1 << "and:\n"
             << t2 << "have only one or less common point" << endl;
        return;
    }

    for (const auto &point : t1.get_points())
    {
        if (!t2.contains_point(point))
        {
            diff_points.push_back(point);
        }
    }

    cout << "t1 was changed from: " << t1;
    t1 = Triangle(diff_points[0], diff_points[1], common_points[0]);
    cout << "to: " << t1;

    cout << "t2 was changed from: " << t2;
    t2 = Triangle(diff_points[0], diff_points[1], common_points[1]);
    cout << "to: " << t2;
}

//============================================

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
    os << "(x: " << p.x << "; y:" << p.y << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Triangle &p)
{
    os << "Triangle: "
       << "(a: " << p.a << " b: " << p.b << " c: " << p.c << ")" << endl;
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

// Edge
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

std::vector<Point> Triangle::get_points() const
{
    return {a, b, c};
}
bool Triangle::contains_point(const Point &p) const
{
    return a == p || b == p || c == p;
}

// Circle
Circle Circle::calculate_circumscribed_circle(const Triangle &triangle)
{
    double x1 = triangle.a.x, y1 = triangle.a.y;
    double x2 = triangle.b.x, y2 = triangle.b.y;
    double x3 = triangle.c.x, y3 = triangle.c.y;

    double d = 2 * (x1 * (y2 - y3) +
                    x2 * (y3 - y1) +
                    x3 * (y1 - y2));

    if (fabs(d) < 1e-12)
    {
        // Degenerate triangle (points are collinear) → no unique circle
        return Circle(Point(0, 0), -1);
    }

    double ux = ((x1 * x1 + y1 * y1) * (y2 - y3) +
                 (x2 * x2 + y2 * y2) * (y3 - y1) +
                 (x3 * x3 + y3 * y3) * (y1 - y2)) /
                d;

    double uy = ((x1 * x1 + y1 * y1) * (x3 - x2) +
                 (x2 * x2 + y2 * y2) * (x1 - x3) +
                 (x3 * x3 + y3 * y3) * (x2 - x1)) /
                d;

    Point center(ux, uy);
    double radius = distance(center, triangle.a);

    return Circle(center, radius);
}
