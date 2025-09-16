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

Point compute_centroid(const std::vector<Point> &points)
{
    double cx = 0.0, cy = 0.0;
    for (const auto &p : points)
    {
        cx += p.x;
        cy += p.y;
    }
    cx /= points.size();
    cy /= points.size();
    return Point(cx, cy);
}

void sort_points_clockwise(std::vector<Point> &points)
{
    if (points.size() < 2)
        return;

    Point center = compute_centroid(points);

    std::sort(points.begin(), points.end(),
              [&center](const Point &a, const Point &b)
              {
                  double angleA = atan2(a.y - center.y, a.x - center.x);
                  double angleB = atan2(b.y - center.y, b.x - center.x);
                  return angleA > angleB;
              });
}

bool operator==(const Point &p1, const Point &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator==(const Edge &e1, const Edge &e2)
{
    return (e1.a == e2.a && e1.b == e2.b) || (e1.a == e2.b && e1.b == e2.a);
}

bool operator==(const Triangle &t1, const Triangle &t2)
{
    std::vector<Point> p1 = {t1.a, t1.b, t1.c};
    std::vector<Point> p2 = {t2.a, t2.b, t2.c};
    std::sort(p1.begin(), p1.end(), [](const Point &a, const Point &b)
              { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    std::sort(p2.begin(), p2.end(), [](const Point &a, const Point &b)
              { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    return p1 == p2;
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

bool Triangle::is_point_in_circle(const Point &p) const
{
    // Беремо вершини як є
    const Point &p1 = a;
    const Point &p2 = b;
    const Point &p3 = c;

    double _11 = p1.x - p.x;
    double _12 = p1.y - p.y;
    double _13 = _11 * _11 + _12 * _12;

    double _21 = p2.x - p.x;
    double _22 = p2.y - p.y;
    double _23 = _21 * _21 + _22 * _22;

    double _31 = p3.x - p.x;
    double _32 = p3.y - p.y;
    double _33 = _31 * _31 + _32 * _32;

    double det = _11 * (_22 * _33 - _23 * _32) - _12 * (_21 * _33 - _23 * _31) + _13 * (_21 * _32 - _22 * _31);

    // Визначаємо орієнтацію трикутника
    double orientation = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    const double EPS = 1e-12;
    if (orientation > 0)
    {
        return det > EPS;
    }
    else
    {
        return det < -EPS;
    }
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
