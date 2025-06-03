#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include <vector>
#include <thread>

using namespace std;

class camera{
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samplesPerPixel = 10;

        void render(const hittable& world){
            initialise();

            //Creates thread vector
            vector<thread> threads(image_height);
            //Creates frame buffer to store colour data before writing to file
            vector<vector<colour>> frameBuffer(image_height, vector<colour>(image_width));
            
            cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                //Creates thread using lambda function: = means pass everything into lambda by copy
                // except &world, &frameBuffer which we need by reference
                threads[j] = thread([=, &world, &frameBuffer](){
                    for (int i = 0; i < image_width; i++) {
                        colour pixelColour(0,0,0);
                        for(int sample = 0; sample < samplesPerPixel; sample++){
                            ray r = getRay(i,j);
                            pixelColour += rayColour(r,world);
                        }

                        frameBuffer[j][i] = pixelSampleScales * pixelColour;
                    
                    }
                });
                
            }
            
            //Waits for all threads to finish
            int count = 0;
            for(auto& th : threads){
                clog << "\rScanlines remaing: " << (image_height - count) << ' ' << flush; 
                th.join();
                ++count;
            }

            //Writes framebuffer to file
            for(int j = 0; j < image_height; j++){
                for(int i = 0; i < image_width; i++){
                    write_colour(cout, frameBuffer[j][i]);
                }
            }
            
            clog << "\rDone                                 \n"; 
        }


    private:
        int image_height;   //Rendered image height
        point3 center;  //Camera center
        point3 pixel00Loc; //Location of pixel 0,0
        vec3 pixelDeltaU;   //Offset of pixel to the right
        vec3 pixelDeltaV;   //Offset of pixel below
        double pixelSampleScales;   //Colour scale factor for a sum of pixel samples

        void initialise(){
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixelSampleScales = 1.0/samplesPerPixel;

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
                vec3 direction = randomOnHemisphere(rec.normal);
                return 0.5 * rayColour(ray(rec.p, direction), world);
            }

            vec3 unitDir = unit_vector(r.direction());
            auto a = 0.5 * (unitDir.y() + 1.0);
            return colour(lerp(a, colour(1.0,1.0,1.0), colour(0.5,0.7,1.0)));
        }

        ray getRay(int i, int j) const{
            //Construct camera ray from origin pointing at random sample around pixel (i,j)
            auto offset = sampleSquare();
            auto pixelSample = pixel00Loc + ((i + offset.x()) * pixelDeltaU) + ((j + offset.y()) * pixelDeltaV);
            auto rayOrigin = center;
            auto rayDirection = pixelSample - rayOrigin;
            return ray(rayOrigin, rayDirection);
        }

        vec3 sampleSquare() const{
            //returns the vector to a random point in 0.5 unit square
            return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
        }
};

#endif