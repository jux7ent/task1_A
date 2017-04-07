#include <cmath>
#include <iostream>
#include "Point.h"
#include "other_func.h"
#include "Ray.h"

Point::Point() {
    x_ = y_ = 0;
    is_none_ = true;
}

Point::Point(double x, double y) {
    insert(x, y);
}

Point::Point(const Point &point) {
    *this = point;
}

void Point::insert(double x, double y) {
    x_ = x;
    y_ = y;
    is_none_ = false;
}

void printPoints(const unsigned int count_points, const Point *points) {
    for (unsigned int i = 0; i < count_points; ++i) {
        std::cout << points[i].x() << ' ' << points[i].y() << std::endl;
    }
}

double Point::x() const {
    return x_;
}

double Point::y() const {
    return y_;
}

double Point::x(double number) {
    x_ += number;

    return x_;
}

double Point::y(double number) {
    y_ += number;

    return y_;
}

bool Point::isNone(bool sign) {
    is_none_ = sign;
    return is_none_;
}

bool Point::isNone() {
    return is_none_;
}


double Point::distance_to_point(const Point &point) {
    return sqrt(sqr(point.x_ - x_) + sqr(point.y_ - y_));
}

bool Point::belong_to_line(const Line &line) const {
    return !compare((line.a() * x_ + line.b() * y_ + line.c()), 0);
}

bool Point::belong_to_segment(const Segment &segment) const {

    Line line(segment.first_point(), segment.second_point());

    if (line.check_point_plane(*this) == 0) { //принадлежность точки прямой
        Vector first_vector(*this, segment.first_point()), second_vector(*this, segment.second_point());

        return compare(scalarMul(first_vector, second_vector), 0) <= 0;
    }

    return false;
}

bool Point::belong_to_ray(const Ray &ray) const {

    Line line(ray.first_point(), ray.second_point());

    if (line.check_point_plane(*this) == 0) { //точка лежит на прямой

        Vector first_vector(ray.first_point(), ray.second_point()), second_vector(ray.first_point(), *this);
        return compare(scalarMul(first_vector, second_vector), 0) >= 0;

    }
    else {

        return false;

    }
}

void Point::shift(const Vector &v) {
    x_ += v.x();
    y_ += v.y();
}

bool Point::check_point(const Point &point) const {
    return x_ == point.x_ && y_ == point.y_;
}

bool Point::intersection_segment(const Segment &segment) const {
    return belong_to_segment(segment);
}
