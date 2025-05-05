#include "DomainDiscretization.h"
#include "Polygon.h"

DomainDiscretization::DomainDiscretization(Polygon& polygon_, int numX_, int numY_): 
numX{ numX_ }, numY{ numY_ }
{   
    dx = static_cast<int>(polygon_.getMaxX() - polygon_.getMinX()) / (numX - 1);
    dy = static_cast<int>(polygon_.getMaxY() - polygon_.getMinY()) / (numY - 1);
}