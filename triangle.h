#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "point.h"

// class containing info about a single triangle, its points and its visible area
// methods explained in trinagle.cpp file
class Triangle
{
    Point p1, p2, p3;
    unsigned int id;
    unsigned int areaSeen;

public:
    static unsigned int count;
    static Point minCoords, maxCoords;
    Point getP1();
    Point getP2();
    Point getP3();
    unsigned int getId();
    void setAreaSeen(unsigned int area);
    void setP1(Point p);
    void setP2(Point p);
    void setP3(Point p);
    Triangle(Point p1, Point p2, Point p3, Point observationPoint);
    friend std::ostream &operator<<(std::ostream &output, Triangle const &t);
    bool operator>(const Triangle &t) const;
    void displayIncudeId();
    void rotate();
    bool pointInTriangle(Point p);
    static int getLowest(int x, int y, int z);
    static int getHighest(int x, int y, int z);
};