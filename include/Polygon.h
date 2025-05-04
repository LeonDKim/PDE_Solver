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
public:
    /// @brief A vector of points representing the vertices of the polygon.
    std::vector<Point2D> vertices;
    
	float minX; ///< @brief Minimum x-coordinate of the polygon.
	float minY; ///< @brief Minimum y-coordinate of the polygon.
	float maxX; ///< @brief Maximum x-coordinate of the polygon.
	float maxY; ///< @brief Maximum y-coordinate of the polygon.
    
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

private:
	/** @brief Checks if the polygon is self-intersecting.
     *  Temporarily implemented using brute force O(n^2) method.
     *  Improving this to O(n log n) using a sweep line algorithm is possible.
     */
    void validatePolygon() const;

    /** @brief Checks if two edges intersect.
     *  Temporary helper method for validatePolygon.
     */
    static bool edgesIntersect(const Point2D& a1, const Point2D& a2,
        const Point2D& b1, const Point2D& b2);
};