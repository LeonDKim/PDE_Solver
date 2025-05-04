#include "Point2D.h"

// Constructor
Point2D::Point2D(float x_, float y_) : x{ x_ }, y{ y_ } {}

Point2D::Point2D(const std::vector<float> &coords)
{
}

float &Point2D::operator[](size_t index)
{
    if (index == 0) return x;
    else if (index == 1) return y;
    throw std::out_of_range("Invalid index");
}

Point2D Point2D::operator+(const Point2D& other) const {
    return Point2D(x + other.x, y + other.y);
}

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}