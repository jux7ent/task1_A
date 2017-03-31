#include <cmath>
#include <cstdlib>
#include "Line.h"
#include "other_func.h"
#include "Vector.h"

Line::Line() {
    a_ = b_ = c_ = 0;
}

Line::Line(const Point &first_point, const Point &second_point) {
    update(first_point, second_point);
}

Line::Line(const double a, const double b, const double c) {
    a_ = a;
    b_ = b;
    c_ = c;
}

void Line::update(const Point &first_point, const Point &second_point) {
    a_ = first_point.y() - second_point.y();
    b_ = second_point.x() - first_point.x();
    c_ = first_point.x() * second_point.y() - second_point.x() * first_point.y();
}

int intersection(const Line &first_line, const Line &second_line) {

    double val = det(first_line.a_, first_line.b_, second_line.a_, second_line.b_);

    if (val == 0) { //прямые совпадают или параллельны

        if(!compare(det(first_line.a_, first_line.c_, second_line.a_, second_line.c_) -
                        det(first_line.b_, first_line.c_, second_line.b_, second_line.c_), 0) &&
               !compare(det(first_line.a_, first_line.c_, second_line.a_, second_line.c_), 0))
            return 2;
        else
            return 0;

    } else {

        return 1;

    }
}

Point *intersection_point(const Line &first_line, const Line &second_line) {

    Point *result = new Point;
    double val = det(first_line.a_, first_line.b_, second_line.a_, second_line.b_);

    result->insert(-det(first_line.c_, first_line.b_, second_line.c_, second_line.b_) / val,
                 -det(first_line.a_, first_line.c_, second_line.a_, second_line.c_) / val);


    return result;

}

int Line::isPointOnLine(const Point &point) { // 1 - верхняя полуплоскость, -1 - нижняя, 0 - на линии

    return compare((a_ * point.x() + b_ * point.y() + c_), 0);

}

double Line::distance_to_point(const Point &point)  const {

    if (point.belong_to_line(*this))
        return 0;

    return std::abs(a_ * point.x() + b_ * point.y() + c_) / sqrt(sqr(a_) + sqr(b_));

}

double Line::distance_to_line(const Line &line) const {

    double coefficient = 1;

    if (a_ != line.a()) {
        if (a_ == 0)
            exit(10);
        coefficient = line.a() / a_;
    }

    return std::abs(line.c() - c_ / coefficient) / sqrt(sqr(a_ / coefficient) + sqr(b_ / coefficient));

}

double Line::a() const {
    return a_;
}

double Line::b() const {
    return b_;
}

double Line::c() const {
    return c_;
}