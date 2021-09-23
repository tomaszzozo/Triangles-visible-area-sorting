#include "point.h"

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point() {}

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

std::ostream &operator<<(std::ostream &output, Point const &p)
{
    output << '[' << p.x << ", " << p.y << ", " << p.z << ']';
    return output;
}

Point &Point::operator-=(Point &p)
{
    this->x -= p.x;
    this->y -= p.y;
    this->z -= p.z;
    return *this;
}
