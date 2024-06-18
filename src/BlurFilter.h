/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#ifndef BLURFILTER_H
#define BLURFILTER_H

#include "Image.h"

/**
 * @brief Provides functions for image blurring using various techniques.
 */
class BlurFilter {
public:
    /**
     * @brief Applies median blur to an image.
     * @param image The input image
     * @param kernelSize The size of the median blur kernel (odd number)
     * @return The image after median blur
     */
    static Image medianBlur(const Image& image, int kernelSize);

    /**
     * @brief Applies box blur to an image.
     * @param image The input image
     * @param kernelSize The size of the box blur kernel (odd number)
     * @return The image after box blur
     */
    static Image boxBlur(const Image& image, int kernelSize);

    /**
     * @brief Applies Gaussian blur to an image.
     * @param image The input image
     * @param kernelSize The size of the Gaussian blur kernel (odd number)
     * @param sigma The standard deviation of the Gaussian distribution
     * @return The image after Gaussian blur
     */
    static Image gaussianBlur(const Image& image, int kernelSize, float sigma);
};

#endif

