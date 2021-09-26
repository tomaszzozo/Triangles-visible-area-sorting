#include "triangle.h"
#include "myExceptions.h"
#include <set>
#include <cmath>
#include <vector>

Triangle::Triangle(Point p1, Point p2, Point p3, Point observationPoint, direction dir)
{
    if (p1.equalsIgnoresId(p2) || p1.equalsIgnoresId(p3) || p2.equalsIgnoresId(p3))
    {
        throw SamePointsException();
    }
    this->p1 = p1 + observationPoint;
    this->p2 = p2 + observationPoint;
    this->p3 = p3 + observationPoint;
    this->id = ++count;

    rotate(dir);

    drawBorders();
    fillShape();
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

void Triangle::lineCreator(Point &p1, Point &p2, std::set<Point> &line)
{
    if (!p1.isNeighbour(p2))
    {
        Point middle = p1.getMiddle(p2);
        lineCreator(p1, middle, line);
        line.insert(middle);
        lineCreator(middle, p2, line);
    }
}

std::set<Point> Triangle::drawLine(Point &p1, Point &p2)
{
    std::set<Point> line;
    line.insert(p1);
    lineCreator(p1, p2, line);
    line.insert(p2);
    return line;
}

void Triangle::drawBorders()
{
    borders.p1p2 = drawLine(p1, p2);
    borders.p1p3 = drawLine(p1, p3);
    borders.p2p3 = drawLine(p2, p3);
}

void Triangle::fillShape()
{
    for (auto point : borders.p2p3)
    {
        std::set<Point> line = drawLine(p1, point);
        fill.insert(line.begin(), line.end());
    }
    for (auto point : borders.p1p2)
    {
        std::set<Point> line = drawLine(p3, point);
        fill.insert(line.begin(), line.end());
    }
    for (auto point : borders.p1p3)
    {
        std::set<Point> line = drawLine(p2, point);
        fill.insert(line.begin(), line.end());
    }
}

unsigned int Triangle::getId()
{
    return id;
}

void Triangle::setAreaSeen(unsigned int area)
{
    areaSeen = area;
}

bool Triangle::operator>(const Triangle &t) const
{
    return areaSeen > t.areaSeen;
}

void Triangle::displayIncudeId()
{
    std::cout << "Triangle " << id << ": " << areaSeen << " pixels" << std::endl;
}

void Triangle::rotate(direction dir)
{
    switch (dir)
    {
    case FRONT:
        return;

    case BACK:
        p1.z *= -1;
        p2.z *= -1;
        p3.z *= -1;
        break;

    case RIGHT:
        std::swap(p1.x, p1.z);
        std::swap(p2.x, p2.z);
        std::swap(p3.x, p3.z);
        p1.x *= -1;
        p2.x *= -1;
        p3.x *= -1;
        break;

    case UP:
        p1.y *= -1;
        p2.y *= -1;
        p3.y *= -1;
        std::swap(p1.y, p1.z);
        std::swap(p2.y, p2.z);
        std::swap(p3.y, p3.z);
        break;

    case DOWN:
        std::swap(p1.y, p1.z);
        std::swap(p2.y, p2.z);
        std::swap(p3.y, p3.z);
        p1.y *= -1;
        p2.y *= -1;
        p3.y *= -1;
        break;

    case LEFT:
        p1.x *= -1;
        p2.x *= -1;
        p3.x *= -1;
        std::swap(p1.x, p1.z);
        std::swap(p2.x, p2.z);
        std::swap(p3.x, p3.z);
        break;

    default:
        throw IncorrectDirectionException();
    }
}