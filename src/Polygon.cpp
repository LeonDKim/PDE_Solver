// Polygon.cpp
#include "Polygon.h"
#include <algorithm>

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
}

Polygon::Polygon(const std::vector<Point2D>& verts) : vertices(verts) {
    if (vertices.size() < 3) {
        throw std::invalid_argument("Polygon requires at least 3 vertices");
    }
    validatePolygon();
}

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

bool Polygon::edgesIntersect(const Point2D& a1, const Point2D& a2,
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
