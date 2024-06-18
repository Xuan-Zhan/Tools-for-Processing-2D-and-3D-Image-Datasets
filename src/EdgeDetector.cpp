/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "Image.h"
#include "EdgeDetector.h"
#include "ColorFilter.h"
#include <cmath>
# include <iostream>


// Define filter kernels for Sobel, Prewitt, Scharr, and Robert's Cross
const int sobelX[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

const int sobelY[3][3] = {
    {-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};

const int prewittX[3][3] = {
    {-1, 0, 1},
    {-1, 0, 1},
    {-1, 0, 1}
};

const int prewittY[3][3] = {
    {-1, -1, -1},
    { 0,  0,  0},
    { 1,  1,  1}
};

const int scharrX[3][3] = {
    { -3, 0,  3},
    {-10, 0, 10},
    { -3, 0,  3}
};

const int scharrY[3][3] = {
    { -3, -10, -3},
    {  0,   0,  0},
    {  3,  10,  3}
};

const int robertsX[2][2] = {
    { 1,  0},
    { 0, -1}
};

const int robertsY[2][2] = {
    { 0,  1},
    {-1,  0}
};

// Function to apply a filter to an image
Image applyFilter(const Image& img, const int kernel[3][3]) {

    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels();
    unsigned char* inputData = img.getImageData();

    unsigned char* outputData = new unsigned char[width * height];

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            float gx = 0.0f;
            float gy = 0.0f;

            // Apply kernels to the current position
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    gx += inputData[(y + ky) * width + (x + kx)] * kernel[ky + 1][kx + 1];
                    gy += inputData[(y + ky) * width + (x + kx)] * kernel[kx + 1][ky + 1]; // Transpose for Y gradient
                }
            }

            // Calculate the gradient magnitude
            float magnitude = sqrt(gx * gx + gy * gy);
            magnitude = magnitude > 255 ? 255 : magnitude;

            // Set the output pixel
            outputData[y * width + x] = static_cast<unsigned char>(magnitude);
        }
    }
    return Image(outputData, width, height, 1);
}

// Function to apply Robert's Cross filter
Image EdgeDetector::applyRobertsCross(const Image& img) {

    Image grayImg = ColorFilter::toGrayscale(img);

    int width = grayImg.getWidth();
    int height = grayImg.getHeight();
    unsigned char* inputData = grayImg.getImageData();

    unsigned char* outputData = new unsigned char[width * height];

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            float gx = inputData[y * width + x] * robertsX[0][0] +
                       inputData[(y + 1) * width + x + 1] * robertsX[1][1];

            float gy = inputData[y * width + x + 1] * robertsY[0][1] +
                       inputData[(y + 1) * width + x] * robertsY[1][0];

            // Calculate the gradient magnitude
            float magnitude = sqrt(gx * gx + gy * gy);
            magnitude = magnitude > 255 ? 255 : magnitude;

            // Set the output pixel
            outputData[y * width + x] = static_cast<unsigned char>(magnitude);
        }
    }
    return Image(outputData, width, height, 1);
}

Image EdgeDetector::applySobel(const Image& img) {
    Image grayImg = ColorFilter::toGrayscale(img);
    grayImg = applyFilter(grayImg, sobelX);
    return grayImg;
}

Image EdgeDetector::applyPrewitt(const Image& img) {
    Image grayImg = ColorFilter::toGrayscale(img);
    grayImg = applyFilter(grayImg, prewittX);
    return grayImg;
}

Image EdgeDetector::applyScharr(const Image& img) {
    Image grayImg = ColorFilter::toGrayscale(img);
    grayImg = applyFilter(grayImg, scharrX);
    return grayImg;
}