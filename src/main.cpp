#include <iostream>
#include "Point2D.h"
#include "Polygon.h"

// static void test_poly()
// {
//     std::vector<Point2D> verts{ {.5 ,0}, {1,0}, {1,1}, {0,1} };
//     Polygon square{ verts };

//     std::cout << "Square vertices: " << std::endl;

//     std::cout << square; // Print the vertices of the square
// }

int main()  
{   
	// std::cout << sizeof(float) << std::endl;
    // std::cout << sizeof(int) << std::endl;
    // std::cout << sizeof(long) << std::endl;
    // std::cout << sizeof(double) << std::endl;
    // std::cout << sizeof(size_t) << std::endl;
    // std::cin.get();
    Point2D p1 {1, 2};
    std::cout << p1;
}
