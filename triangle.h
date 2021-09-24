#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "point.h"

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
    void setP1(Point p);
    void setP2(Point p);
    void setP3(Point p);
    Triangle(Point p1, Point p2, Point p3);
    friend std::ostream &operator<<(std::ostream &output, Triangle const &t);
};