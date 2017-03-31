#pragma once

class Point;

class Line {

    friend bool intersection(const Line &, const Line &, Point &);

private:

    double a_, b_, c_; //коэфф. ур-я ax + by + c = 0

public:

    Line();

    Line(const Point &first_point, const Point &second_point);

    Line(const double a, const double b, const double c);

    void update(const Point &first_point, const Point &second_point);

    bool isPointOnLine(const Point &point);

    double distance_to_point(const Point &point);

    double distance_to_line(const Line &line) const;

    double a() const;

    double b() const;

    double c() const;
};
