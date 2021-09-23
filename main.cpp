#include <iostream>
#include "triangle.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "fileCorruptedException.h"

#define MAX_RANGE 1000

void calibrate(Point &observationPoint, std::vector<Triangle> &triangles);
void readTriangles(std::vector<Triangle> &triangles);

int main()
{
    std::cout << "Please select observation point coordinates:\n";
    Point observationPoint;
    // std::cin >> observationPoint;
    observationPoint.x = 3;
    observationPoint.y = 3;
    observationPoint.z = 3;
    std::cout << "\nSelected point " << observationPoint << std::endl;

    std::cout << "\nReading triangles...\n\n";
    std::vector<Triangle> triangles;
    readTriangles(triangles);

    calibrate(observationPoint, triangles);
}

// moves observation point to [0, 0, 0] and adjusts triangles accordingly
void calibrate(Point &observationPoint, std::vector<Triangle> &triangles)
{
    for (auto triangle : triangles)
    {
        triangle.p1 -= observationPoint;
        triangle.p2 -= observationPoint;
        triangle.p3 -= observationPoint;
    }
    observationPoint = Point(0, 0, 0);
}

// reads data from "triangles.txt"
void readTriangles(std::vector<Triangle> &triangles)
{
    std::ifstream f("triangles.txt");
    std::string data;
    while (getline(f, data))
    {
        std::replace(data.begin(), data.end(), ';', ',');
        std::stringstream temp(data);
        std::vector<std::string> seglist;
        std::string segment;
        while (std::getline(temp, segment, ','))
        {
            seglist.push_back(segment);
        }
        if (seglist.size() != 9)
        {
            throw FileCorruptedException();
        }
        triangles.push_back(Triangle(
            Point(std::stoi(seglist[0]), std::stoi(seglist[1]), std::stoi(seglist[2])),
            Point(std::stoi(seglist[3]), std::stoi(seglist[4]), std::stoi(seglist[5])),
            Point(std::stoi(seglist[6]), std::stoi(seglist[7]), std::stoi(seglist[8]))));
        std::cout << "Read triangle: " << triangles.back() << std::endl;
    }
}
