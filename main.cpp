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

void readTriangles(std::vector<Triangle> &triangles, Point observationPoint, direction dir);
void algorithm(std::vector<Triangle> &triangles);

// static variable that keeps track of created triangles count
unsigned int Triangle::count = 0;

int main()
{
    // select observation point
    std::cout << "Please select observation point coordinates:\n";
    Point observationPoint(0, 0, 0);
    std::cin >> observationPoint;
    std::cout << "\nSelected point " << observationPoint << std::endl;

    // select looking direction
    std::cout << "\nSelect looking direction:\n";
    std::cout << "1.Front\n2.Back\n3.Up\n4.Down\n5.Left\n6.Right\n";
    int option = 1;
    std::cin >> option;

    // read triangles from file
    std::cout << "\nReading triangles...\n\n";
    std::vector<Triangle> triangles;
    readTriangles(triangles, observationPoint, (direction)option);

    // display triangles sorted by largest visible area
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
                // get all points from current triangle into one set
                std::set<Point> allPoints(triangle.fill);
                allPoints.insert(triangle.borders.p1p2.begin(), triangle.borders.p1p2.end());
                allPoints.insert(triangle.borders.p1p3.begin(), triangle.borders.p1p3.end());
                allPoints.insert(triangle.borders.p2p3.begin(), triangle.borders.p2p3.end());

                for (auto point : allPoints)
                {
                    // if this point has this pixels coordinates and is either first or has current lowest z, update current lowest z and set this point as current winner
                    if (point.y == i && point.x == j && point.z >= 0 && (first || point.z < currentWinnerZ))
                    {
                        currentWinnerId = point.id;
                        currentWinnerZ = point.z;
                        first = false;
                    }
                }
            }
            // set this pixels color to id of the point that won the comparison or if there are no points set it to 0
            fov[w][k] = currentWinnerId;
        }
    }

    std::cout << "\nColours map: \n";

    // display color map
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

    // calculate visible area for each triangle
    for (unsigned int i = 1; i <= triangles.size(); i++)
    {
        unsigned int currentArea = 0;
        for (int w = 0; w < FOV_HEIGHT * 2; w++)
        {
            for (int k = 0; k < FOV_WIDTH * 2; k++)
            {
                // if this pixel has value of current i, add 1 to current area
                if (fov[w][k] == i)
                {
                    currentArea++;
                }
            }
        }
        for (auto &triangle : triangles)
        {
            // find a triangle with id equal to i and set it visible area calculated in the previous loop
            if (triangle.getId() == i)
            {
                triangle.setAreaSeen(currentArea);
                break;
            }
        }
    }

    // sort set using our custom defined '>' operator which returns triangle with bigger visible area
    std::sort(triangles.begin(), triangles.end(), std::greater<Triangle>());

    // display sorted triangles with their id's
    for (auto triangle : triangles)
    {
        triangle.displayIncudeId();
    }
}