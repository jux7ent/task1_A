#include <cmath>
#include <algorithm>
#include <iostream>
#include "Polygon.h"
#include "other_func.h"
#include "Ray.h"
#include <vector>

using std::vector;

bool check_point(const Point &verified_point, Point *points, unsigned int points_count) {

    Point extension(verified_point.x() + 123, verified_point.y() + 15);
    Ray ray(verified_point, extension);
    Line line(verified_point, extension);
    Line lines[points_count];

    unsigned int count_intersect = 0;

    for (short i = 0; i < points_count; ++i) { //проверка границ

        Segment segment(points[i % points_count], points[(i + 1) % points_count]);

        if (verified_point.belong_to_segment(segment))
            return true;

    }

    for (short i = 0; i < points_count; ++i) {

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
            if (verified_point.belong_to_segment({points[i % points_count], points[(i + 1) % points_count]}))
                return true;
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

    int i, j, k;
    int flag = 0;
    double z;

    if (count_points < 3)
        return(0);

    for (i = 0; i< count_points; i++) {

        j = (i + 1) % count_points;
        k = (i + 2) % count_points;
        z  = (points[j].x() - points[i].x()) * (points[k].y() - points[j].y());
        z -= (points[j].y() - points[i].y()) * (points[k].x() - points[j].x());

        if (z < 0)
            flag |= 1;
        else if (z > 0)
            flag |= 2;
        if (flag == 3)
            return false;

    }

    if (flag != 0)
        return true;
    else
        return(false);

}


void convexJarvis(vector<Point> &points, vector<int> &result) {
    int n = points.size();
    int first, q, next, i;
    double sign;
    // находим самую нижнюю из самых левых точек
    first = 0;
    for (i = 1; i < n; ++ i)
        if (points[i].x() < points[first].x() || (points[i].x() == points[first].x() && points[i].y() < points[first].y()))
            first = i;

    q = first; // текущая точка
    // добавляем точки в оболочку
    do
    {
        result.push_back(q);
        next = q;
        // ищем следующую точку
        for (i = n - 1; i >= 0; -- i)
            if (points[i].x() != points[q].x() || points[i].y() != points[q].y())
            {
                sign = area_triangle (points[q], points[i], points[next]);

                if (next == q || sign > 0 || (sign == 0 && point_in_box(points[next], points[q], points[i])))
                    next = i;
            }
        q = next;
    }
    while (q != first);
}

Point *convexHullGraham(unsigned int points_count, Point *points) {

    Point st_pt = points[0];
    unsigned int i;

    for (i = 1; i < points_count; ++i) { //поиск минимальной точки (стартовой)
        if (st_pt.y() > points[i].y())
            st_pt = points[i];
        else if (st_pt.y() == points[i].y() && st_pt.x() > points[i].x())
            st_pt = points[i];
    }

    swap(points[i], points[0]);

    //заполняем массив полярными углами от стартовой точки

    double *polar = new double[points_count - 1];

    Vector h_vec(st_pt.x(), st_pt.y(), st_pt.x() + 1, st_pt.y());
    Vector cur_vec;

    for (unsigned int i = 1; i < points_count; ++i) {
        cur_vec.update(st_pt, points[i]);
        polar[i - 1] = vecMul(h_vec, cur_vec);
    }

    quickSort(polar, 0, points_count - 1);


}































