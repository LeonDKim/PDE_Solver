#pragma once
#include "Polygon.h"
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * @brief enum class representing the type of grid cell.
 * UNDEFINED: Cell type is not defined.
 * BOUNDARY: Cell is part of the polygon boundary.
 * INTERIOR: Cell is inside the polygon.
 * EXTERIOR: Cell is outside the polygon.
 */
enum GridType: int8_t {
    UNDEFINED = -1,
    BOUNDARY = 0,
    INTERIOR = 1,
    EXTERIOR = 2
};

/**
 * @brief Class representing a 2D grid for Finite Difference Method (FDM) discretization.
 * The grid is used to classify cells as interior, exterior, or boundary based on a polygon.
 */
class FDMGrid {
private:

/*====================================  Attributes  =========================================*/

    float originX, originY;  /// @brief Bottom-left corner of the grid
    float dx, dy;            /// @brief Grid spacing
    int nx, ny;              /// @brief Number of grid points in each direction
    std::vector<std::vector<GridType>> gridMatrix; /// @brief Matrix storing cell classifications
    
public:
/*====================================  Constructor  =========================================*/

    /**
     * @brief Constructs a grid based on the provided polygon.
     * @param nx_ Number of grid points in x-direction.
     * @param ny_ Number of grid points in y-direction.
     * @param polygon The polygon defining the interior/exterior regions.
     */
    FDMGrid(int nx_, int ny_, Polygon& polygon);


/*==================================== Getters =============== ==========================*/


    float getDx() const { return dx; }
    float getDy() const { return dy; }
    int getNx() const { return nx; }
    int getNy() const { return ny; }
    const std::vector<std::vector<GridType>>& getGridMatrix() const { return gridMatrix; }

        
/*====================================  Methods  =========================================*/
    /**
      * @brief  Converts grid indices to world coordinates.
      * @param i The x index of the grid cell.
      * @param j The y index of the grid cell.
      * @return The corresponding Point2D in world coordinates.     
      */
    Point2D indexToPoint(int i, int j) const;
    
    /**
      * @brief Converts world coordinates to grid indices.
      * @param point The Point2D in world coordinates.
      * @return A pair of indices (i, j) corresponding to the grid cell.
      *         The indices are rounded to the nearest integer.
      */
    std::pair<int, int> pointToIndex(const Point2D& point) const;

    /**
     * @brief Gets the grid type of a specific cell.
     * @param i The x index of the grid cell.
     * @param j The y index of the grid cell.
     * @return The type of the cell (INTERIOR, EXTERIOR, BOUNDARY, UNDEFINED).
     */
    GridType getCellType(int i, int j) const;
    


    /**
     * @brief Checks if the given indices are within the grid bounds.
     * @param i The x index of the grid cell.
     * @param j The y index of the grid cell.
     * @return True if indices are valid, false otherwise.
     */
    bool isValidIndex(int i, int j) const;


    /**
     * @brief Gets the points of a specific type in the grid.
     * @param type The type of cell to get (INTERIOR, EXTERIOR, BOUNDARY).
     * @return A vector of Point2D representing the points of the specified type.
     */
    std::vector<Point2D> getPointsOfType(GridType type) const;
    
    /**
     * @brief Gets the points of type BOUNDARY in the grid.
     *  
     * @return A vector of Point2D representing the boundary points.
     */
    std::vector<Point2D> getBoundaryPoints() const ;
    
    /**
     * @brief Gets the points of type INTERIOR in the grid.
     *  
     * @return A vector of Point2D representing the interior points.
     */
    std::vector<Point2D> getInteriorPoints() const;
    
    /**
     * @brief Gets the points of type EXTERIOR in the grid.
     *  
     * @return A vector of Point2D representing the exterior points.
     */
    std::vector<Point2D> getExteriorPoints() const;
    

    

private:
/*====================================  Helper Methods  =========================================*/
    /**
     * @brief Sets the type of a specific cell in the grid.
     * @param i The x index of the grid cell.
     * @param j The y index of the grid cell.
     * @param type The type to set (INTERIOR, EXTERIOR, BOUNDARY).
     */
    void setCellType(int i, int j, GridType type);


    /**
     * @brief Makes first pass to mark the boundaries of the polygon on the grid.
     * @param polygon The polygon defining the interior/exterior regions.
     * @note This method uses Bresenham's line algorithm to mark the boundary cells.
     * */
    void markBoundaries(const Polygon& polygon);
    
    /**
     * @brief Fills the grid with interior and exterior classifications based on the polygon.
     * @param polygon The polygon defining the interior/exterior regions.
     * @note This method uses a scan-line fill algorithm to classify the cells.
     * */
    void fillInteriorExterior(const Polygon& polygon);
    
};
