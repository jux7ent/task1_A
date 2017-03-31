#include <cmath>
#include <algorithm>
#include "Polygon.h"
#include "Line.h"
#include "Segment.h"
#include "other_func.h"

bool check_point(const Point &verified_point, Point *points, unsigned int points_count) {

    Point extension(verified_point.x(), verified_point.y() + 1);
    Line line(verified_point, extension);
    Line lines[points_count];
    Point intersection_point;

    unsigned int count_intersect = 0;

    for (short i = 0; i < points_count; ++i) { //проверка границ

        Segment segment(points[i % points_count], points[(i + 1) % points_count]);

        if (verified_point.belong_to_segment(segment))
            return true;

    }

    for (short i = 0; i < points_count; ++i) {

        lines[i].update(points[i % points_count], points[(i + 1) % points_count]);

        if (intersection(line, lines[i], intersection_point)) { //если прямые пересекаются

            if (!intersection_point.isNone()) {

                Segment segment(points[i % points_count], points[(i + 1) % points_count]);

                if (intersection_point.x() >= verified_point.x() &&
                        intersection_point.belong_to_segment(segment)) {

                    ++count_intersect;

                }

            }

        }
    }

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

bool isConvexPolygon(const Point *points, int count_points) {

    Vector *first_vector = new Vector(points[0], points[1]); //для того чтобы просто поменять указатели
    Vector *second_vector = new Vector(points[1], points[2]);
    int sign = compare(vecMul(*first_vector, *second_vector), 0);

    std::swap(first_vector, second_vector);

    for (unsigned int i = 2; i < count_points; ++i) {

        second_vector->update(points[i % count_points], points[(i + 1) % count_points]);

        if (sign != compare(vecMul(*first_vector, *second_vector), 0))
            return false;

    }

    delete first_vector, second_vector;

    return true;
}

Point *convexJarvis(unsigned int count_points, Point *points) {

    Point *result = new Point[count_points + 1];
    unsigned int cur = 0;
    int left = 0;

    for (int i = 1; i < count_points; i++)
        if (points[i].x() < points[left].x())
            left = i;

    int p = left, q;

    do {
        result[cur] = points[p];
        ++cur;

        q = (p + 1) % count_points;

        for (int i = 0; i < count_points; i++)
        {
            //если i более подходит, чем q, то обновляем q
            if (orientation(points[p], points[i], points[q]) == -1)
                q = i;
        }

        p = q;

    } while (p != left);

    result[count_points].insert(cur, cur); //в качестве последней точки добавляем сколько всего точек по вып. обол.

    return result;
}