#include <iostream>  
#include "Polygon.h"


static void test_point2d()
{  
    Point2D p1{ 0, 0 };  
    Point2D p2{ 1, 1 };  
    Point2D p3{ 0, 1 };  
    Point2D p4{ 1, 0 };  
    std::cout << "p1: " << p1 << std::endl;  
    std::cout << "p2: " << p2 << std::endl;  
    std::cout << "p3: " << p3 << std::endl;  
    std::cout << "p4: " << p4 << std::endl;  
}
static void test_poly()
{
    std::vector<Point2D> verts{ {.5 ,0}, {1,0}, {1,1}, {0,1} };
    Polygon square{ verts };

    std::cout << "Square vertices: " << std::endl;

    std::cout << square; // Print the vertices of the square
}
int main()  
{   
    test_point2d();
    std::cin.get();
}
