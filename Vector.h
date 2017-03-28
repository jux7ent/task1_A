#pragma once

#include <iostream>
#include <cmath>
#include "Point.h"

class Vector {
private:
    friend Vector plus_minus(const Vector &, const Vector &, bool); //true - '+', false - '-'
public:
    double x, y;
    Vector();
    Vector(double, double);
    Vector(const Point &, const Point &);
    Vector(double, double, double, double);
    void update(const Point &, const Point &);
    friend double vecMul(const Vector &, const Vector &);
    friend void  printCoords(const Vector &);
    friend Vector operator + (const Vector &, const Vector &);
    friend Vector operator - (const Vector &, const Vector &);
    friend double operator * (const Vector &, const Vector &);
    friend std::ostream &operator << (std::ostream &, const Vector &);
    double length();
};