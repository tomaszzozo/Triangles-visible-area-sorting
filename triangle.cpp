#include "triangle.h"
#include "myExceptions.h"
#include <set>
#include <cmath>
#include <vector>

// creates triagnle with given point and modifies these points to match selected observation point and looking direction
Triangle::Triangle(Point p1, Point p2, Point p3, Point observationPoint, direction dir)
{
    if (p1.equalsIgnoresId(p2) || p1.equalsIgnoresId(p3) || p2.equalsIgnoresId(p3))
    {
        throw SamePointsException();
    }
    // move this triangle points accordingly to observation point
    this->p1 = p1 + observationPoint;
    this->p2 = p2 + observationPoint;
    this->p3 = p3 + observationPoint;

    Point thisMax(getHighest(p1.x, p2.x, p3.x), getHighest(p1.y, p2.y, p3.y), getHighest(p1.z, p2.z, p3.z));
    Point thisMin(getLowest(p1.x, p2.x, p3.x), getLowest(p1.y, p2.y, p3.y), getLowest(p1.z, p2.z, p3.z));

    if (count == 0)
    {
        maxCoords = thisMax;
        minCoords = thisMin;
    }
    else
    {
        if (maxCoords.x < thisMax.x)
            maxCoords.x = thisMax.x;
        if (minCoords.x > thisMin.x)
            minCoords.x = thisMin.x;

        if (maxCoords.y < thisMax.y)
            maxCoords.y = thisMax.y;
        if (minCoords.y > thisMin.y)
            minCoords.y = thisMin.y;

        if (maxCoords.z < thisMax.z)
            maxCoords.z = thisMax.z;
        if (minCoords.z > thisMin.z)
            minCoords.z = thisMin.z;
    }

    id = ++count;

    // transform points if we are not looking forward
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

int Triangle::getHighest(int x, int y, int z)
{
    if (x > y)
    {
        return x > z ? x : z;
    }
    return y > z ? y : z;
}

void Triangle::incrementArea()
{
    areaSeen++;
}

bool Triangle::isPointInside(Point p)
{
    // if point is one of triangle vericies, simply return true
    if (p.equalsIgnoresId(p1) || p.equalsIgnoresId(p2) || p.equalsIgnoresId(p3))
        return true;

    /*  
        Angle Test
        A common way to check if a point is in a triangle is to find the vectors connecting the point to each of the triangle's 
        three vertices and sum the angles between those vectors. If the sum of the angles is 2*pi then the point is inside the triangle, 
        otherwise it is not.
    */
    Point vP1(p1.x - p.x, p1.y - p.y, p1.z - p.z);
    Point vP2(p2.x - p.x, p2.y - p.y, p2.z - p.z);
    Point vP3(p3.x - p.x, p3.y - p.y, p3.z - p.z);

    double equation = angleBetweenVectors(vP1, vP2) + angleBetweenVectors(vP2, vP3) + angleBetweenVectors(vP1, vP3);

    // leave 0.1 headroom for errors since computers have problems with floats
    return abs(2 * M_PI - equation) < 0.1;
}

// calculate angle between vectors
double Triangle::angleBetweenVectors(const Point vector1, const Point vector2)
{
    return acos((double)(vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z) / (sqrt(vector1.x * vector1.x + vector1.y * vector1.y + vector1.z * vector1.z) * sqrt(vector2.x * vector2.x + vector2.y * vector2.y + vector2.z * vector2.z)));
}

int Triangle::getLowest(int x, int y, int z)
{
    if (x < y)
    {
        return x < z ? x : z;
    }
    return y < z ? y : z;
}
