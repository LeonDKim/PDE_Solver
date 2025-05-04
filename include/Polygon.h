// Polygon.h
#pragma once
#include <vector>
#include <stdexcept>
#include <ostream>
#include "Point2D.h"

/**
 * @brief Represents a simple polygon with arbitrary vertices.
 * 
 * This class stores a sequence of vertices and checks for self-intersection.
 */
class Polygon {
private:
    /// @brief A vector of points representing the vertices of the polygon.
    std::vector<Point2D> vertices;

	/// @brief Checks if the polygon is self-intersecting.
    void validatePolygon() const;
    static bool edgesIntersect(const Point2D& a1, const Point2D& a2,
        const Point2D& b1, const Point2D& b2);

public:
    /**
     * @brief Constructs a polygon from a list of vertices.
     * @param verts A vector of points representing the vertices (in order).
     * @throws std::invalid_argument if the polygon is self-intersecting.
     */
    explicit Polygon(const std::vector<Point2D>& verts);

    /**
     * @brief Outputs the first vertex of the polygon.
     * @param os The output stream.
     * @param poly The polygon to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly);
};