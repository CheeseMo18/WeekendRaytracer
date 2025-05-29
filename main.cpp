#include <iostream>
#include "header/colour.h"
#include "header/vec3.h"


int main(){
// Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaing: " << (image_height - j) << ' ' << std::flush; 
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            auto pixel_colour = colour(r,g,b);

            write_colour(std::cout, pixel_colour);
        }
    }
    
    std::clog << "\rDone                                 \n"; 
}