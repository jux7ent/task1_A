#pragma once

#include "Point.h"

class Segment {

    friend bool intersection(const Segment &first_segment, const Segment &second_segment, Point &intersection_point);

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


};