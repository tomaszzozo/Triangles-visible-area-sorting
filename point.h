#pragma once
#include <iostream>

struct Point
{
    int x, y, z;
    Point();
    Point(int x, int y, int z);
    friend std::istream &operator>>(std::istream &input, Point &p);
    friend std::ostream &operator<<(std::ostream &output, Point const &p);
    Point &operator-=(Point &p);
};