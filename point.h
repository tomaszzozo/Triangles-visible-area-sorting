#pragma once
#include <iostream>
#include <vector>

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
    Point getMiddle(const Point &p);
    bool operator!=(const Point &p);
    bool equalsIgnoresId(const Point &p);
    bool operator<(const Point &p) const;
    bool isNeighbour(const Point &p);
};