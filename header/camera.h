#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera{
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;

        void render(const hittable& world){
            initialise();

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaing: " << (image_height - j) << ' ' << std::flush; 
                for (int i = 0; i < image_width; i++) {
                    auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
                    auto rayDir = pixelCenter - center;
                    ray r(center, rayDir);

                    colour pixel_colour = rayColour(r, world);

                    write_colour(std::cout, pixel_colour);
                }
            }
            
            std::clog << "\rDone                                 \n"; 
        }

    private:
        int image_height;   //Rendered image height
        point3 center;  //Camera center
        point3 pixel00Loc; //Location of pixel 0,0
        vec3 pixelDeltaU;   //Offset of pixel to the right
        vec3 pixelDeltaV;   //Offset of pixel below

        void initialise(){
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            //Camera settings
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/ image_height);
            auto cameraCenter = point3(0,0,0);
            auto focalLength = 1.0;

            //Calculates horizontal and vertical viewport vectors
            auto viewportU = vec3(viewport_width, 0, 0);
            auto viewportV = vec3(0, -viewport_height, 0);
            //Calculate horizontal and vertical deltas from pixel to pixel
            pixelDeltaU = viewportU / image_width;
            pixelDeltaV = viewportV / image_height;
            //Calculate the location of upper left pixel(this is where the render starts)
            auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLength) - (viewportU/2) - (viewportV/2);
            pixel00Loc = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));


        }

        colour rayColour(const ray& r, const hittable& world) const{
            hit_record rec;
            if(world.hit(r, interval(0, infinity), rec)){
                return 0.5 * (rec.normal + colour(1,1,1));
            }

            vec3 unitDir = unit_vector(r.direction());
            auto a = 0.5 * (unitDir.y() + 1.0);
            return colour(lerp(a, colour(1.0,1.0,1.0), colour(0.5,0.7,1.0)));
        }
};

#endif