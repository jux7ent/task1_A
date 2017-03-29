#pragma once
#include "other_func.cpp"
#include "Point.h"

class Line {
public:
    double a, b, c; //коэфф. ур-я ax + by + c = 0
    Line();
    Line(const Point &, const Point &);
    Line(const double, const double, const double);
    void insert(const Point &, const Point &);
    bool isPointOnLine(const Point &);
    double distPointLine(const Point &);
    friend bool intersection(const Line &, const Line &, Point &);
};

int compare(double num1, double num2);