#pragma once

class Point {
public:
    double x, y;
    bool is_none;
    Point();
    Point(double, double);
    void insert(double, double);
    friend double dist_between_points(const Point &, const Point &);
    Point &operator = (double);
    friend void printPoints(const Point *, const unsigned int);
    //   friend bool between_points(const Point &, const Point &, const Point &);
};