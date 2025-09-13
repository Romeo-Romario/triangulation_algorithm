#pragma once
#include <cmath> // For std::sqrt

class Point
{
public:
    double x;
    double y;

    Point() : x(0.0), y(0.0) {}
    Point(const Point &el) : x{el.x}, y{el.y} {}
    Point(double x, double y) : x(x), y(y) {}

    ~Point() {}
};

class Edge
{
public:
    Point a;
    Point b;

    Edge() : a(), b() {}
    Edge(const Point &p1, const Point &p2) : a(p1), b(p2) {}
    Edge(const Edge &e) : a(e.a), b(e.b) {}

    ~Edge() {}

    double length() const
    {
        double dx = b.x - a.x;
        double dy = b.y - a.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

struct Triangle
{
    Point a;
    Point b;
    Point c;

    Triangle() : a(), b(), c() {}
    Triangle(const Point &p1, const Point &p2, const Point &p3) : a(p1), b(p2), c(p3) {}
    Triangle(const Triangle &t) : a(t.a), b(t.b), c(t.c) {}

    ~Triangle() {}

    // Calculate the area using the shoelace formula
    double area() const
    {
        return 0.5 * std::abs(
                         a.x * (b.y - c.y) +
                         b.x * (c.y - a.y) +
                         c.x * (a.y - b.y));
    }

    bool isValid() const
    {
        return area() > 0.0;
    }

    double perimeter() const
    {
        Edge ab(a, b);
        Edge bc(b, c);
        Edge ca(c, a);
        return ab.length() + bc.length() + ca.length();
    }
};

struct Circle
{
    Point center;
    double radius;

    static Circle calculate_center(Triangle triangle)
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

        return Circle();
    }
}