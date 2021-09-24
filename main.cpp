#include <iostream>
#include "triangle.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "myExceptions.h"
#include "point.h"

#define MAX_RANGE 1000
#define FOV_WIDTH 10
#define FOV_HEIGHT 10

void calibrate(Point &observationPoint, std::vector<Triangle> &triangles);
void readTriangles(std::vector<Triangle> &triangles);
void algorithm(std::vector<Triangle> &triangles, Point &observationPoint);

unsigned int Triangle::count = 0;

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
}

// moves observation point to [0, 0, 0] and adjusts triangles accordingly
void calibrate(Point &observationPoint, std::vector<Triangle> &triangles)
{
    for (auto triangle : triangles)
    {
        triangle.setP1(triangle.getP1() - observationPoint);
        triangle.setP2(triangle.getP2() - observationPoint);
        triangle.setP3(triangle.getP3() - observationPoint);
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
            Point(std::stoi(seglist[0]), std::stoi(seglist[1]), std::stoi(seglist[2]), Triangle::count + 1),
            Point(std::stoi(seglist[3]), std::stoi(seglist[4]), std::stoi(seglist[5]), Triangle::count + 1),
            Point(std::stoi(seglist[6]), std::stoi(seglist[7]), std::stoi(seglist[8]), Triangle::count + 1)));
        std::cout << "Read triangle: " << triangles.back() << std::endl;
    }
}

// main algorithm of the program that is responsible for sorting the triagnles
void algorithm(std::vector<Triangle> &triangles, Point &observationPoint)
{
    calibrate(observationPoint, triangles);

    unsigned int fov[FOV_HEIGHT * 2][FOV_WIDTH * 2] = {0};

    for (int i = -FOV_HEIGHT; i < FOV_HEIGHT; i++)
    {
        for (int j = -FOV_WIDTH; j < FOV_WIDTH; j++)
        {
            unsigned int currentWinnerId = 0;
            int currentWinnerZ = MAX_RANGE;
            for (auto triangle : triangles)
            {
                for (auto point : triangle.borders.p1p2)
                {
                }
                for (auto point : triangle.borders.p1p3)
                {
                }
                for (auto point : triangle.borders.p2p3)
                {
                }
                for (auto point : triangle.fill)
                {
                }
            }
        }
    }

    // display field of view
    for (int i = -FOV_HEIGHT; i < FOV_HEIGHT; i++)
    {
        for (int j = -FOV_WIDTH; j < FOV_WIDTH; j++)
        {
            std::cout << fov[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}