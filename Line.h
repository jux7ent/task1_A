#pragma once

#include "BaseShape.h"

class Point;
class Segment;

class Line : public BaseShape {

    friend int intersection(const Line &first_line, const Line &second_line); // 0 - параллельны, 1 - пересекаются, 2 - совпадают
    friend Point *intersection_point(const Line &first_line, const Line &second_line);

private:

    double a_, b_, c_; //коэфф. ур-я ax + by + c = 0

public:

    Line();

    Line(const Point &first_point, const Point &second_point);

    Line(const double a, const double b, const double c);

    void update(const Point &first_point, const Point &second_point);

    double distance_to_point(const Point &point) const;

    double distance_to_line(const Line &line) const;

    int check_point_plane(const Point &point);

    double a() const;

    double b() const;

    double c() const;

    void shift (const Vector &vector);

    bool intersection_segment(const Segment &segment) const;

    bool check_point(const Point &point) const;
};
