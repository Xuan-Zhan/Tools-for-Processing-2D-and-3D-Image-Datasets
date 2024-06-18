/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

/**
 * @brief Provides functions for detecting edges in images.
 */

#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H

#include "Image.h"

class EdgeDetector {
public:
    /**
     * @brief Applies the Sobel edge detection filter to the input image.
     * @param img The input image to which the filter will be applied
     * @return The resulting edge-detected image
     */
    static Image applySobel(const Image& image);

    /**
     * @brief Applies the Prewitt edge detection filter to the input image.
     * @param img The input image to which the filter will be applied
     * @return The resulting edge-detected image
     */
    static Image applyPrewitt(const Image& image);

    /**
     * @brief Applies the Scharr edge detection filter to the input image.
     * @param img The input image to which the filter will be applied
     * @return The resulting edge-detected image
     */
    static Image applyScharr(const Image& image);

    /**
     * @brief Applies the Robert's Cross edge detection filter to the input image.
     * @param img The input image to which the filter will be applied
     * @return The resulting edge-detected image
     */
    static Image applyRobertsCross(const Image& image);
};

#endif