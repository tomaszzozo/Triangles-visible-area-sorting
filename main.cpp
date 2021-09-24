#include <iostream>
#include "triangle.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "myExceptions.h"
#include "point.h"

#define MAX_RANGE 1000
#define FOV_WIDTH 6
#define FOV_HEIGHT 6

void calibrate(Point &observationPoint, std::vector<Triangle> &triangles);
void readTriangles(std::vector<Triangle> &triangles);
void algorithm(std::vector<Triangle> &triangles, Point &observationPoint);

unsigned int Triangle::count = 0;

int main()
{
    std::cout << "Please select observation point coordinates:\n";
    Point observationPoint(0, 0, 0);
    // std::cin >> observationPoint;
    std::cout << "\nSelected point " << observationPoint << std::endl;

    std::cout << "\nReading triangles...\n\n";
    std::vector<Triangle> triangles;
    readTriangles(triangles);
    algorithm(triangles, observationPoint);
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
    if (!f.is_open())
    {
        throw CouldNotOpenFileException();
    }
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
    f.close();
}

// main algorithm of the program that is responsible for sorting the triagnles
void algorithm(std::vector<Triangle> &triangles, Point &observationPoint)
{
    calibrate(observationPoint, triangles);

    unsigned int fov[FOV_HEIGHT * 2][FOV_WIDTH * 2] = {0};

    for (int i = FOV_HEIGHT, w = 0; i >= -FOV_HEIGHT; i--, w++)
    {
        for (int j = -FOV_WIDTH, k = 0; j < FOV_WIDTH; j++, k++)
        {
            unsigned int currentWinnerId = 0;
            int currentWinnerZ = MAX_RANGE;
            bool first = true;
            for (auto triangle : triangles)
            {
                std::set<Point> allPoints(triangle.fill);
                allPoints.insert(triangle.borders.p1p2.begin(), triangle.borders.p1p2.end());
                allPoints.insert(triangle.borders.p1p3.begin(), triangle.borders.p1p3.end());
                allPoints.insert(triangle.borders.p2p3.begin(), triangle.borders.p2p3.end());

                for (auto point : allPoints)
                {
                    if (point.y == i && point.x == j && (first || (point.z >= 0 && point.z < currentWinnerZ)))
                    {
                        currentWinnerId = point.id;
                        currentWinnerZ = point.z;
                        first = false;
                    }
                }
            }
            fov[w][k] = currentWinnerId;
        }
    }

    // display field of view
    std::cout << "\nColours map: \n";

    for (int i = 0; i < FOV_HEIGHT * 2; i++)
    {
        for (int j = 0; j < FOV_WIDTH * 2; j++)
        {
            printf("%5d ", fov[i][j]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}