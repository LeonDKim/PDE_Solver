#include <iostream>
#include "Point2D.h"
#include "Polygon.h"
#include "FDMGrid.h"

int main()
{   

    Polygon polygon( { {.3,0}, {.5,.5}, {1.2 , 1} ,{1,1.2}, {.7,1}, {0,.5}, {0,.2} } ); 

    // std::cout << "Polygon vertices: " << polygon << std::endl;
    // std::cout << "Polygon minX: " << polygon.getMinX() << std::endl;
    // std::cout << "Polygon minY: " << polygon.getMinY() << std::endl;
    // std::cout << "Polygon maxX: " << polygon.getMaxX() << std::endl;
    // std::cout << "Polygon maxY: " << polygon.getMaxY() << std::endl;

    FDMGrid grid(30, 30, polygon); 
    for (int j = grid.getNy() - 1; j >= 0; j--) {
        for(int i = 0; i < grid.getNx(); i++) {
            int celltype = static_cast<int>(grid.getCellType(i, j));
            std::cout << (celltype == -1 ? "" : " ") << static_cast<int>(celltype) << " ";
        }
        std::cout << std::endl;
    }

    return 0;


}

