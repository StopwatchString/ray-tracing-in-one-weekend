#include "PPMImage.h"
#include "Pixel.h"
#include "vec3.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <numeric>


const size_t imageWidth = 256;
const size_t imageHeight = 256;
const std::string filename = "image.ppm";

int main()
{
    vec3<double> data(0.0, 1.1, 2.2);
    vec3<double> data2(3.3, 4.4, 5.5);
    
    vec3<double> data3 = cross(data, data2);

    PPMImage<imageWidth, imageHeight>* image = new PPMImage<imageWidth, imageHeight>();

    for (size_t x = 0; x < imageWidth; ++x) {
        for (size_t y = 0; y < imageHeight; ++y) {
            vec3<double> v{ (double)x, (double)y, 0.3 };
            Pixel p{ v.x(), v.y(), v.z() };
            image->setPixel(x, y, p);
        }
    }

    std::cout << "Writing to file " << filename << std::endl;
    image->writeToFile(filename);
    std::cout << "Finished writing to file" << std::endl;

    return 0;
}