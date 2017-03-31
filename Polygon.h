#pragma once

#include "Vector.h"
#include "Point.h"
#include "Line.h"
#include "Segment.h"


bool check_point(const Point &verified_point, Point *points, unsigned int points_count);

double area(unsigned int points_count, Point *points);

bool isConvexPolygon(const Point *points, int count_points);

Point *convexJarvis(unsigned int points_count, Point *points);


class BaseShape {

    virtual void shift(const Vector &) = 0;

    virtual bool check_point(double, double) = 0;

    virtual bool intersect_segment(double, double, double, double) = 0;

};

template<unsigned int points_count>
class Polygon : public BaseShape {

protected:

    Point points_[points_count];

public:

    Polygon();

    Polygon(const Point *);

    void shift(const Vector &);

    bool check_point(const Point &verified_point) const;

    bool intersect_segment(const Segment &segment) const;

    double area() const;

};


template<unsigned int points_count>
Polygon<points_count>::Polygon() {

    for (short i = 0; i < points_count; ++i) {
        points_[i].insert(0, 0);
    }

}

template<unsigned int points_count>
Polygon<points_count>::Polygon(const Point *points) {

    for (short i = 0; i < points_count; ++i) {
        points_[i] = points[i];
    }

}

template<unsigned int points_count>
void Polygon<points_count>::shift(const Vector &vector) {

    for (short i = 0; i < points_count; ++i) {
        points_[i].x(vector.x());
        points_[i].y(vector.y());
    }

}


template<unsigned int points_count>
bool Polygon<points_count>::check_point(const Point &verified_point) const {
    return ::check_point(verified_point, points_, points_count);
}

template<unsigned int points_count>
bool Polygon<points_count>::intersect_segment(const Segment &segment) const {

    Line line(segment.first_point(), segment.second_point());
    Line lines[points_count];
    Point intersect_point;

    for (short i = 0; i < points_count; ++i) {

        lines[i].update(points_[i % points_count], points_[(i + 1) % points_count]);

        if (intersection(line, lines[i], intersect_point) == 1) { //если прямые пересекаются

            Segment temp_segment(points_[i % points_count], points_[(i + 1) % points_count]);

            if (intersect_point.belong_to_segment(temp_segment)) { //если true, то точка лежит на стороне

                if (intersect_point.belong_to_segment(segment)) { //если точка лежит на отрезке

                    return true;

                }

            }

        }
        else if (intersection(line, lines[i], intersect_point) == 2) {

            return true;

        }
    }

    return false;
}

template<unsigned int points_count>
double Polygon<points_count>::area() const {
    return area(points_count, points_);
}

//////////////////////////////////////////////////////

class Rectangle : public Polygon<4> {

public:

    Rectangle() : Polygon() {}

    Rectangle(const Point *points) : Polygon(points) {}

};

///////////////////////////////////////////////////////

class Triangle : public Polygon<3> {

public:

    Triangle() : Polygon() {}

    Triangle(const Point *points) : Polygon(points) {}

};