#include "triangle.h"
#include "myExceptions.h"
#include <set>
#include <cmath>
#include <vector>

// creates triagnle with given point and modifies these points to match selected observation point and looking direction
Triangle::Triangle(Point p1, Point p2, Point p3, Point observationPoint)
{
    if (p1.equalsIgnoresId(p2) || p1.equalsIgnoresId(p3) || p2.equalsIgnoresId(p3))
    {
        throw SamePointsException();
    }
    this->p1 = p1 + observationPoint;
    this->p2 = p2 + observationPoint;
    this->p3 = p3 + observationPoint;

    rotate();

    int minX = getLowest(p1.x, p2.x, p3.x),
        maxX = getHighest(p1.x, p2.x, p3.x),
        minY = getLowest(p1.y, p2.y, p3.y),
        maxY = getHighest(p1.y, p2.y, p3.y),
        minZ = getLowest(p1.z, p2.z, p3.z),
        maxZ = getHighest(p1.z, p2.z, p3.z);

    if (count == 0)
    {
        minCoords = Point(minX, minY, minZ);
        maxCoords = Point(maxX, maxY, maxZ);
    }
    else
    {
        if (minX < minCoords.x)
            minCoords.x = minX;
        if (maxX > maxCoords.x)
            maxCoords.x = maxX;
        if (minY < minCoords.y)
            minCoords.y = minY;
        if (maxY > maxCoords.y)
            maxCoords.y = maxY;
        if (minZ < minCoords.z)
            minCoords.y = minZ;
        if (maxZ > maxCoords.z)
            maxCoords.z = maxZ;
    }

    this->id = ++count;

    areaSeen = 0;
}

// getters / setters
Point Triangle::getP1() { return p1; }
Point Triangle::getP2() { return p2; }
Point Triangle::getP3() { return p3; }
void Triangle::setP1(Point p) { p1 = p; }
void Triangle::setP2(Point p) { p2 = p; }
void Triangle::setP3(Point p) { p3 = p; }
unsigned int Triangle::getId() { return id; }
void Triangle::setAreaSeen(unsigned int area) { areaSeen = area; }

// make 'cout << Trinangle' possible, display info about the points of the triangle
std::ostream &operator<<(std::ostream &output, Triangle const &t)
{
    output << '{' << t.p1 << ", " << t.p2 << ", " << t.p3 << '}';
    return output;
}

// this operator is overloaded to make sorting possible, makes 'Triangle > Triangle' possible
bool Triangle::operator>(const Triangle &t) const
{
    return areaSeen > t.areaSeen;
}

// display info about triangle and its id
void Triangle::displayIncudeId()
{
    std::cout << "Triangle " << id << ": " << areaSeen << " pixels" << std::endl;
}

// transform triangle points to match passed looking direction
void Triangle::rotate()
{
}

static int getLowest(int x, int y, int z)
{
    if (x < y)
    {
        return x < z ? x : z;
    }
    return y < z ? y : z;
}

static int getHighest(int x, int y, int z)
{
    if (x > y)
    {
        return x > z ? x : z;
    }
    return y > z ? y : z;
}
