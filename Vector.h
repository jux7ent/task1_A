#pragma once

class Point;

class Vector {

    friend double vecMul(const Vector &, const Vector &);

    friend double scalarMul(const Vector &first_vector, const Vector &second_vector);

    friend void  printCoords(const Vector &vector);

    friend Vector operator + (const Vector &first_vector, const Vector &second_vector);

    friend Vector operator - (const Vector &first_vector, const Vector &second_vector);

    friend Vector plus_minus(const Vector &first_vector, const Vector &second_vector, bool sign); //true - '+', false - '-'

private:

    double x_, y_;

public:

    Vector();

    Vector(double x, double y);

    Vector(double point1_x, double point1_y, double point2_x, double point2_y);

    Vector (const Point &first_point, const Point &second_point);

    void update(const Point &first_point, const Point &second_point);

    double x() const;

    double y() const;

    double length();
};