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
    
    // Fill the interior and exterior cells
    fillInteriorExterior(polygon);
}






void FDMGrid::markBoundaries(const Polygon& polygon) {
    const std::vector<Point2D>& vertices = polygon.getVertices();
    if (vertices.empty()) return;
    
    // For each edge of the polygon
    for (size_t v = 0; v < vertices.size(); v++) {
        const Point2D& start = vertices[v];
        const Point2D& end = vertices[(v + 1) % vertices.size()];
        
        // Convert to grid indices
        auto [i1, j1] = pointToIndex(start);
        auto [i2, j2] = pointToIndex(end);
        
        // Use Bresenham's line algorithm to mark the line on the grid
        int di = std::abs(i2 - i1);
        int dj = std::abs(j2 - j1);
        int si = i1 < i2 ? 1 : -1; // step in i direction
        int sj = j1 < j2 ? 1 : -1; // step in j direction
        
        int error = di - dj;
        
        int i = i1, j = j1;
        
        // Draw the line on the grid
        while (true) {
            // Mark this cell as boundary if in range
            if (isValidIndex(i, j)) {
                gridMatrix[i][j] = BOUNDARY;
            }
            
            // Exit if we've reached the end point
            if (i == i2 && j == j2) break;
            
            // Calculate next point
            int e2 = 2 * error;
            if (e2 > -dj) {
                error -= dj;
                i += si;
            }
            if (e2 < di) {
                error += di;
                j += sj;
            }
        }
    }
    
}
void FDMGrid::fillInteriorExterior(const Polygon& polygon) {

    
    // Scan-line fill with proper boundary crossing detection
    for (int j = 0; j < ny; j++) {
        bool inside = false;
        
        for (int i = 0; i < nx; i++) {
            if (gridMatrix[i][j] == BOUNDARY) {
                // Check the type of boundary crossing
                int nextI = i + 1;
                while (nextI < nx && gridMatrix[nextI][j] == BOUNDARY) {
                    nextI++;
                }
                // Toggle inside/outside when crossing boundary
                inside = !inside;
                
                i = nextI - 1; // Skip ahead past the boundary section
            } 
            else {
                // Fill cells based on current inside/outside state
                gridMatrix[i][j] = inside ? INTERIOR : EXTERIOR;
            }
        }
        // in case of a corner, we need to backfill the falsely marked interior to exterior
        if (gridMatrix[nx-1][j] == INTERIOR){
            for (int i = nx - 1; gridMatrix[i][j] != BOUNDARY ; i--) {
                gridMatrix[i][j] = EXTERIOR;
            }
        }
    }

}