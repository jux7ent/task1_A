#pragma once

#include "BaseShape.h"
#include "Point.h"

class Vector;

class Ray : public BaseShape {

private:

    Point first_point_;
    Point second_point_;

public:

    Ray();

    Ray(const Point &first_point, const Point &second_point);

    double distance_to_point(const Point &point);

    Point first_point() const;

    Point second_point() const;

    void shift(const Vector &vector);

    bool check_point(const Point &point) const;

    bool intersection_segment(const Segment &segment) const;
};
