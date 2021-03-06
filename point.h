#pragma once
#include <iostream>
#include <vector>

// structure that holds information about a single Point (x, y, z) and providing a set of methods to work with it
struct Point
{
    int x, y, z;
    unsigned int id;

    Point();
    Point(int x, int y, int z);
    Point(int x, int y, int z, unsigned int id);
    Point(const Point &p);
    friend std::istream &operator>>(std::istream &input, Point &p);
    friend std::ostream &operator<<(std::ostream &output, Point const &p);
    Point operator+(const Point &p);
    bool equalsIgnoresId(const Point &p);
};