/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "Slice.h"
#include <iostream>  // For std::cerr and std::endl
#include "stb_image_write.h"
#include <vector>

bool saveSliceXZ(const Volume& volume, const std::string& outputPath, int yIndex) {
    if (yIndex < 0 || yIndex >= volume.getHeight()) {
        std::cerr << "Y index out of range." << std::endl;
        return false;
    }

    std::vector<unsigned char> slice(volume.getWidth() * volume.getDepth());
    for (int z = 0; z < volume.getDepth(); ++z) {
        for (int x = 0; x < volume.getWidth(); ++x) {
            int index = z * volume.getWidth() * volume.getHeight() + yIndex * volume.getWidth() + x;
            slice[z * volume.getWidth() + x] = volume.getData()[index];
        }
    }

    std::string fullPath = outputPath + "/slice_xz_" + std::to_string(yIndex) + ".png";
    return stbi_write_png(fullPath.c_str(), volume.getWidth(), volume.getDepth(), 1, slice.data(), volume.getWidth());
}

bool saveSliceYZ(const Volume& volume, const std::string& outputPath, int xIndex) {
    if (xIndex < 0 || xIndex >= volume.getWidth()) {
        std::cerr << "X index out of range." << std::endl;
        return false;
    }

    std::vector<unsigned char> slice(volume.getHeight() * volume.getDepth());
    for (int z = 0; z < volume.getDepth(); ++z) {
        for (int y = 0; y < volume.getHeight(); ++y) {
            int index = z * volume.getWidth() * volume.getHeight() + y * volume.getWidth() + xIndex;
            slice[z * volume.getHeight() + y] = volume.getData()[index];
        }
    }

    std::string fullPath = outputPath + "/slice_yz_" + std::to_string(xIndex) + ".png";
    return stbi_write_png(fullPath.c_str(), volume.getHeight(), volume.getDepth(), 1, slice.data(), volume.getHeight());
}
