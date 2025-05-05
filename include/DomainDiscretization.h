#pragma once
#include <vector>
#include <stdexcept>
#include <ostream>
#include <algorithm>
#include "Polygon.h"



class DomainDiscretization {
private:
/*====================================  Attributes  =========================================*/
    

    int numX; /// @brief Number of discretization points along the x-axis.
    int numY; /// @brief Number of discretization points along the y-axis.

    int dx; /// @brief Discretization step size along the x-axis.  
    int dy; /// @brief Discretization step size along the y-axis.

public:
/*====================================  Constructors  =========================================*/

    /**
     * @brief Constructs a DomainDiscretization object with the given polygon and number of points.
     * @param polygon_ The polygon representing the domain's boundary.
     * @param numX_ The number of discretization points along the x-axis.
     * @param numY_ The number of discretization points along the y-axis.
     */
    DomainDiscretization(Polygon& polygon_, int numX_, int numY_);


    /*====================================  Getters/Setters  =========================================*/

    /**
     * @brief Gets the number of discretization points along the x-axis.
     * @return The number of discretization points along the x-axis.
     */
    int getNumX() const { return numX; }

    /**
     * @brief Gets the number of discretization points along the y-axis.
     * @return The number of discretization points along the y-axis.
     */
    int getNumY() const { return numY; }

    /**
     * @brief Gets the discretization step size along the x-axis.
     * @return The discretization step size along the x-axis.
     */
    int getDx() const { return dx; }

    /**
     * @brief Gets the discretization step size along the y-axis.
     * @return The discretization step size along the y-axis.
     */
    int getDy() const { return dy; }

};
