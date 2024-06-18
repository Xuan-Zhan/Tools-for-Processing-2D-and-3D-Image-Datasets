/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/


#ifndef COLORFILTER_H
#define COLORFILTER_H

#include "Image.h"

/**
 * @brief Represents a color space (e.g., HSL or HSV).
 */
struct ColorSpace {
    float h; /** Hue, common to both HSL and HSV */
    float s; /** Saturation, common to both HSL and HSV */
    float l; /** Lightness for HSL, Value for HSV */
};

/**
 * @brief Provides functions for color manipulation and filtering.
 */
class ColorFilter {
public:
    /**
     * @brief Converts an image to grayscale.
     * @param image The input image
     * @return The grayscale version of the input image
     */
    static Image toGrayscale(const Image& image);

    /**
     * @brief Adjusts the brightness of an image.
     * @param image The input image
     * @param brightness The amount by which to adjust the brightness (-255 to 255)
     * @return The image with adjusted brightness
     */
    static Image adjustBrightness(const Image& image, int brightness = 0);

    /**
     * @brief Performs histogram equalization on an image.
     * @param image The input image
     * @param colorSpace The color space of the image ("HSL" or "HSV")
     * @return The image after histogram equalization
     */
    static Image histogramEqualization(const Image& image, const char* colorSpace);

    /**
     * @brief Thresholds an image to create a binary image.
     * @param image The input image
     * @param threshold The threshold value
     * @param colorSpace The color space of the image ("HSL" or "HSV")
     * @return The thresholded binary image
     */
    static Image thresholdImage(const Image& image, unsigned char threshold, const char* colorSpace);

    /**
     * @brief Adds salt-and-pepper noise to an image.
     * @param img The input image
     * @param noisePercent The percentage of pixels to add noise to (0 to 1)
     * @return The image with salt-and-pepper noise added
     */
    static Image addSaltAndPepperNoise(const Image& img, float noisePercent);
};

#endif