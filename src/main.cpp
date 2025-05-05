#include <iostream>
#include "Point2D.h"
#include "Polygon.h"

int main()
{   
	// std::cout << sizeof(float) << std::endl;
    // std::cout << sizeof(int) << std::endl;
    // std::cout << sizeof(long) << std::endl;
    // std::cout << sizeof(double) << std::endl;
    // std::cout << sizeof(size_t) << std::endl;
    // std::cin.get();
    Polygon polygon( { {1,2}, {3,4},{5,6} } );
    std::cout << "Polygon vertices: " << polygon << std::endl;
}

