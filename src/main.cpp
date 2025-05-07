#include <iostream>
#include "Point2D.h"
#include "Polygon.h"
#include "FDMGrid.h"

int main()
{   

    Polygon polygon( { {.3,.3}, {1,0}, {1,1},  {.5,1} } ); 

    FDMGrid grid(30, 30, polygon); // Create a grid with 10x10 points

    for(int i = 0; i < grid.getNx(); i++) {
        for (int j = grid.getNy() - 1; j >= 0; j--) {
            int celltype = static_cast<int>(grid.getCellType(i, j));
            std::cout << (celltype == -1 ? "" : " ") << static_cast<int>(celltype) << " ";
        }
        std::cout << std::endl;
    }

    return 0;


}

