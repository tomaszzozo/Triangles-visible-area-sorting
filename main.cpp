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
#define FOV_WIDTH 100
#define FOV_HEIGHT 100

void readTriangles(std::vector<Triangle> &triangles, Point observationPoint, direction dir);
void algorithm(std::vector<Triangle> &triangles);

// static variable that keeps track of created triangles count and also max depth
unsigned int Triangle::count = 0;
Point Triangle::maxCoords, Triangle::minCoords;

int main()
{
    // select observation point
    std::cout << "Please select observation point coordinates:\n";
    Point observationPoint(0, 0, 0);
    std::cin >> observationPoint;
    std::cout << "\nSelected point " << observationPoint << std::endl;

    std::cout << "\nSelect looking direction:\n";
    std::cout << "1.Forward\n2.Backward\n3.Up\n4.Down\n5.Left\n6.Right\n";
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
    std::cout << std::endl;
    f.close();
}

void algorithm(std::vector<Triangle> &triangles)
{
    Point start(Triangle::minCoords.x > -FOV_WIDTH ? Triangle::minCoords.x : -FOV_WIDTH, Triangle::maxCoords.y < FOV_HEIGHT - 1 ? Triangle::maxCoords.y : FOV_HEIGHT - 1, Triangle::minCoords.z > 0 ? Triangle::minCoords.z : 0),
        stop(Triangle::maxCoords.x < FOV_WIDTH ? Triangle::maxCoords.x : FOV_WIDTH, Triangle::minCoords.y > -FOV_HEIGHT ? Triangle::minCoords.y : -FOV_HEIGHT, Triangle::maxCoords.z);

    std::cout << "Field of view (empty space around ignored):\n\n";
    // iterate through every FOV row
    for (int y = start.y; y >= stop.y; y--)
    {
        // iterate through every FOX column
        for (int x = start.x; x <= stop.x; x++)
        {
            bool found = false;
            // iterate thorugh every depth
            for (int z = start.z; z <= stop.z; z++)
            {
                // flag for moving onto nextx pixel if point was found
                found = false;
                // iterate through every triangle
                for (auto &triangle : triangles)
                {
                    // if current point (x,y,z) is inside current triangle, increment its area and move onto the next pixel
                    if (triangle.isPointInside(Point(x, y, z)))
                    {
                        triangle.incrementArea();
                        std::cout << triangle.getId();
                        found = true;
                        break;
                    }
                }
                // if point was found stop adding to depth
                if (found)
                    break;
            }
            if (!found)
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // sort triangles by visible areas, descend
    std::sort(triangles.begin(), triangles.end(), std::greater<Triangle>());

    // display sorted triangles
    for (auto triangle : triangles)
    {
        triangle.displayIncudeId();
    }
}
