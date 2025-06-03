#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
        ray(){}
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction){}

        const point3& origin() const {return orig;}
        const vec3& direction() const {return dir;}

        // 't' is distance across the ray from the origin, usually means z-axis value for a surface parallel to the camera.
        point3 at(double t) const{
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif