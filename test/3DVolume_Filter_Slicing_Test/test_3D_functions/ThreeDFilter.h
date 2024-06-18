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
 * @file ThreeDFilter.h
 * @brief Definition of ThreeDFilter class for applying various filters to volumetric data.
 */

#ifndef THREEDFILTER_H
#define THREEDFILTER_H

#include "Volume.h"

/**
 * @brief Class for applying various filters to volumetric data.
 */
class ThreeDFilter {
public:
    /**
     * @brief Apply Gaussian blur filter to the volume.
     * @param volume The volume to apply the filter to.
     * @param kernelSize The size of the Gaussian kernel.
     * @param sigma The standard deviation of the Gaussian distribution.
     */
    static void gaussianBlur(Volume& volume, int kernelSize, float sigma);
    /**
     * @brief Apply median filter to the volume.
     * @param volume The volume to apply the filter to.
     * @param kernelSize The size of the median filter kernel.
     */
    static void medianFilter(Volume& volume, int kernelSize);
private:
    /**
     * @brief Calculate the value of a Gaussian function at a given point.
     * @param x X-coordinate of the point.
     * @param y Y-coordinate of the point.
     * @param z Z-coordinate of the point.
     * @param sigma The standard deviation of the Gaussian distribution.
     * @return The value of the Gaussian function at the given point.
     */
    static float gaussian(float x, float y, float z, float sigma);
};

#endif
