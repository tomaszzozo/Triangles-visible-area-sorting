#pragma once
#include <iostream>

struct Point
{
    double x, y, z;
    Point();
    Point(double x, double y, double z);
    friend std::istream &operator>>(std::istream &input, Point &p);
    friend std::ostream &operator<<(std::ostream &output, Point const &p);
    Point &operator-=(Point &p);
};