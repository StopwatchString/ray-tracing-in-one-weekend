#include "PPMImage.h"
#include "Pixel.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <numeric>

const size_t width = 4000;
const size_t height = 4000;
const std::string filename = "image.ppm";

int main()
{
    PPMImage<width, height>* image = new PPMImage<width, height>();

    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            image->setPixel(x, y, { 0, 0, 255, 0});
        }
    }

    std::cout << "Writing to file " << filename << std::endl;
    image->writeToFile(filename);
    std::cout << "Finished writing to file" << std::endl;

    return 0;
}