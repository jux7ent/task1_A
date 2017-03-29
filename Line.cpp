#include <cmath>
#include "Line.h"
#include "other_func.cpp"

Line::Line() {
    a = b = c = 0;
}

Line::Line(const Point &p1, const Point &p2) {
    this->insert(p1, p2);
}

Line::Line(const double A, const double B, const double C) {
    this->a = A;
    this->b = B;
    this->c = C;
}

void Line::insert(const Point &p1, const Point &p2) {
    this->a = p1.y - p2.y;
    this->b = p2.x - p1.x;
    this->c = p1.x * p2.y - p2.x * p1.y;
}

bool intersection(const Line &line1, const Line &line2, Point &point) {
    point.is_none = true;
    double val = det(line1.a, line1.b, line2.a, line2.b);
    if (val == 0) { //прямые совпадают или параллельны
        return !compare(det(line1.a, line1.c, line2.a, line2.c) - det(line1.b, line1.c, line2.b, line2.c), 0) &&
               !compare(det(line1.a, line1.c, line2.a, line2.c), 0);
    } else {
        point.insert(-det(line1.c, line1.b, line2.c, line2.b) / val,
                     -det(line1.a, line1.c, line2.a, line2.c) / val);
        return true;
    }
}

bool Line::isPointOnLine(const Point &point) {
    return !compare((a * point.x + b * point.y + c), 0);
}

double Line::distPointLine(const Point &point) {
    return std::abs(a * point.x + b * point.y + c) / sqrt(a * a + b * b);
}