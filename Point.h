#pragma once

#include "BaseShape.h"

class Line;
class Ray;
class Segment;

class Point : public BaseShape {

    friend void printPoints(const unsigned int points_count, const Point *);

private:

    double x_, y_;
    bool is_none_;

public:

    Point();

    Point(double x, double y);

    Point(const Point &point);

    void insert(double x, double y);

    double distance_to_point(const Point &point);

    bool belong_to_line(const Line &line) const;

    bool belong_to_segment(const Segment &segment) const;

    bool belong_to_ray(const Ray &ray) const;

    double x() const;

    double y() const;

    double x(double number);

    double y(double number);

    bool isNone(bool sign);

    bool isNone();

    void shift(const Vector &v);

    bool check_point(const Point &point) const;

    bool intersection_segment(const Segment &segment) const;

};
