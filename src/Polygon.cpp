// Polygon.cpp
#include "Polygon.h"
#include <algorithm>

/*==================================  Helper Functions  =========================================*/

namespace {
    // Helper function for orientation check
    int orientation(const Point2D& p, const Point2D& q, const Point2D& r) {
        const double val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);
        return (val > 1e-9) ? 1 : (val < -1e-9) ? 2 : 0;
    }

    // Helper function to check if point lies on segment
    bool onSegment(const Point2D& p, const Point2D& q, const Point2D& r) {
        return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y) &&
            orientation(p, q, r) == 0;
    }

    // Helper function to check if two edges intersect
    bool edgesIntersect(const Point2D& a1, const Point2D& a2,
        const Point2D& b1, const Point2D& b2) {
        // Orientation calculations
        const int o1 = orientation(a1, a2, b1);
        const int o2 = orientation(a1, a2, b2);
        const int o3 = orientation(b1, b2, a1);
        const int o4 = orientation(b1, b2, a2);
    
        // General case: segments intersect properly
        if (o1 != o2 && o3 != o4) return true;
    
        // Special cases: collinear points
        if (o1 == 0 && onSegment(a1, b1, a2)) return true;
        if (o2 == 0 && onSegment(a1, b2, a2)) return true;
        if (o3 == 0 && onSegment(b1, a1, b2)) return true;
        if (o4 == 0 && onSegment(b1, a2, b2)) return true;
    
        return false;
    }
}

/*====================================  Constructors  =========================================*/

Polygon::Polygon(const std::vector<Point2D>& verts) : vertices(verts) {
    if (vertices.size() < 3) {
        throw std::invalid_argument("Polygon requires at least 3 vertices");
    }
    validatePolygon();

    // Calculate bounding box (minX, minY, maxX, maxY)
    auto minmaxX = std::minmax_element(vertices.begin(), vertices.end(),
        [](const Point2D& a, const Point2D& b) { return a.x < b.x; });
    minX = minmaxX.first->x;
	maxX = minmaxX.second->x;

    auto minmaxY = std::minmax_element(vertices.begin(), vertices.end(),
        [](const Point2D& a, const Point2D& b) { return a.y < b.y; });
    minY = minmaxY.first->y;
    maxY = minmaxY.second->y;
}

/*=================================  Other Methods   ==============================================*/

bool Polygon::containsPoint(const Point2D& point) const
{
    // Check first if the point is within the bounding box of the polygon
    if (point.x < minX || point.x > maxX || point.y < minY || point.y > maxY) {
        return false;
    }

    // Ray-casting algorithm to check if the point is inside the polygon by shooting a ray to the right, counting the number of intersections
    bool inside = false;
    size_t j = vertices.size() - 1;
    
    for (size_t i = 0; i < vertices.size(); i++) {
        if (((vertices[i].y > point.y) != (vertices[j].y > point.y)) &&
            (point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x)) {
            inside = !inside;
        }
        j = i;
    }
    return inside;
}

bool Polygon::isOnBoundary(const Point2D& point, float epsilon) const
{
    // Check if point is on any edge
    for (size_t i = 0; i < vertices.size(); i++) {
        size_t j = (i + 1) % vertices.size();
        
        const Point2D& v1 = vertices[i];
        const Point2D& v2 = vertices[j];
        
        // Vector from v1 to v2
        Point2D edge = {v2.x - v1.x, v2.y - v1.y};
        // Vector from v1 to point
        Point2D toPoint = {point.x - v1.x, point.y - v1.y};
        
        // Calculate distance from point to line segment
        float edgeLength = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        if (edgeLength < epsilon) continue; // Skip degenerate edges
        
        // Normalize edge vector
        edge.x /= edgeLength;
        edge.y /= edgeLength;
        
        // Calculate projection of toPoint onto edge
        float projection = toPoint.x * edge.x + toPoint.y * edge.y;
        
        // Check if projection is within segment bounds
        if (projection < 0 || projection > edgeLength) continue;
        
        // Calculate distance from point to line
        float distance = std::abs(toPoint.x * edge.y - toPoint.y * edge.x);
        
        if (distance < epsilon) return true;
    }
    return false;
}


/*==================================  Helper Methods  =========================================*/

void Polygon::validatePolygon() const {
    const int n = vertices.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Skip adjacent edges
            if (j == (i + 1) % n || i == (j + 1) % n) continue;

            const Point2D& a1 = vertices[i];
            const Point2D& a2 = vertices[(i + 1) % n];
            const Point2D& b1 = vertices[j];
            const Point2D& b2 = vertices[(j + 1) % n];

            if (edgesIntersect(a1, a2, b1, b2)) {
                throw std::invalid_argument("Self-intersection detected");
            }
        }
    }
}



/*==================================  Getters/Setters  =========================================*/

const std::vector<Point2D>& Polygon::getVertices() const { return vertices; }
float Polygon::getMinX() const { return minX; }
float Polygon::getMinY() const { return minY; }
float Polygon::getMaxX() const { return maxX; }
float Polygon::getMaxY() const { return maxY; }


/*====================================  Operators  =========================================*/

std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
    if (!poly.vertices.empty()) {
        const Point2D& p = poly.vertices.front();
        os << "First vertex: (" << p.x << ", " << p.y << ")";
    }
    else {
        os << "Polygon has no vertices";
    }
    return os;
}