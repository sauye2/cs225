/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wreturn-stack-address"
#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
HSLAPixel* myFavoriteColor() {
    HSLAPixel *p = new HSLAPixel(213, 1, 0.46, 1);             
    return p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();                    
    //std::cout << "Reached line " << __LINE__ << std::endl;
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
    //std::cout << "Reached line " << __LINE__ << std::endl;
    // Create out.png
    PNG* output = setupOutput(width, height);                              


    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1;   y < height; y++) {                     
        for (unsigned x = 1;  x < width; x++) {                    
            // Calculate the pixel difference
           // std::cout << "Reached line " << __LINE__ << std::endl;
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
           // std::cout << "Reached line " << __LINE__ << std::endl;
            HSLAPixel& curr = original->getPixel(x, y);
           // std::cout << "Reached line " << __LINE__ << std::endl;
            double diff = std::fabs(curr.h - prev.h);
            //std::cout << "Reached line " << __LINE__ << std::endl;  
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            //std::cout << "Reached line " << __LINE__ << std::endl;
            HSLAPixel &currOutPixel = (*output).getPixel(x, y);                    
            //std::cout << "Reached line " << __LINE__ << std::endl;
            if (diff > 20) {
                currOutPixel = *myPixel;
                //std::cout << "Reached line " << __LINE__ << std::endl;
            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;                     
    delete original;
}
