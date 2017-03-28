#include <iomanip>
#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Line.h"

using std::cout;
using std::cin;
using std::endl;

#define SQR(x) ((x) * (x))

bool between_points(const Point &p1, const Point &p2, const Point &p3) { //принадлежность точки отрезку
    if (!compare(((p3.y - p1.y) * (p2.x - p1.x)) - ((p3.x - p1.x) * (p2.y - p1.y)), 0)) { //принадлежность точки прямой
        Vector vec1(p3, p1), vec2(p3, p2);
        return compare(vec1 * vec2, 0) <= 0;
    }

    return false;
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



class BaseShape {
public:
    virtual void shift(const Vector &) = 0;
    virtual bool check_point(double, double) = 0;
    virtual bool intersect_segment(double, double, double, double) = 0;
};

/////////////////////////////

template<int points_count>
class Polygon : public BaseShape {
protected:
    Point points[points_count];
public:
    Polygon();
    Polygon(const Point *);
    void shift(const Vector &);
    bool check_point(double, double);
    bool intersect_segment(double, double, double, double);
    double area();
};

template<int points_count>
void Polygon<points_count>::shift(const Vector &vector) {
    for (short i = 0; i < points_count; ++i) {
        this->points[i].x += vector.x;
        this->points[i].y += vector.y;
    }
}

template<int points_count>
Polygon<points_count>::Polygon() {
    for (short i = 0; i < points_count; ++i) {
        this->points[i] = 0;
    }
}

template<int points_count>
Polygon<points_count>::Polygon(const Point *points) {
    for (short i = 0; i < points_count; ++i) {
        this->points[i] = points[i];
    }
}

template<int points_count>
bool Polygon<points_count>::check_point(double x, double y) {
  //  return (x > this->points[2].x || x < this->points[1].x || y > this->points[1].y || y < this->points[0].y);
    Point p1(x, y), p2(x + 1, y);
    Line line(p1, p2);
    unsigned int count_intersect = 0;
    Line lines[points_count];
    Point intersect_point;

    for (short i = 0; i < points_count; ++i) { //проверка границ
        if (between_points(this->points[i % points_count], this->points[(i + 1) % points_count], p1))
            return true;
    }

    for (short i = 0; i < points_count; ++i) {
        lines[i].insert(this->points[i % points_count], this->points[(i + 1) % points_count]);
        if (intersection(line, lines[i], intersect_point)) { //если прямые пересекаются
            if (!intersect_point.is_none) {
                if (intersect_point.x >= p1.x && between_points(this->points[i % points_count], this->points[(i + 1) % points_count], intersect_point)) {
                    ++count_intersect;
                }
            }
        }
    }

    return count_intersect % 2 != 0;
}

template<int points_count>
bool Polygon<points_count>::intersect_segment(double x1, double y1, double x2, double y2) {
    Point p1(x1, y1), p2(x2, y2);
    Line line(p1, p2);
    Line lines[points_count];
    Point intersect_point;

    for (short i = 0; i < points_count; ++i) {
        lines[i].insert(this->points[i % points_count], this->points[(i + 1) % points_count]);
        if (intersection(line, lines[i], intersect_point)) { //если прямые пересекаются
            if (between_points(this->points[i % points_count], this->points[(i + 1) % points_count], intersect_point)) { //если true, то точка лежит на стороне
                if (between_points(p1, p2, intersect_point)) { //если точка лежит на отрезке
                    return true;
                }
            }
        }
    }

    return false;
}

template<int points_count>
double Polygon<points_count>::area() {
    double result = 0;

    for (unsigned int i = 0; i < points_count; ++i) {
        result += points[i % points_count].x * points[(i + 1) % points_count].y - points[i % points_count].y *
                                                                                  points[(i + 1) % points_count].x;
    }

    result /= 2;
    result = std::abs(result);

    return result;
}

//////////////////////////////////////////////////////

class Rectangle : public Polygon<4> {
protected:
    const unsigned int count_points = 4;
public:
    Rectangle();
    Rectangle(const Point *);
    double area();
};

Rectangle::Rectangle(): Polygon() {}
Rectangle::Rectangle(const Point *points): Polygon(points) {}

double Rectangle::area() {
    return dist_between_points(this->points[0], this->points[1]) * dist_between_points(this->points[1], this->points[2]);
}
///////////////////////////////////////////////////////

class Triangle : public Polygon<3> {
protected:
    const unsigned int points_count = 3;
public:
    Triangle();
    Triangle(const Point *);
    double area();
};

Triangle::Triangle() : Polygon() {}
Triangle::Triangle(const Point *points) : Polygon(points) {}

double Triangle::area() {
    double a, b, c;
    a = dist_between_points(this->points[0], this->points[1]);
    b = dist_between_points(this->points[1], this->points[2]);
    c = dist_between_points(this->points[2], this->points[0]);
    double p = (a + b + c) / 2.0;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}
//////////////////////////////////////////////////////



int main() {
    //task1_B
    /*
    Vector v1 (5, 1, 2, 6), v2(1, 1, 7, 8);
    cout << std::setfill('0') << std::setprecision(10) << std::fixed;
    cout << v1.length() << ' ' << v2.length() << endl;
    Vector v3 = v1 + v2;
    cout << v3.x << ' ' << v3.y << endl;
    cout << v1 * v2 << ' ';
    cout << vecMul(v1, v2) << endl;
    Point points[3];
    points[0].insert(0, 0);
    points[1].insert(v1.x, v1.y);
    points[2].insert(v2.x, v2.y);
    Triangle tr(points);
    cout << tr.area() << endl;
    */
    //task1_C
    /*
    Line line1(1, 1, -1), line2(1, -1, 0);
    cout << std::setfill('0') << std::setprecision(10) << std::fixed;
    cout << line1.a << ' ' << line1.b << endl;
    cout << line2.a << ' ' << line2.b << endl;
    Point point;

    if (intersection(line1, line2, point)) {
        cout << point.x << ' ' << point.y << endl;
    }
    else {
        cout << "lines don't intersect" << endl;
        cout << std::abs(line2.c - line1.c) / (sqrt(SQR(line1.a) + SQR(line1.b))) << endl;
    }
    */

    //task1_D
    /*
    Point point(1, 6), point1(3, 7), point2(5, 8);
    Line line(point1, point2);

    if (line.isPointOnLine(point)) { //принадлежность линии
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    if (isPointOnRay(point1, point2, point)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    if (between_points(point1, point2, point)) { //принадлежность отрезку
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
     */

    //task1_E
    /*
    Point point(3, 0), point1(1, 1), point2(2, 1);
    Line line(point1, point2);

    cout << line.distPointLine(point) << endl;
    cout << distPointRay(point1, point2, point) << endl;
    cout << distPointSegment(point1, point2, point) << endl;
     */

    //task1_F
    /*
    Point s1_1(5, 1), s1_2(2, 6), s2_1(1, 1), s2_2(7, 8);
    if (segmentIntersection(s1_1, s1_2, s2_1, s2_2)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
     */

    //task1_G
    /*
    Point s1_1(1, 1), s1_2(2, 2), s2_1(2, 1), s2_2(3, 0);
    cout << distBetweenSegments(s1_1, s1_2, s2_1, s2_2) << endl;
     */

    //task1_H
    /*
    int count_points = 3;
    Point points[3];
    points[0].insert(0, 0);
    points[1].insert(0, 1);
    points[2].insert(1, 0);

    if (isConvexPolygon(count_points, points)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    */

    //task1_I
    /*
    const int count_points = 3;

    Point point(1, 8);
    Point points[count_points];

    points[0].insert(1, 1);
    points[1].insert(10, 2);
    points[2].insert(2, 8);

    Polygon<count_points> pol(points);

    if (pol.check_point(point.x, point.y)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
     */

    //task1_J
    /*
    const int count_points = 3;
    Point points[count_points];
    points[0].insert(1, 0);
    points[1].insert(0, 1);
    points[2].insert(1, 1);

    Polygon<count_points> pol(points);

    cout << pol.area() << endl;
     */

    //task1_K

    unsigned int count_points = 5;
    Point points[count_points];
    points[0].insert(0, 0);
    points[1].insert(2, 0);
    points[2].insert(0, 2);
    points[3].insert(1, 1);
    points[4].insert(2, 2);

    Point *result = convexJarvis(count_points, points);

    cout << result[count_points].x << endl;
    printPoints(result, (unsigned int)(result[count_points].x));

/*
    Point pointsArea[(unsigned int)(result[count_points].x)];
    for (unsigned int i = 0; i < result[count_points].x; ++i) {
        pointsArea[i].insert(result[i].x, result[i].y);
    }

    Polygon<(unsigned int)(result[count_points].x)> pol(pointsArea);

    cout << pol.area() << endl;
    */

    return 0;
}