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

int orientation(Point first_point, Point second_point, Point third_point) {
    double val = (second_point.y() - first_point.y()) * (third_point.x() - second_point.x()) -
                 (second_point.x() - first_point.x()) * (third_point.y() - second_point.y());

    return compare(val, 0);
}

void quickSort(double *arr, int left, int right) {
    int i = left, j = right;
    double tmp;
    double pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}