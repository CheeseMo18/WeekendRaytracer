#include "header/general.h"
#include <iostream>
#include "header/colour.h"
#include "header/vec3.h"
#include "header/ray.h"
#include "header/hittable.h"
#include "header/hittableList.h"
#include "header/shapes/sphere.h"
#include "header/camera.h"

/*
Checks if ray r intersects a sphere using ray-sphere intersection equations
*/
double hitSphere(const point3& center, double radius, const ray& r){
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    if(discriminant < 0){
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
}


int main(){
    //World
    hittableList world;
    world.add(make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100));

    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.render(world);


}