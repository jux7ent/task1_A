#include <iostream>
#include "Segment.h"
#include "Ray.h"
#include "Line.h"
#include "other_func.h"

Segment::Segment() {
    first_point_.insert(0, 0);
    second_point_.insert(0, 0);
}

Segment::Segment(double point1_x, double point1_y, double point2_x, double point2_y) {
    first_point_.insert(point1_x, point1_y);
    second_point_.insert(point2_x, point2_y);
}

Segment::Segment(const Point &first_point, const Point &second_point) {
    first_point_ = first_point;
    second_point_ = second_point;
}

double Segment::distance_to_segment(const Segment &segment) const {
    Point intersection_point;

    if (intersection(*this, segment))

        return 0;

    else {

        double result, temp;

        result = this->distance_to_point(segment.first_point_);

        temp = this->distance_to_point(segment.second_point_);

        result = result < temp ? result : temp;

        temp = segment.distance_to_point(this->first_point_);

        result = result < temp ? result : temp;

        temp = segment.distance_to_point(this->second_point_);

        result = result < temp ? result : temp;

        return result;
    }
}

double Segment::distance_to_point(const Point &point) const {

    double first_distance, second_distance;

    Ray first_ray(first_point_, second_point_);
    Ray second_ray(second_point_, first_point_);

    first_distance = first_ray.distance_to_point(point);
    second_distance = second_ray.distance_to_point(point);

    return first_distance > second_distance ? first_distance : second_distance;
}

Point Segment::first_point() const {
    return first_point_;
}

Point Segment::second_point() const {
    return second_point_;
}

bool intersection(const Segment &first_segment, const Segment &second_segment) {

    bool f_condition = addition_intersection(first_segment.first_point().x(), first_segment.second_point().x(),
                                             second_segment.first_point().x(), second_segment.second_point().x());
    bool s_condition = addition_intersection(first_segment.first_point().y(), first_segment.second_point().y(),
                                             second_segment.first_point().y(), second_segment.second_point().y());
    bool t_contidion = area_triangle(first_segment.first_point(), first_segment.second_point(), second_segment.first_point()) *
                       area_triangle(first_segment.first_point(), first_segment.second_point(), second_segment.second_point()) <= 0;
    bool fo_contidion = area_triangle(second_segment.first_point(), second_segment.second_point(), first_segment.first_point()) *
                        area_triangle(second_segment.first_point(), second_segment.second_point(), first_segment.second_point()) <= 0;

    return f_condition && s_condition && t_contidion && fo_contidion;

}