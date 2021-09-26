#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "point.h"

// enum containing information about where does the user want to look
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
    static void lineCreator(Point &p1, Point &p2, std::set<Point> &line);
    static std::set<Point> drawLine(Point &p1, Point &p2);
    void drawBorders();
    void fillShape();

public:
    static unsigned int count;
    struct Border
    {
        std::set<Point> p1p2;
        std::set<Point> p1p3;
        std::set<Point> p2p3;
    };
    Border borders;
    std::set<Point> fill;
    Point getP1();
    Point getP2();
    Point getP3();
    unsigned int getId();
    void setAreaSeen(unsigned int area);
    void setP1(Point p);
    void setP2(Point p);
    void setP3(Point p);
    Triangle(Point p1, Point p2, Point p3, Point observationPoint, direction dir);
    friend std::ostream &operator<<(std::ostream &output, Triangle const &t);
    bool operator>(const Triangle &t) const;
    void displayIncudeId();
    void rotate(direction dir);
};