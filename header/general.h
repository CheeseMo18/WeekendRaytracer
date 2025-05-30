#ifndef GENERAL_H
#define GENERAL_H

//Stores commonly used imports and constants

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees){
    return degrees * pi / 180.0;
}

inline double randomDouble(){
    //Returns a random real in [0,1)
    return std::rand()/(RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max){
    //Returns a random real in [min,max)
    return min + (max-min) * randomDouble();
}


#include "colour.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

/* 
Lerp: linearly blending between two values, usually in the form
of -> blendedVal = (1 - a) * startVal + a * endVal
where a goes from 0 to 1
*/
inline vec3 lerp(double a, vec3 startVal, vec3 endVal){
    return (1.0 - a) * startVal + a * endVal;
}


#endif