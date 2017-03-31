#pragma once

#include <algorithm>
#include "Point.h"

#define PRECISION 1e-9


inline double sqr(double x) {
    return x * x;
}

inline double area_triangle (const Point &a, const Point &b, const Point &c) {
    return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
}

inline double max(double a, double b) {
    return a > b ? a : b;
}

inline double min(double a, double b) {
    return a < b ? a : b;
}

inline bool addition_intersection(double a, double b, double c, double d) {
    if (a > b)  std::swap (a, b);
    if (c > d)  std::swap (c, d);
    return max(a,c) <= min(b,d);
}

int compare(double num1, double num2);

double det(double a, double b, double c, double d);

int orientation(Point first_point, Point second_point, Point third_point);