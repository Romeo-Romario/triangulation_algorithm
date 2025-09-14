#include "../headers/figures.hpp"
#include <ostream>

using std::cout;
using std::endl;

// Generall
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
    os << "(x: " << p.x << "; y:" << p.y << ")";
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

std::vector<Point> Triangle::get_points() const
{
    return {a, b, c};
}
bool Triangle::contains_point(const Point &p) const
{
    return a == p || b == p || c == p;
}

Point Triangle::replace_diff_point(const Point &p)
{
    // TODO check this thing
    Point res;
    if (a != p)
    {
        res = a;
        a = p;
        cout << "a was changed \n";
        cout << "from " << res << " to " << p << endl;
    }
    else if (b != p)
    {
        res = b;
        b = p;
        cout << "b was changed \n";
        cout << "from " << res << " to " << p << endl;
    }
    else if (c != p)
    {
        res = c;
        c = p;
        cout << "c was changed \n";
        cout << "from " << res << " to " << p << endl;
    }
    else
    {
        cout << "nothing was changed \n";
    }
    return res;
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
