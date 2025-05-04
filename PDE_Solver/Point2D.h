#pragma once
#include <ostream>
#include <vector>
#include <utility>

/**
 * @brief Represents a 2D point with x and y coordinates.
 */
class Point2D {
public:
    float x; ///< The x-coordinate of the point.
    float y; ///< The y-coordinate of the point.


    const static Point2D zero; ///< A constant static point representing the origin (0, 0).
    const static Point2D left; ///< A constant static point representing the (-1, 0).
    const static Point2D right;
    const static Point2D up;
    const static Point2D down;

    /**
     * @brief Constructs a Point with the given coordinates.
     * @param x_ The x-coordinate.
     * @param y_ The y-coordinate.
     */
    Point2D(float x_ = 0, float y_ = 0);

 //   /**
 //    * @brief Constructs a Point from another Point.
 //    * @param point The point to copy.
	// */
 //   Point2D(const Point2D& point);

 //   /**
 //    * @brief Constructs a Point from a pair of coordinates.
 //    * @param coords The coordinates to copy.
	// */
	//Point2D(const std::pair<float, float>& coords);

 //   /**
 //    * @brief Constructs a Point from a vector of coordinates.
 //    * @param coords The coordinates to copy.
	// */
	//Point2D(const std::vector<float>& coords);


    /**
     * @brief Accesses the x or y coordinate of the point.
     * @param index The index of the coordinate (0 for x, 1 for y).
     */
    float& operator[](size_t index);


    /**
     * @brief Adds two points component-wise.
     * @param other The point to add.
     * @return A new Point that is the sum of this point and the other point.
     */
    Point2D operator+(const Point2D& other) const;

    
    //Point2D operator-(const Point2D& other) const;
    //Point2D operator==(const Point2D& other) const;
    //Point2D operator!=(const Point2D& other) const;

    //Point2D operator*(const float scalar) const;
    //friend float& operator*(const float& scalar, const Point2D& point);

    //Point2D operator/(const float scalar) const;


    /**
     * @brief Outputs the point in the format (x, y).
     * @param os The output stream.
     * @param point The point to output.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Point2D& point);
};
