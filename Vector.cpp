#include <cmath>
#include <iostream>
#include "Vector.h"
#include "other_func.h"

Vector::Vector() {
    x_ = y_ = 0;
}

Vector::Vector(double x, double y) {
    x_ = x;
    y_ = y;
}

Vector::Vector(const Point &first_point, const Point &second_point) {
    update(first_point, second_point);
}

Vector::Vector(double point1_x, double point1_y, double point2_x, double point2_y) {
    x_ = point2_x - point1_x;
    y_ = point2_y - point1_y;
}

void Vector::update(const Point &first_point, const Point &second_point) {
    x_ = second_point.x() - first_point.x();
    y_ = second_point.y() - first_point.y();
}

Vector plus_minus(const Vector &first_vector, const Vector &second_vector, bool sign) {
    int factor = (int(sign) * 2) - 1;

    Vector *result = new Vector(first_vector.x_ + factor * second_vector.x_, first_vector.y_ + factor * second_vector.y_);

    return *result;
}

double Vector::length() {
    return sqrt(sqr(x_) + sqr(y_));
}

void printCoords(const Vector &vector) {
    std::cout << vector.x_ << ' ' << vector.y_ << std::endl;
}

double vecMul(const Vector &vec1, const Vector &vec2) {
    return vec1.x_ * vec2.y_ - vec1.y_ * vec2.x_;
}

Vector operator + (const Vector &first_vector, const Vector &second_vector) {
    return plus_minus(first_vector, second_vector, true);
}

Vector operator - (const Vector &first_vector, const Vector &second_vector) {
    return plus_minus(first_vector, second_vector, false);
}

double scalarMul(const Vector &first_vector, const Vector &second_vector) {
    return first_vector.x_ * second_vector.x_ + first_vector.y_ * second_vector.y_;
}

std::ostream &operator << (std::ostream &out, const Vector &vector) {
    out << vector.x() << ' ' << vector.y();

    return out;
}

double Vector::x() const {
    return x_;
}

double Vector::y() const {
    return y_;
}