#include <iostream>
#include "triangle.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "myExceptions.h"
#include "point.h"
#include <functional>

// how much of a screen does the user see
#define FOV_WIDTH 16
#define FOV_HEIGHT 16

void readTriangles(std::vector<Triangle> &triangles, Point observationPoint);
void algorithm(std::vector<Triangle> &triangles);

// static variable that keeps track of created triangles count and also max and min coordinates
unsigned int Triangle::count = 0;
Point Triangle::minCoords = Point(0, 0, 0), Triangle::maxCoords = Point(0, 0, 0);

int main()
{
    // select observation point
    std::cout << "Please select observation point coordinates:\n";
    Point observationPoint(0, 0, 0);
    std::cin >> observationPoint;
    std::cout << "\nSelected point " << observationPoint << std::endl;

    // read triangles from file
    std::cout << "\nReading triangles...\n\n";
    std::vector<Triangle> triangles;
    readTriangles(triangles, observationPoint);

    // display triangles sorted by largest visible area
    algorithm(triangles);
}

void readTriangles(std::vector<Triangle> &triangles, Point observationPoint)
{
    std::ifstream f("triangles.txt");
    if (!f.is_open())
    {
        throw CouldNotOpenFileException();
    }

    std::string data;
    // read file line by line
    while (getline(f, data))
    {
        // replace all ';' in line with ','
        std::replace(data.begin(), data.end(), ';', ',');
        std::stringstream temp(data);
        std::vector<std::string> seglist;
        std::string segment;
        // create a list with strings between ','
        while (std::getline(temp, segment, ','))
        {
            seglist.push_back(segment);
        }
        // check if list is correct in size
        if (seglist.size() != 9)
        {
            throw FileCorruptedException();
        }
        // add new triangle to set based on the coordinates in the list
        triangles.push_back(Triangle(
            Point(std::stoi(seglist[0]), std::stoi(seglist[1]), std::stoi(seglist[2]), Triangle::count + 1),
            Point(std::stoi(seglist[3]), std::stoi(seglist[4]), std::stoi(seglist[5]), Triangle::count + 1),
            Point(std::stoi(seglist[6]), std::stoi(seglist[7]), std::stoi(seglist[8]), Triangle::count + 1),
            observationPoint));
        std::cout << "Read triangle: " << triangles.back() << std::endl;
    }

    f.close();
}

void algorithm(std::vector<Triangle> &triangles)
{
}