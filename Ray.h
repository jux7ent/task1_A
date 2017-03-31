#pragma once
#include "Point.h"
#include "Vector.h"

class Ray {

private:

    Point first_point_;
    Point second_point_;

public:

    Ray();

    Ray(const Point &first_point, const Point &second_point);

    bool intersect_to_segment(const Segment &segment);

    double distance_to_point(const Point &point);

    Point first_point() const;

    Point second_point() const;
};
