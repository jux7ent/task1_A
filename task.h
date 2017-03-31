#pragma once

#include <iostream>
#include "Point.h"
#include "other_func.h"
#include "Vector.h"
#include "Line.h"
#include "Ray.h"
#include "Segment.h"
#include "Polygon.h"


using std::cout;
using std::cin;
using std::endl;

void B() {

    double point1_x, point1_y, point2_x, point2_y;

    cin >> point1_x >> point1_y >> point2_x >> point2_y;

    Vector first_vector(point1_x, point1_y, point2_x, point2_y);

    cin >> point1_x >> point1_y >> point2_x >> point2_y;

    Vector second_vector(point1_x, point1_y, point2_x, point2_y);


    cout << first_vector.length() << ' ' << second_vector.length() << endl;

    Vector sum_vector = first_vector + second_vector;

    cout << sum_vector.x() << ' ' << sum_vector.y() << endl;

    cout << scalarMul(first_vector, second_vector) << ' ' << vecMul(first_vector, second_vector) << endl;

    Point input_points[3];

    input_points[0].insert(0, 0);
    input_points[1].insert(first_vector.x(), first_vector.y());
    input_points[2].insert(second_vector.x(), second_vector.y());

    cout << area(3, input_points);

}

void C() {

    double x, y;

    cin >> x >> y;

    Point first_point(x, y);

    cin >> x >> y;

    Point second_point(x, y);

    cin >> x >> y;

    Point third_point(x, y);

    cin >> x >> y;

    Point fourth_point(x, y);

    Line first_line(first_point, second_point);
    Line second_line(third_point, fourth_point);

    cout << first_line.b() << ' ' << -first_line.a() << endl;
    cout << second_line.b() << ' ' << -second_line.a() << endl;

    if (intersection(first_line, second_line) == 1) {

        Point *intersect_point = intersection_point(first_line, second_line);

        cout << intersect_point->x() << ' ' << intersect_point->y() << endl;

        delete intersect_point;

    }
    else if (intersection(first_line, second_line) == 2) {
        cout << 0 << endl;
    }
    else {

        cout << first_line.distance_to_line(second_line) << endl;

    }

}

void D() {

    double x, y;

    cin >> x >> y;

    Point c(x, y);

    cin >> x >> y;

    Point a(x, y);

    cin >> x >> y;

    Point b(x, y);

    Line line(a, b);
    Ray ray(a, b);
    Segment segment(a, b);

    if (c.belong_to_line(line))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;


    if (c.belong_to_ray(ray))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;


    if (c.belong_to_segment(segment))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

}

void E() {

    double x, y;

    cin >> x >> y;

    Point c(x, y);

    cin >> x >> y;

    Point a(x, y);

    cin >> x >> y;

    Point b(x, y);

    Line line(a, b);
    Ray ray(a, b);
    Segment segment(a, b);

    cout << line.distance_to_point(c) << endl;
    cout << ray.distance_to_point(c) << endl;
    cout << segment.distance_to_point(c) << endl;

}

void F() {

    double point1_x, point1_y, point2_x, point2_y;

    cin >> point1_x >> point1_y >> point2_x >> point2_y;

    Segment first_segment(point1_x, point1_y, point2_x, point2_y);

    cin >> point1_x >> point1_y >> point2_x >> point2_y;

    Segment second_segment(point1_x, point1_y, point2_x, point2_y);

    if (intersection(first_segment, second_segment)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

}

void G() {

    double point1_x, point1_y, point2_x, point2_y;

    cin >> point1_x >> point1_y >> point2_x >> point2_y;

    Segment first_segment(point1_x, point1_y, point2_x, point2_y);

    cin >> point1_x >> point1_y >> point2_x >> point2_y;

    Segment second_segment(point1_x, point1_y, point2_x, point2_y);

    cout << first_segment.distance_to_segment(second_segment) << endl;
}

void H() {

    unsigned int points_count;

    cin >> points_count;

    Point *points = new Point[points_count];

    for (unsigned int i = 0; i < points_count; ++i) {

        int x, y;

        cin >> x >> y;

        points[i].insert(x, y);

    }

    if (isConvexPolygon(points, points_count))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;


    delete[] points;
}

void I() {

    unsigned int points_count;
    double x, y;

    cin >> points_count >> x >> y;

    Point verified_point(x, y);

    Point *points = new Point[points_count];

    for (unsigned int i = 0; i < points_count; ++i) {

        cin >> x >> y;

        points[i].insert(x, y);

    }

    if (check_point(verified_point, points, points_count))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;


    delete[] points;
}

void J() {

    unsigned int points_count;

    cin >> points_count;

    Point *points = new Point[points_count];

    for (unsigned int i = 0; i < points_count; ++i) {

        double x, y;

        cin >> x >> y;

        points[i].insert(x, y);

    }

    cout << area(points_count, points) << endl;

    delete[] points;
}

void K() {

    unsigned int points_count;

    cin >> points_count;

    Point *points = new Point[points_count];

    for (unsigned int i = 0; i < points_count; ++i) {

        double x, y;

        cin >> x >> y;

        points[i].insert(x, y);

    }

    Point *result = convexJarvis(points_count, points);

    cout << result[points_count].x() << endl;
    printPoints((unsigned int)(result[points_count].x()), result);

    cout << area((unsigned int)(result[points_count].x()), result) << endl;


    delete[] points;
}