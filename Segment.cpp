#include "Segment.h"
#include "Ray.h"
#include "Line.h"

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

    if (intersection(*this, segment, intersection_point))
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

bool intersection(const Segment &first_segment, const Segment &second_segment, Point &intersection_point) {

    Line first_line(first_segment.first_point_, first_segment.second_point_);
    Line second_line(second_segment.first_point_, second_segment.second_point_);

    if (intersection(first_line, second_line, intersection_point)) {
        return intersection_point.belong_to_segment(first_segment) && intersection_point.belong_to_segment(second_segment);
    }
    else {
        return false;
    }
}