#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "point.h"

enum direction
{
    UP = 3,
    DOWN = 4,
    RIGHT = 6,
    LEFT = 5,
    FRONT = 1,
    BACK = 2
};

// class containing info about a single triangle, its points and its visible area
// methods explained in trinagle.cpp file
class Triangle
{
    Point p1, p2, p3;
    unsigned int id;
    unsigned int areaSeen;
    double angleBetweenVectors(const Point vector1, const Point vector2);

public:
    static unsigned int count;
    static int maxZ;
    Point getP1();
    Point getP2();
    Point getP3();
    unsigned int getId();
    unsigned int getAreaSeen();
    void incrementArea();
    void setP1(Point p);
    void setP2(Point p);
    void setP3(Point p);
    Triangle(Point p1, Point p2, Point p3, Point observationPoint, direction dir);
    friend std::ostream &operator<<(std::ostream &output, Triangle const &t);
    bool operator>(const Triangle &t) const;
    void displayIncudeId();
    int getHighest(int x, int y, int z);
    bool isPointInside(Point p);
};