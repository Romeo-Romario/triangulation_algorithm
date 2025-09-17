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

bool nearlyEqual(double a, double b)
{
    constexpr double eps = 0.003;
    return std::fabs(a - b) < eps;
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
        // cout << "Triangles:\n"
        //      << t1 << "and:\n"
        //      << t2 << "have only one or less common point" << endl;
        return;
    }

    for (const auto &point : t1.get_points())
    {
        if (!t2.contains_point(point))
        {
            diff_points.push_back(point);
        }
    }

    // cout << "t1 was changed from: " << t1;
    t1 = Triangle(diff_points[0], diff_points[1], common_points[0]);
    // cout << "to: " << t1;

    // cout << "t2 was changed from: " << t2;
    t2 = Triangle(diff_points[0], diff_points[1], common_points[1]);
    // cout << "to: " << t2;
}

std::vector<Edge> points_to_sorted_edges(const std::vector<Point> &points)
{
    std::vector<Edge> result;
    size_t n = points.size();
    if (n < 2)
        return result;
    if (n == 2)
    {
        result.emplace_back(points[0], points[1]);
        return result;
    }

    // compute centroid
    double cx = 0.0, cy = 0.0;
    for (const auto &p : points)
    {
        cx += p.x;
        cy += p.y;
    }
    cx /= static_cast<double>(n);
    cy /= static_cast<double>(n);

    // build angle+dist table
    struct Entry
    {
        Point p;
        double ang;
        double dist2;
    };
    std::vector<Entry> table;
    table.reserve(n);
    for (const auto &p : points)
    {
        double dx = p.x - cx;
        double dy = p.y - cy;
        double ang = std::atan2(dy, dx);
        double d2 = dx * dx + dy * dy;
        table.push_back({p, ang, d2});
    }

    const double ANG_EPS = 1e-12;
    std::sort(table.begin(), table.end(), [&](const Entry &A, const Entry &B)
              {
        if (std::fabs(A.ang - B.ang) < ANG_EPS)
            return A.dist2 < B.dist2; // tie-break: nearer point first
        return A.ang < B.ang; });

    // form edges in sorted order (wrap around)
    for (size_t i = 0; i < n; ++i)
    {
        const Point &pa = table[i].p;
        const Point &pb = table[(i + 1) % n].p;
        result.emplace_back(pa, pb);
    }

    return result;
}

int orientation(const Point &p, const Point &q, const Point &r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);

    if (val == 0.0)
        return 0;
    return (val > 0.0) ? 1 : 2;
}

// check if point q lies on segment pr
bool onSegment(const Point &p, const Point &q, const Point &r)
{
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

// main intersection check
bool intersects(const Edge &e1, const Edge &e2)
{
    Point p1 = e1.a, q1 = e1.b;
    Point p2 = e2.a, q2 = e2.b;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
    {
        // exclude endpoint-only case
        if (p1 == p2 || p1 == q2 || q1 == p2 || q1 == q2)
            return false;
        return true;
    }

    // Special cases (collinear + overlap)
    if (o1 == 0 && onSegment(p1, p2, q1))
        return !(p2 == p1 || p2 == q1);
    if (o2 == 0 && onSegment(p1, q2, q1))
        return !(q2 == p1 || q2 == q1);
    if (o3 == 0 && onSegment(p2, p1, q2))
        return !(p1 == p2 || p1 == q2);
    if (o4 == 0 && onSegment(p2, q1, q2))
        return !(q1 == p2 || q1 == q2);

    return false;
}

std::vector<Edge> edges_to_point(const Point &target_point, const std::vector<Point> &points)
{
    std::vector<Edge> result = {};
    for (const auto &point : points)
    {
        result.push_back(Edge(target_point, point));
    }
    return result;
}
//============================================

bool operator==(const Point &p1, const Point &p2)
{
    const double EPS = 1e-9;
    return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS;
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

// Triangle

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
