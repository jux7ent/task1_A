#pragma once

#include "BaseShape.h"
#include "Point.h"


class Segment : public BaseShape {

    friend bool intersection(const Segment &first_segment, const Segment &second_segment);

private:

    Point first_point_, second_point_;

public:

    Segment();

    Segment(double point1_x, double point1_y, double point2_x, double point2_y);

    Segment(const Point &first_point, const Point &second_point);

    double distance_to_segment(const Segment &segment) const;

    double distance_to_point(const Point &point) const;

    Point first_point() const;

    Point second_point() const;

    void shift(const Vector &vector);

    bool check_point(const Point &point) const;

    bool intersection_segment(const Segment &segment) const;
};