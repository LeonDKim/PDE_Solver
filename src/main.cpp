#include <iostream>
#include "Point2D.h"
#include "Polygon.h"
#include "DomainDiscretization.h"

int main()
{   


    Polygon polygon( { {1,2}, {3,4}, {5,6} } );
    DomainDiscretization domain(polygon, 10, 10);


}

