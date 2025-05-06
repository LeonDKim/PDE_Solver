#include "DomainDiscretization.h"
#include "Polygon.h"

DomainDiscretization::DomainDiscretization(Polygon& polygon_, int numX_, int numY_): 
numX{ numX_ }, numY{ numY_ }, polygon{ polygon_ } 
{
    if (numX_ <= 3 || numY_ <= 3) {
        throw std::invalid_argument("Number of discretization points must be positive.");
    }
    dx = (polygon_.getMaxX() - polygon_.getMinX()) / float(numX);
    dy = (polygon_.getMaxY() - polygon_.getMinY()) / float(numY);
}
