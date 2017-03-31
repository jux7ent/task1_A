#include <cmath>
#include "other_func.h"

int compare(double num1, double num2) {
    if (std::abs(num1 - num2) < PRECISION) {
        return 0;
    }
    return num1 < num2 ? -1 : 1;
}

double det(double a, double b, double c, double d) {
    return a * d - b * c;
}

double orientation(Point first_point, Point second_point, Point third_point) {

    double val = (second_point.y() - first_point.y()) * (third_point.x() - second_point.x()) -
                 (second_point.x() - first_point.x()) * (third_point.y() - second_point.y());

    return compare(val, 0);

}