#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <cmath> // For std::sqrt
#include <algorithm>

class Point
{
public:
    double x;
    double y;

    Point() : x(0.0), y(0.0) {}
    Point(const Point &el) : x{el.x}, y{el.y} {}
    Point(double x, double y) : x(x), y(y) {}
    friend bool operator==(const Point &p1, const Point &p2);
    friend std::ostream &operator<<(std::ostream &os, const Point &p); // mainly for debug purposes
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
    friend bool operator==(const Edge &e1, const Edge &e2);
    ~Edge() {}

    double length() const;
};

struct Triangle
{
public:
    Point a, b, c;
    Triangle() : a(), b(), c() {}
    Triangle(const Point &p1, const Point &p2, const Point &p3) : a(p1), b(p2), c(p3) {}
    double area() const;
    double perimeter() const;
    bool isValid() const;
    std::vector<Edge> get_edges() const;
    std::vector<Point> get_points() const;
    bool contains_point(const Point &p) const;
    friend bool operator==(const Triangle &t1, const Triangle &t2);
    friend std::ostream &operator<<(std::ostream &os, const Triangle &p); // mainly for debug purposes
};

struct Circle
{
public:
    Point center;
    double radius;
    Circle() : center(), radius(0.0) {} // <-- Default constructor needed!
    Circle(const Point &c, double r) : center(c), radius(r) {}
    static Circle calculate_circumscribed_circle(const Triangle &triangle);
};

double distance(const Point &p1, const Point &p2);
bool check_if_point_inside_circle(const Point &p, const Circle &c);
void rotate_edge(Triangle &t1, Triangle &t2);
bool nearlyEqual(double a, double b);
std::vector<Edge> points_to_sorted_edges(const std::vector<Point> &points);
