#include "Ray.h"
#include "other_func.h"

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

bool Ray::intersection_segment(const Segment &segment) const {
    Line f_line(first_point_, second_point_);
    Line s_line(segment.first_point(), segment.second_point());

    if (intersection(f_line, s_line)) {
        Point *t_pt = intersection_point(f_line, s_line);

        bool result = t_pt->belong_to_segment(segment) && t_pt->belong_to_ray(*this);

        delete t_pt;

        return result;

    }
    else {
        return false;
    }
}

Point Ray::first_point() const {
    return first_point_;
}

Point Ray::second_point() const {
    return second_point_;
}

void Ray::shift(const Vector &vector) {
    first_point_.shift(vector);
    second_point_.shift(vector);
}

bool Ray::check_point(const Point &point) const {
    return point.belong_to_ray(*this);
}
