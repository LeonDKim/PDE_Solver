#include <iostream>
#include "Point2D.h"
#include "Polygon.h"
#include "FDMGrid.h"

int main()
{   

    Polygon polygon( { {.3f,0.f}, {.5f,.5f}, {1.0f, .3f}, {1.2f , 1.0f} ,{1.0f,1.2f}, {.7f,.8f}, {0.6f,.6f}, {0.0f,.8f} } ); 

    // std::cout << "Polygon vertices: " << polygon << std::endl;
    // std::cout << "Polygon minX: " << polygon.getMinX() << std::endl;
    // std::cout << "Polygon minY: " << polygon.getMinY() << std::endl;
    // std::cout << "Polygon maxX: " << polygon.getMaxX() << std::endl;
    // std::cout << "Polygon maxY: " << polygon.getMaxY() << std::endl;

    FDMGrid grid(40, 40, polygon); 
    for (int j = grid.getNy() - 1; j >= 0; j--) {
        for(int i = 0; i < grid.getNx(); i++) {
            int celltype = static_cast<int>(grid.getCellType(i, j));
            std::cout << (celltype == -1 ? "" : " ") << static_cast<int>(celltype) << " ";
        }
        std::cout << std::endl;
    }

    return 0;


}

