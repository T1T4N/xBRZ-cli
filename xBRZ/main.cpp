//
//  main.cpp
//  xBRZ
//
//  Created by T!T@N on 04.24.16.
//

#include <iostream>
#include <sstream>
#include "xbrz.h"

#define cimg_use_png
#define cimg_display 0
#include "CImg.h"

using namespace cimg_library;

template <uint32_t N> inline
unsigned char getByte(uint32_t val) { return static_cast<unsigned char>((val >> (8 * N)) & 0xff); }

bool validScale(const char* scale) {
    bool output = false;
    if (0 == std::strcmp(scale, "2")) output = true;
    if (0 == std::strcmp(scale, "3")) output = true;
    if (0 == std::strcmp(scale, "4")) output = true;
    if (0 == std::strcmp(scale, "5")) output = true;
    if (0 == std::strcmp(scale, "6")) output = true;
    return output;
}

int main(int argc, const char * argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: xbrz-cli inputFile scaleFactor outputFile" << std::endl;
        std::cerr << "inputFile is assumed to be in the Grayscale, RGB or RGBA color space" << std::endl;
        return EXIT_FAILURE;
    }
    const char* filename = argv[1];
    const char* requestedScale = argv[2];
    const char* outname = argv[3];
    
    if (!validScale(requestedScale)) {
        std::cerr << "Scale must be 2, 3, 4, 5 or 6" << std::endl;
        return EXIT_FAILURE;
    }
    
    char* err;
    int scale = (int)strtol(requestedScale, &err, 10);
    if (!(!*err)) {
        std::cerr << "Scale factor " << err << " could not be parsed" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Loading image from path: " << filename << std::endl;
    CImg<uint32_t> image(filename);
    int width = image.width();
    int height = image.height();
    int depth = image.depth();
    int spectrum = image.spectrum();
    bool isRGBA = spectrum == 4;

    std::cout << "Getting raw pixel data" << std::endl;
    uint32_t* p_raw = new uint32_t[width * height];
    // RGBA to ARGB
    for(uint32_t y = 0; y < (uint32_t)width; y++) {
        for(uint32_t x = 0; x < (uint32_t)height; x++) {
            uint32_t r = image(y, x, 0, 0);
            uint32_t g = image(y, x, 0, 1);
            uint32_t b = image(y, x, 0, 2);
            uint32_t a = 0;
            if (isRGBA) a = image(y, x, 0, 3);
            p_raw[x*width + y] = (a << 24) | (r << 16) | (g << 8) | b;
        }
    }
    
    uint32_t* p_output = new uint32_t[scale * scale * height * width];

    std::cout << "Perform scaling" << std::endl;
    xbrz::scale(
                scale,
                p_raw,
                p_output,
                width,
                height,
                isRGBA? xbrz::ColorFormat::ARGB : xbrz::ColorFormat::RGB
                );
    
    delete[] p_raw;
    
    CImg<uint32_t> output(width * scale, height * scale, depth, spectrum);
    std::cout << "Converting output data to RGBA" << std::endl;
    // ARGB to RGBA
    for(uint32_t y = 0; y < (uint32_t)output.width(); y++) {
        for(uint32_t x = 0; x < (uint32_t)output.height(); x++) {
            uint32_t pixel = p_output[x * width * scale +  y];
            
            switch (spectrum) {
                case 1:
                    output(y, x, 0) = getByte<2>(pixel);    /* R */
                    break;
                case 2:
                    output(y, x, 0) = getByte<2>(pixel);    /* R */
                    output(y, x, 1) = getByte<1>(pixel);    /* G */
                    break;
                case 3:
                    output(y, x, 0) = getByte<2>(pixel);    /* R */
                    output(y, x, 1) = getByte<1>(pixel);    /* G */
                    output(y, x, 2) = getByte<0>(pixel);    /* B */
                    break;
                case 4:
                    output(y, x, 0) = getByte<2>(pixel);    /* R */
                    output(y, x, 1) = getByte<1>(pixel);    /* G */
                    output(y, x, 2) = getByte<0>(pixel);    /* B */
                    output(y, x, 3) = getByte<3>(pixel);    /* A */
                    break;
                default:
                    break;
            }
        }
    }
    delete[] p_output;
    std::cout << "Saving output data" << std::endl;
    output.save(outname);
    
    return EXIT_SUCCESS;
}
