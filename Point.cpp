#include <iostream>
#include "Point.h"
#include "cmath"
#include "other_func.cpp"
#include "Vector.h"

#define SQR(x) ((x) * (x))

Point::Point() {
    this->x = this->y = 0;
    this->is_none = true;
}

Point::Point(double x, double y) {
    this->insert(x, y);
}

void Point::insert(double x, double y) {
    this->x = x;
    this->y = y;
    this->is_none = false;
}

double dist_between_points(const Point &p1, const Point &p2) {
    return sqrt(SQR(p2.x - p1.x) + SQR(p2.y - p1.y));
}

Point &Point::operator = (double val) {
    this->x = val;
    this->y = val;
}

void printPoints(const Point *points, const unsigned int count_points) {
    for (unsigned int i = 0; i < count_points; ++i) {
        std::cout << points[i].x << ' ' << points[i].y << std::endl;
    }
}

bool between_points(const Point &p1, const Point &p2, const Point &p3) { //принадлежность точки отрезку
    if (!compare(((p3.y - p1.y) * (p2.x - p1.x)) - ((p3.x - p1.x) * (p2.y - p1.y)), 0)) { //принадлежность точки прямой
        Vector vec1(p3, p1), vec2(p3, p2);
        return compare(vec1 * vec2, 0) <= 0;
    }

    return false;
}