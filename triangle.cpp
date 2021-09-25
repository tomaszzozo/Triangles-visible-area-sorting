#include "triangle.h"
#include "myExceptions.h"
#include <set>
#include <cmath>
#include <vector>

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

void Triangle::rotate(float roll, float pitch, float yaw)
{
    float cosa = cos(yaw);
    float sina = sin(yaw);

    float cosb = cos(pitch);
    float sinb = sin(pitch);

    float cosc = cos(roll);
    float sinc = sin(roll);

    float Axx = cosa * cosb;
    float Axy = cosa * sinb * sinc - sina * cosc;
    float Axz = cosa * sinb * cosc + sina * sinc;

    float Ayx = sina * cosb;
    float Ayy = sina * sinb * sinc + cosa * cosc;
    float Ayz = sina * sinb * cosc - cosa * sinc;

    float Azx = -sinb;
    float Azy = cosb * sinc;
    float Azz = cosb * cosc;

    std::vector<Point> temp;

    for (auto point : borders.p1p2)
    {
        point.x = (int)(Axx * point.x + Axy * point.y + Axz * point.z);
        point.y = (int)(Ayx * point.x + Ayy * point.y + Ayz * point.z);
        point.z = (int)(Azx * point.x + Azy * point.y + Azz * point.z);
        temp.push_back(point);
    }
    borders.p1p2.clear();
    for (auto point : temp)
    {
        borders.p1p2.insert(point);
    }
    temp.clear();

    for (auto point : borders.p1p3)
    {
        point.x = (int)(Axx * point.x + Axy * point.y + Axz * point.z);
        point.y = (int)(Ayx * point.x + Ayy * point.y + Ayz * point.z);
        point.z = (int)(Azx * point.x + Azy * point.y + Azz * point.z);
    }
    borders.p1p3.clear();
    for (auto point : temp)
    {
        borders.p1p3.insert(point);
    }
    temp.clear();

    for (auto point : borders.p2p3)
    {
        point.x = (int)(Axx * point.x + Axy * point.y + Axz * point.z);
        point.y = (int)(Ayx * point.x + Ayy * point.y + Ayz * point.z);
        point.z = (int)(Azx * point.x + Azy * point.y + Azz * point.z);
    }
    borders.p2p3.clear();
    for (auto point : temp)
    {
        borders.p2p3.insert(point);
    }
    temp.clear();

    for (auto point : fill)
    {
        point.x = (int)(Axx * point.x + Axy * point.y + Axz * point.z);
        point.y = (int)(Ayx * point.x + Ayy * point.y + Ayz * point.z);
        point.z = (int)(Azx * point.x + Azy * point.y + Azz * point.z);
    }
    fill.clear();
    for (auto point : temp)
    {
        fill.insert(point);
    }
    temp.clear();
}