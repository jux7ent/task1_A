#include <cmath>
#include "Point.h"
#include "Line.h"
#include "Vector.h"

#define PRESICION 1e-9

int compare(double num1, double num2) {
    if (std::abs(num1 - num2) < PRESICION) {
        return 0;
    }
    return num1 < num2 ? -1 : 1;
}

double det (double a, double b, double c, double d) {
    return a * d - b * c;
}

bool isPointOnRay(const Point &p1, const Point &p2, const Point &p) {
    Line line(p1, p2);
    if (line.isPointOnLine(p)) {
        Vector vec1(p1, p), vec2(p, p2);
        return vec1 * vec2 >= 0;
    }
    else {
        return false;
    }
}

double distPointRay(const Point &p1, const Point &p2, const Point &p) {
    Vector vec1(p1, p2), vec2(p1, p);
    if (vec1 * vec2 >= 0) {
        Line line(p1, p2);
        return line.distPointLine(p);
    }
    else {
        Vector vec_result(p1, p);
        return vec_result.length();
    }
}

double distPointSegment(const Point &p1, const Point &p2, const Point &p) {
    double dist1, dist2;
    dist1 = distPointRay(p1, p2, p);
    dist2 = distPointRay(p2, p1, p);

    return dist1 > dist2 ? dist1 : dist2;
}

bool segmentIntersection(const Point &segm1_1, const Point &segm1_2, const Point &segm2_1, const Point &segm2_2) {
    Line line1(segm1_1, segm1_2), line2(segm2_1, segm2_2);
    Point pointIntersection;

    if (intersection(line1, line2, pointIntersection)) {
        return between_points(segm1_1, segm1_2, pointIntersection) && between_points(segm2_1, segm2_2, pointIntersection);
    }
    else {
        return false;
    }
}

double distBetweenSegments(const Point &segm1_1, const Point &segm1_2, const Point &segm2_1, const Point &segm2_2) {
    if (segmentIntersection(segm1_1, segm1_2, segm2_1, segm2_2))
        return 0;
    else {
        double result, temp;
        result = distPointSegment(segm1_1, segm1_2, segm2_1);
        temp = distPointSegment(segm1_1, segm1_2, segm2_2);
        result = result < temp ? result : temp;
        temp = distPointSegment(segm2_1, segm2_2, segm1_1);
        result = result < temp ? result : temp;
        temp = distPointSegment(segm2_1, segm2_2, segm1_2);
        result = result < temp ? result : temp;

        return result;
    }
}

bool isConvexPolygon(int count_points, const Point *points) {
    Vector *vec1 = new Vector(points[0], points[1]); //для того чтобы просто поменять указатели
    Vector *vec2 = new Vector(points[1], points[2]);
    int sign = compare(vecMul(*vec1, *vec2), 0);
    std::swap(vec1, vec2);

    for (unsigned int i = 2; i < count_points; ++i) {
        vec2->update(points[i % count_points], points[(i + 1) % count_points]);
        if (sign != compare(vecMul(*vec1, *vec2), 0))
            return false;
    }

    delete vec1, vec2;

    return true;
}

int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);

    return compare(val, 0);
}


Point *convexJarvis(const unsigned int count_points, Point *points)
{
    Point *result = new Point[count_points + 1];
    unsigned int cur = 0;

    int left = 0;
    for (int i = 1; i < count_points; i++)
        if (points[i].x < points[left].x)
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