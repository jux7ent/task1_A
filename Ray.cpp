#include "Ray.h"
#include "other_func.h"
#include "Line.h"

Ray::Ray() {
    first_point_.insert(0, 0);
    second_point_.insert(0, 0);
}

Ray::Ray(const Point &first_point, const Point &second_point) {
    first_point_ = first_point;
    second_point_ = second_point;
}

double Ray::distance_to_point(const Point &point) {

    Vector first_vector(first_point_, second_point_), second_vector(first_point_, point);

    if (compare(scalarMul(first_vector, second_vector), 0) >= 0) {

        Line line(first_point_, second_point_);

        return line.distance_to_point(point);

    }
    else {

        Vector result(first_point_, point);

        return result.length();

    }
}

Point Ray::first_point() const {
    return first_point_;
}

Point Ray::second_point() const {
    return second_point_;
}