#pragma once

class Point;

class Line {

    friend int intersection(const Line &first_line, const Line &second_line); // 0 - параллельны, 1 - пересекаются, 2 - совпадают
    friend Point *intersection_point(const Line &first_line, const Line &second_line);

private:

    double a_, b_, c_; //коэфф. ур-я ax + by + c = 0

public:

    Line();

    Line(const Point &first_point, const Point &second_point);

    Line(const double a, const double b, const double c);

    void update(const Point &first_point, const Point &second_point);

    bool isPointOnLine(const Point &point);

    double distance_to_point(const Point &point) const;

    double distance_to_line(const Line &line) const;

    double a() const;

    double b() const;

    double c() const;
};
