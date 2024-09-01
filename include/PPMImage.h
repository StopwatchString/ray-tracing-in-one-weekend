#ifndef PPM_IMAGE_H
#define PPM_IMAGE_H

#include "Pixel.h"

#include <cstdint>
#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>

template <size_t widthType, size_t heightType>
class PPMImage
{
public:
    PPMImage() = default;
    ~PPMImage() = default;

    void setPixel(size_t x, size_t y, Pixel p) {
        pixels[x][y] = p;
    }

    void writeToFile(const std::string& filename)
    {
        std::ofstream outfile(filename, std::ios::binary);

        if (outfile.is_open()) {
            outfile << "P3\n";
            outfile << widthType << " " << heightType << '\n';
            outfile << 255 << '\n';

            // Write out the image data row by row to the file.
            // Using a buffer the size of a single row balances file write speed with buffer allocation size in this function.
            // Creating a buffer the entire size of every row and column needed increases the write speed of this function by ~5%.
            // Not really worth the time savings.
            std::array<char, widthType * 12 + 1> buffer; // width * (3 colors * 3 digits max + 1 space each) + 1 for newline
            for (uint32_t y = 0; y < heightType; ++y) {
                char* bufferPtr = buffer.data();
                for (uint32_t x = 0; x < widthType; ++x) {
                    int len = std::snprintf(bufferPtr, 13, "%d %d %d ", static_cast<int>(pixels[x][y].r), static_cast<int>(pixels[x][y].g), static_cast<int>(pixels[x][y].b));
                    bufferPtr += len;
                }
                *bufferPtr = '\n';
                bufferPtr++;

                outfile.write(buffer.data(), bufferPtr - buffer.data());
            }
        }
        else {
            std::cout << "Unable to open the file " << filename << std::endl;
        }
    }

private:
    std::array<std::array<Pixel, heightType>, widthType> pixels;
};

#endif