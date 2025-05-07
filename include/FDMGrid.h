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
    float originX, originY;  // Bottom-left corner of the grid
    float dx, dy;            // Grid spacing
    int nx, ny;               // Number of grid points in each direction
    std::vector<std::vector<GridType>> gridMatrix;  // Matrix storing cell classifications
    
public:
    // Constructor

    /**
     * @brief Constructs a grid based on the provided polygon.
     * @param nx_ Number of grid points in x-direction.
     * @param ny_ Number of grid points in y-direction.
     * @param polygon The polygon defining the interior/exterior regions.
     */
    FDMGrid(int nx_, int ny_, Polygon& polygon);
        
    
    // Convert grid indices to world coordinates
    Point2D indexToPoint(int i, int j) const {
        return {originX + i * dx, originY + j * dy};
    }
    
    // Convert world coordinates to grid indices
    std::pair<int, int> pointToIndex(const Point2D& point) const {
        int i = std::round((point.x - originX) / dx);
        int j = std::round((point.y - originY) / dy);
        return {i, j};
    }
    
    // Check if indices are within grid bounds
    bool isValidIndex(int i, int j) const {
        return i >= 0 && i < nx && j >= 0 && j < ny;
    }
    
    // Get cell type at specified indices
    GridType getCellType(int i, int j) const {
        if (!isValidIndex(i, j)) return EXTERIOR;
        return gridMatrix[i][j];
    }


    // Accessors
    float getDx() const { return dx; }
    float getDy() const { return dy; }
    int getNx() const { return nx; }
    int getNy() const { return ny; }

private:
    // Mark a cell as a specific type
    void setCellType(int i, int j, GridType type) {
        if (isValidIndex(i, j)) {
            gridMatrix[i][j] = type;
        }
    }


    // Get points of a specific type
    std::vector<Point2D> getPointsOfType(GridType type) const {
        std::vector<Point2D> points;
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                if (gridMatrix[i][j] == type) {
                    points.push_back(indexToPoint(i, j));
                }
            }
        }
        return points;
    }
    
    // Get boundary points
    std::vector<Point2D> getBoundaryPoints() const {
        return getPointsOfType(BOUNDARY);
    }
    
    // Get interior points
    std::vector<Point2D> getInteriorPoints() const {
        return getPointsOfType(INTERIOR);
    }
    
    // Get exterior points
    std::vector<Point2D> getExteriorPoints() const {
        return getPointsOfType(EXTERIOR);
    }
    

    
    // Get the full grid data
    const std::vector<std::vector<GridType>>& getCellTypes() const {
        return gridMatrix;
    }


private:
/*====================================  Helper Methods  =========================================*/

    /**
     * @brief Makes first pass to mark the boundaries of the polygon on the grid.
     * @param polygon The polygon defining the interior/exterior regions.
     * */
    void markBoundaries(const Polygon& polygon);
    
    /**
     * @brief Fills the grid with interior and exterior classifications based on the polygon.
     * @param polygon The polygon defining the interior/exterior regions.
     * */
    void fillInteriorExterior(const Polygon& polygon);
    
};
