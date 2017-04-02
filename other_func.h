#pragma once

#include <algorithm>
#include "Point.h"
#include "Polygon.h"

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

inline void swap(Point &f_pt, Point &s_pt) {
    Point temp = f_pt;
    f_pt = s_pt;
    s_pt = temp;
}

inline bool compare (Point f_pt, Point s_pt) {
    return f_pt.x() < s_pt.x() || f_pt.x() == s_pt.x() && f_pt.y() < s_pt.y();
}

bool point_in_box(const Point &f_pt, const Point &s_pt, const Point &ch_pt);

double cosAngle(Point f_pt, Point s_pt, Point t_pt);

void quickSort(double *arr, int begin, int end);

int compare(double num1, double num2);

double det(double a, double b, double c, double d);

int orientation(Point first_point, Point second_point, Point third_point);