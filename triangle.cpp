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
    this->p1 = p1 + observationPoint;
    this->p2 = p2 + observationPoint;
    this->p3 = p3 + observationPoint;
    this->id = ++count;

    rotate(dir);

    drawBorders();
    fillShape();
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

// recursive algorithm that fills empty space between p1 and p2 with new points which are stored in 'line' set
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

// returns set of points that would create line between p1 and p2
std::set<Point> Triangle::drawLine(Point &p1, Point &p2)
{
    std::set<Point> line;
    line.insert(p1);
    lineCreator(p1, p2, line);
    line.insert(p2);
    return line;
}

// fills borders sets with points that would create borders of current triangle
void Triangle::drawBorders()
{
    borders.p1p2 = drawLine(p1, p2);
    borders.p1p3 = drawLine(p1, p3);
    borders.p2p3 = drawLine(p2, p3);
}

// creates lines that fill up the empty space inside the triangle
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

// display info about triangle and its id
void Triangle::displayIncudeId()
{
    std::cout << "Triangle " << id << ": " << areaSeen << " pixels" << std::endl;
}

// transform triangle points to match passed looking direction
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