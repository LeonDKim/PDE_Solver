#include <iostream>
#include "Point2D.h"
#include "Polygon.h"
#include "FDMGrid.h"

int main()
{   

    Polygon polygon( { {0,0}, {1,0}, {1,1},    {0,1} } ); 
    std::cout << "Polygon vertices: " << polygon << std::endl;
    std::cout << "is on boundary: " << polygon.isOnBoundary({1, 2}) << std::endl;
    return 0;


}

