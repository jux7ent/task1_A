#include <cmath>
#include <algorithm>
#include "Polygon.h"
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

        if (intersection(line, lines[i])) { //если прямые пересекаются или совпадают


            Segment segment(points[i % points_count], points[(i + 1) % points_count]);

            if (intersection_point.x() >= verified_point.x() &&
                intersection_point.belong_to_segment(segment)) {

                ++count_intersect;

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