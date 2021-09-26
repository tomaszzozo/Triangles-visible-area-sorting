#include <iostream>
#include "triangle.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "myExceptions.h"
#include "point.h"
#include <functional>

#define FOV_WIDTH 16
#define FOV_HEIGHT 16

void readTriangles(std::vector<Triangle> &triangles, Point observationPoint, direction dir);
void algorithm(std::vector<Triangle> &triangles);

unsigned int Triangle::count = 0;

int main()
{
    std::cout << "Please select observation point coordinates:\n";
    Point observationPoint(0, 0, 0);
    //std::cin >> observationPoint;
    std::cout << "\nSelected point " << observationPoint << std::endl;

    std::cout << "\nSelect looking direction:\n";
    std::cout << "1.Front\n2.Back\n3.Up\n4.Down\n5.Left\n6.Right\n";
    int option = 1;
    //std::cin >> option;

    std::cout << "\nReading triangles...\n\n";
    std::vector<Triangle> triangles;
    readTriangles(triangles, observationPoint, (direction)option);
    algorithm(triangles);
}

void readTriangles(std::vector<Triangle> &triangles, Point observationPoint, direction dir)
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
            Point(std::stoi(seglist[6]), std::stoi(seglist[7]), std::stoi(seglist[8]), Triangle::count + 1),
            observationPoint,
            dir));
        std::cout << "Read triangle: " << triangles.back() << std::endl;
    }
    f.close();
}

// main algorithm of the program that is responsible for sorting the triagnles
void algorithm(std::vector<Triangle> &triangles)
{
    unsigned int fov[FOV_HEIGHT * 2][FOV_WIDTH * 2] = {0};

    for (int i = FOV_HEIGHT - 1, w = 0; i >= -FOV_HEIGHT; i--, w++)
    {
        for (int j = -FOV_WIDTH, k = 0; j < FOV_WIDTH; j++, k++)
        {
            unsigned int currentWinnerId = 0;
            int currentWinnerZ = 0;
            bool first = true;
            for (auto triangle : triangles)
            {
                std::set<Point> allPoints(triangle.fill);
                allPoints.insert(triangle.borders.p1p2.begin(), triangle.borders.p1p2.end());
                allPoints.insert(triangle.borders.p1p3.begin(), triangle.borders.p1p3.end());
                allPoints.insert(triangle.borders.p2p3.begin(), triangle.borders.p2p3.end());

                for (auto point : allPoints)
                {
                    if (point.y == i && point.x == j && point.z >= 0 && (first || point.z < currentWinnerZ))
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
            if (fov[i][j] != 0)
            {
                printf("%5d ", fov[i][j]);
            }
            else
            {
                std::cout << "      ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // calculate triangle visible areas
    for (unsigned int i = 1; i <= triangles.size(); i++)
    {
        unsigned int currentArea = 0;
        for (int w = 0; w < FOV_HEIGHT * 2; w++)
        {
            for (int k = 0; k < FOV_WIDTH * 2; k++)
            {
                if (fov[w][k] == i)
                {
                    currentArea++;
                }
            }
        }
        for (auto &triangle : triangles)
        {
            if (triangle.getId() == i)
            {
                triangle.setAreaSeen(currentArea);
                break;
            }
        }
    }

    // sort triangles by visible areas, descend
    std::sort(triangles.begin(), triangles.end(), std::greater<Triangle>());

    // display sorted triangles
    for (auto triangle : triangles)
    {
        triangle.displayIncudeId();
    }
}