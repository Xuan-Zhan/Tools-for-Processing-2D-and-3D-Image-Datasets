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
 * @file slice.h
 * @brief Functions for saving slices of volumetric data to image files.
 */

#ifndef SLICE_H
#define SLICE_H

#include "Volume.h"
#include <string>

/**
 * @brief Save a slice of the volume in the XZ plane to a PNG image file.
 * @param volume The volume containing the data.
 * @param outputPath The path to the directory where the image will be saved.
 * @param yIndex The index of the Y-slice to be saved.
 * @return True if saving is successful, false otherwise.
 * @note The Y index must be within the valid range of the volume's height.
 */
bool saveSliceXZ(const Volume& volume, const std::string& outputPath, int yIndex);

/**
 * @brief Save a slice of the volume in the YZ plane to a PNG image file.
 * @param volume The volume containing the data.
 * @param outputPath The path to the directory where the image will be saved.
 * @param xIndex The index of the X-slice to be saved.
 * @return True if saving is successful, false otherwise.
 * @note The X index must be within the valid range of the volume's width.
 */
bool saveSliceYZ(const Volume& volume, const std::string& outputPath, int xIndex);

#endif // SLICE_H
