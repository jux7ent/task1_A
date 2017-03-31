#pragma once

#include "Point.h"

#define PRECISION 1e-9


inline double sqr(double x) {
    return x * x;
}

int compare(double num1, double num2);

double det(double a, double b, double c, double d);

double orientation(Point first_point, Point second_point, Point third_point);