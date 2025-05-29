#include "header/general.h"
#include <iostream>
#include "header/colour.h"
#include "header/vec3.h"
#include "header/ray.h"
#include "header/hittable.h"
#include "header/hittableList.h"
#include "header/shapes/sphere.h"

/* 
Lerp: linearly blending between two values, usually in the form
of -> blendedVal = (1 - a) * startVal + a * endVal
where a goes from 0 to 1
*/
vec3 lerp(double a, vec3 startVal, vec3 endVal){
    return (1.0 - a) * startVal + a * endVal;
}

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

colour ray_colour(const ray& r, const hittable& world){
    hit_record rec;
    if(world.hit(r, 0, infinity, rec)){
        return 0.5 * (rec.normal + colour(1,1,1));
    }

    vec3 unitDir = unit_vector(r.direction());
    auto a = 0.5 * (unitDir.y() + 1.0);
    return colour(lerp(a, colour(1.0,1.0,1.0), colour(0.5,0.7,1.0)));
}




int main(){
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //World
    hittableList world;
    world.add(make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100));

    //Camera settings
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/ image_height);
    auto cameraCenter = point3(0,0,0);
    auto focalLength = 1.0;

    //Calculates horizontal and vertical viewport vectors
    auto viewportU = vec3(viewport_width, 0, 0);
    auto viewportV = vec3(0, -viewport_height, 0);
    //Calculate horizontal and vertical deltas from pixel to pixel
    auto pixelDeltaU = viewportU / image_width;
    auto pixelDeltaV = viewportV / image_height;

    //Calculate the location of upper left pixel(this is where the render starts)
    auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLength) - (viewportU/2) - (viewportV/2);
    auto pixel00Loc = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaing: " << (image_height - j) << ' ' << std::flush; 
        for (int i = 0; i < image_width; i++) {
            auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDir = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDir);

            colour pixel_colour = ray_colour(r, world);

            write_colour(std::cout, pixel_colour);
        }
    }
    
    std::clog << "\rDone                                 \n"; 
}