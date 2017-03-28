#include <iostream>
#include "Point.h"
#include "cmath"

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