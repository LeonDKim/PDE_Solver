#include "FDMGrid.h"
#include "Polygon.h"


FDMGrid::FDMGrid(int nx_, int ny_, Polygon& polygon) : nx(nx_), ny(ny_) {
    originX = polygon.getMinX();
    originY = polygon.getMinY();

    dx = (polygon.getMaxX() - originX) / (nx - 1);
    dy = (polygon.getMaxY() - originY) / (ny - 1);
    
    // Initialize all cells to UNDEFINED
    gridMatrix.resize(nx, std::vector<GridType>(ny, UNDEFINED));
    
    // Mark the boundaries of the polygon
    markBoundaries(polygon);
    
    // // Fill the interior and exterior cells
    // fillInteriorExterior(polygon);
}






void FDMGrid::markBoundaries(const Polygon& polygon) {
    // For each edge of the polygon
    const std::vector<Point2D>& vertices = polygon.getVertices();
    for (size_t v = 0; v < vertices.size(); v++) {
        const Point2D& p1 = vertices[v];
        const Point2D& p2 = vertices[(v + 1) % vertices.size()];
        
        // Use Bresenham-like algorithm to sample edge on the grid
        auto [i1, j1] = pointToIndex(p1);
        auto [i2, j2] = pointToIndex(p2);
        
        // Simple line traversal algorithm
        int dx = std::abs(i2 - i1);
        int dy = std::abs(j2 - j1);
        int sx = i1 < i2 ? 1 : -1;
        int sy = j1 < j2 ? 1 : -1;
        int err = dx - dy;
        
        while (true) {
            // Mark this cell as boundary
            if (isValidIndex(i1, j1)) {
                gridMatrix[i1][j1] = BOUNDARY;
            }
            
            if (i1 == i2 && j1 == j2) break;
            
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                i1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                j1 += sy;
            }
        }
    }
}

void FDMGrid::fillInteriorExterior(const Polygon& polygon) {

    //scan each row to determine interior/exterior
    for (int j = 0; j < ny; j++) {
        bool inside = false;
        int lastBoundaryType = -1;  // Track the type of boundary crossing
        
        for (int i = 0; i < nx; i++) {
            if (gridMatrix[i][j] == BOUNDARY) {
                // Check if this is a real boundary crossing
                // Calculate the slope at this point to determine if we're crossing the boundary
                
                Point2D current = indexToPoint(i, j);
                
                // Look at neighboring cells to determine if this is a crossing boundary
                bool hasAboveBoundary = (j+1 < ny) && (gridMatrix[i][j+1] == BOUNDARY);
                bool hasBelowBoundary = (j-1 >= 0) && (gridMatrix[i][j-1] == BOUNDARY);
                
                // Vertical or sloped boundary - toggle inside/outside
                if (hasAboveBoundary != hasBelowBoundary) {
                    inside = !inside;
                }
                // Handle horizontal boundaries - need to detect transitions
                else if (hasAboveBoundary && hasBelowBoundary) {
                    // Look at left and right neighbors to determine crossing behavior
                    int currentSide = -1;
                    
                    // Check left and right to determine which side the polygon is on
                    if (i-1 >= 0 && gridMatrix[i-1][j] != BOUNDARY) {
                        // Test left neighbor with ray casting
                        Point2D leftPoint = indexToPoint(i-1, j);
                        currentSide = polygon.containsPoint(leftPoint) ? 1 : 0;
                    } else if (i+1 < nx && gridMatrix[i+1][j] != BOUNDARY) {
                        // Test right neighbor with ray casting
                        Point2D rightPoint = indexToPoint(i+1, j);
                        currentSide = polygon.containsPoint(rightPoint) ? 1 : 0;
                    }
                    
                    // If we detected a transition in the side
                    if (lastBoundaryType != -1 && lastBoundaryType != currentSide) {
                        inside = !inside;
                    }
                    
                    lastBoundaryType = currentSide;
                }
            } 
            else {
                // For non-boundary cells, mark as interior or exterior
                gridMatrix[i][j] = inside ? INTERIOR : EXTERIOR;
            }
        }
    }
}