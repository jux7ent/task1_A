#pragma once

class Segment;
class Vector;
class Point;

class BaseShape {

    virtual void shift(const Vector &vector) = 0;

    virtual bool check_point(const Point &point) const = 0;

    virtual bool intersection_segment(const Segment &segment) const = 0;

};