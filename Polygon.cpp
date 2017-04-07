#include <cmath>
#include <iostream>
#include "Polygon.h"
#include "other_func.h"
#include "Ray.h"

bool check_point(const Point &verified_point, const Point *points, unsigned int points_count) {

    Point extension(verified_point.x() + 123, verified_point.y() + 15);
    Ray ray(verified_point, extension);
    Line line(verified_point, extension);
    Line *lines = new Line[points_count];

    unsigned int count_intersect = 0;

    for (unsigned int i = 0; i < points_count; ++i) { //проверка границ

        Segment segment(points[i % points_count], points[(i + 1) % points_count]);

        if (verified_point.belong_to_segment(segment))
            return true;

    }

    for (unsigned int i = 0; i < points_count; ++i) {

        lines[i].update(points[i % points_count], points[(i + 1) % points_count]);

        if (intersection(line, lines[i]) == 1) { //если прямые пересекаются

            Point *intersect_point = intersection_point(line, lines[i]);
            Segment segment(points[i % points_count], points[(i + 1) % points_count]);

            if (intersect_point->belong_to_ray(ray) &&
                intersect_point->belong_to_segment(segment)) {

                ++count_intersect;

            }

            delete intersect_point;

        }
        else if (intersection(line, lines[i]) == 2) {
            if (verified_point.belong_to_segment({points[i % points_count], points[(i + 1) % points_count]})) {
                delete[] lines;
                return true;
            }
        }

    }

    delete[] lines;
     return count_intersect % 2 != 0;
}

double area(unsigned int points_count, Point *points) {
    double result = 0;

    for (unsigned int i = 0; i < points_count; ++i) {
        result += points[i % points_count].x() * points[(i + 1) % points_count].y() - points[i % points_count].y() *
                                                                                      points[(i + 1) % points_count].x();
    }

    result /= 2;
    result = std::abs(result);

    return result;
}

bool isConvexPolygon(const Point *points, int points_count) {

    int i, j, k;
    int flag = 0;
    double z;

    if (points_count < 3)
        return(0);

    for (i = 0; i< points_count; i++) {
        j = (i + 1) % points_count;
        k = (i + 2) % points_count;
        z  = (points[j].x() - points[i].x()) * (points[k].y() - points[j].y());
        z -= (points[j].y() - points[i].y()) * (points[k].x() - points[j].x());

        if (z < 0)
            flag |= 1;
        else if (z > 0)
            flag |= 2;
        if (flag == 3)
            return false;
    }

    return bool(flag);
}