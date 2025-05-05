#include "Point2D.h"

const Point2D Point2D::zero{0, 0};
const Point2D Point2D::left{-1, 0};
const Point2D Point2D::right{1, 0};
const Point2D Point2D::up{0, 1};
const Point2D Point2D::down{0, -1};

Point2D::Point2D(float x_, float y_) : x{ x_ }, y{ y_ } {}

Point2D::Point2D(const Point2D &point): x{point.x}, y{point.y} {}

Point2D::Point2D(const std::pair<float,float>& coords): x{coords.first}, y{coords.second} {}

Point2D::Point2D(const std::vector<float> &coords)
{
    if (coords.size() == 2) 
    {
        x = coords[0];
        y = coords[1];
    } 
    else 
    {
        throw std::invalid_argument("Vector array must be of size 2.");
    }
}

float &Point2D::operator[](size_t index)
{
    if (index == 0) return x;
    else if (index == 1) return y;
    throw std::out_of_range("Invalid index.");
}

Point2D Point2D::operator+(const Point2D& other) const {
    return Point2D(x + other.x, y + other.y);
}

Point2D Point2D::operator-(const Point2D &other) const
{
    return Point2D(x - other.x, y - other.y);
}

bool Point2D::operator==(const Point2D &other) const
{
    if(x == other.x && y == other.y) 
    {
        return true;
    } 
    else
    {
        return false;
    }
}

bool Point2D::operator!=(const Point2D &other) const
{
    if ((x != other.x) || (y != other.y)) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

Point2D Point2D::operator*(const float scalar) const
{
    return Point2D(scalar * x, scalar * y);
}

Point2D operator*(const float &scalar, const Point2D &point)
{
    return Point2D(scalar * point.x, scalar * point.y);
}

Point2D Point2D::operator/(const float scalar) const
{
    return Point2D(x/scalar, y/scalar);
}

std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}