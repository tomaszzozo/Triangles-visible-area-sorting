#include "point.h"
#include <cmath>
#include <vector>

// creates point with given coords and id 0
Point::Point(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    id = 0;
}

// creates point with given coords and given id
Point::Point(int x, int y, int z, unsigned int id)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->id = id;
}

// creates point with exact same values as the passed point (copies it)
Point::Point(const Point &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    id = p.id;
}

// takes info about current point, makes 'cin >> Point' possible
std::istream &operator>>(std::istream &input, Point &p)
{
    std::cout << "x: ";
    input >> p.x;
    std::cout << "y: ";
    input >> p.y;
    std::cout << "z: ";
    input >> p.z;
    return input;
}

// displays info about current point, makes 'cout << Point' possible
std::ostream &operator<<(std::ostream &output, Point const &p)
{
    output << '[' << p.x << ", " << p.y << ", " << p.z << ']';
    return output;
}

// makes adding points possible
Point Point::operator+(const Point &p)
{
    return Point(x + p.x, y + p.y, z + p.z, id);
}

// return a Point that is in the middle between current Point and p
Point Point::getMiddle(const Point &p)
{
    int a = ceil((float)(p.x + x) / 2);
    int b = ceil((float)(p.y + y) / 2);
    int c = ceil((float)(p.z + z) / 2);
    return Point(a, b, c, id);
}

// makes 'Point != Point' possible
bool Point::operator!=(const Point &p)
{
    return x != p.x || y != p.y || z != p.z || id != p.id;
}

// compares two points but ignores their id's
bool Point::equalsIgnoresId(const Point &p)
{
    return x == p.x && y == p.y && z == p.z;
}

// implemented to make set<Point> available to use, makes 'Point < Point' possible
bool Point::operator<(const Point &p) const
{
    if (x == p.x)
    {
        if (y == p.y)
        {
            return z < p.z;
        }
        return y < p.y;
    }
    return x < p.x;
}

// returns true if p is 1 pixel away from current Point
bool Point::isNeighbour(const Point &p)
{
    return (x - p.x == 0 || abs(x - p.x) == 1) && (y - p.y == 0 || abs(y - p.y) == 1) && (z - p.z == 0 || abs(z - p.z) == 1);
}
