#include <iostream>
#include "triangle.h"
#include <vector>
#include <ctime>
#include <cstdlib>

#define MAX_RANGE 1000

double calculateVisibleArea(Point observationPoint, std::vector<Triangle> triangles);

int main()
{
    srand(time(nullptr));

    std::cout << "Please select observation point coordinates:\n";
    Point observationPoint;
    std::cin >> observationPoint;
    std::cout << "\nSelected point " << observationPoint << std::endl;
    std::cout << "\nPlease input a number of triangles to be created: ";
    size_t trianglesCount;
    std::cin >> trianglesCount;
    std::cout << "\nGenerating " << trianglesCount << " triangles...\n\n";

    std::vector<Triangle> triangles;

    for (unsigned int i = 0; i < trianglesCount; i++)
    {
        Point p1((double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100, (double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100, (double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100);
        Point p2((double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100, (double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100, (double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100);
        Point p3((double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100, (double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100, (double)(rand() % (MAX_RANGE * 2 + 1) - MAX_RANGE) / 100);

        triangles.emplace_back(Triangle(p1, p2, p3));
        std::cout << "Generated triangle " << i + 1 << ": " << triangles.back() << std::endl;
    }

    std::cout << "\n\nVisible area: " << calculateVisibleArea(observationPoint, triangles) << std::endl;
}

double calculateVisibleArea(Point observationPoint, std::vector<Triangle> triangles)
{
    return 0;
}
