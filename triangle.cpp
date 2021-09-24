#include "triangle.h"
#include "myExceptions.h"

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    if (p1.equalsIgnoresId(p2) || p1.equalsIgnoresId(p3) || p2.equalsIgnoresId(p3))
    {
        throw SamePointsException();
    }
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->id = ++count;
    drawBorders();
    fillBorders();
    areaSeen = 0;
}

Point Triangle::getP1() { return p1; }
Point Triangle::getP2() { return p2; }
Point Triangle::getP3() { return p3; }
void Triangle::setP1(Point p) { p1 = p; }
void Triangle::setP2(Point p) { p2 = p; }
void Triangle::setP3(Point p) { p3 = p; }

std::ostream &operator<<(std::ostream &output, Triangle const &t)
{
    output << '{' << t.p1 << ", " << t.p2 << ", " << t.p3 << '}';
    return output;
}

void Triangle::lineCreator(Point &p1, Point &p2, std::vector<Point> &line)
{
    Point middle = p1.getMiddle(p2);
    if (middle != p1 || middle != p2)
    {
        lineCreator(p1, middle, line);
        line.emplace_back(middle);
        lineCreator(middle, p2, line);
    }
}

std::vector<Point> Triangle::drawLine(Point &p1, Point &p2)
{
    std::vector<Point> line;
    lineCreator(p1, p2, line);
    return line;
}

void Triangle::drawBorders()
{
    borders.p1p2 = drawLine(p1, p2);
    borders.p1p3 = drawLine(p1, p3);
    borders.p2p3 = drawLine(p2, p3);
}

void Triangle::fillBorders()
{
    for (auto point : borders.p2p3)
    {
        fill = drawLine(p1, point);
    }
    for (auto point : borders.p1p2)
    {
        fill += drawLine(p3, point);
    }
    for (auto point : borders.p1p3)
    {
        fill += drawLine(p2, point);
    }
}
