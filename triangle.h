#pragma once
#include "point.h"

struct Triangle
{
    Point p1, p2, p3;

public:
    Triangle(Point &p1, Point &p2, Point &p3);
    friend std::ostream &operator<<(std::ostream &output, Triangle const &t);
};