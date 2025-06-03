#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

using colour = vec3;

inline double linearToGamma(double linearComp){
    return linearComp > 0 ? std::sqrt(linearComp) : 0;
}

void write_colour(std::ostream& out, const colour& pixel_colour){
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    //Translate from [0,1] range to [0,255]
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    //write colours
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


#endif