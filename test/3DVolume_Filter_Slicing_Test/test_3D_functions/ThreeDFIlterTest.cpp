/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include <iostream>
#include <vector>
#include "ThreeDFilter.h"
#include "test_for_Volume.h"

/**
 * @brief Helper function to compare volume data.
 * 
 * @param originalData The original volume data.
 * @param newData The new volume data.
 * @return true if the volume data has changed, false otherwise.
 */

bool isVolumeDataChanged(const std::vector<unsigned char>& originalData, const std::vector<unsigned char>& newData) {
    if (originalData.size() != newData.size()) {
        return true;
    }

    for (size_t i = 0; i < originalData.size(); ++i) {
        if (originalData[i] != newData[i]) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Test the Gaussian blur filter.
 */

void testGaussianBlur() {
    std::cout << "Testing gaussianBlur..." << std::endl;

    test_for_Volume volume;
    // Assume loadFromFolder is implemented to load a specific test volume
    if (!volume.loadFromFolder("3DVolume_Filter_Slicing_Test/test_images_3D")) {
        std::cerr << "Failed to load volume for testing gaussianBlur." << std::endl;
        return;
    }

    // Save original dimensions and channels before applying the filter
    int originalWidth = volume.getWidth();
    int originalHeight = volume.getHeight();
    int originalDepth = volume.getDepth();
    int originalChannels = volume.getChannels();

    ThreeDFilter filter;
    std::vector<unsigned char> originalData(volume.getData(), volume.getData() + volume.getWidth() * volume.getHeight() * volume.getDepth() * volume.getChannels());

    filter.gaussianBlur(volume, 5, 1.0); // Example parameters

    // Check dimensions and channels
    if (volume.getWidth() != originalWidth || volume.getHeight() != originalHeight || volume.getDepth() != originalDepth || volume.getChannels() != originalChannels) {
        std::cerr << "Volume dimensions or channels changed after gaussianBlur." << std::endl;
    } else {
        std::cout << "Volume dimensions and channels unchanged after gaussianBlur, as expected." << std::endl;
    }

    // Check if data changed
    if (isVolumeDataChanged(originalData, std::vector<unsigned char>(volume.getData(), volume.getData() + volume.getWidth() * volume.getHeight() * volume.getDepth() * volume.getChannels()))) {
        std::cout << "Volume data changed after gaussianBlur, as expected." << std::endl;
    } else {
        std::cerr << "Volume data unchanged after gaussianBlur." << std::endl;
    }
}

/**
 * @brief Test the median filter.
 */
void testMedianFilter() {
    std::cout << "Testing medianFilter..." << std::endl;

    test_for_Volume volume;
    // Assume loadFromFolder is implemented to load a specific test volume
    if (!volume.loadFromFolder("3DVolume_Filter_Slicing_Test/test_images_3D")) {
        std::cerr << "Failed to load volume for testing medianFilter." << std::endl;
        return;
    }

    // Save original dimensions and channels before applying the filter
    int originalWidth = volume.getWidth();
    int originalHeight = volume.getHeight();
    int originalDepth = volume.getDepth();
    int originalChannels = volume.getChannels();

    ThreeDFilter filter;
    std::vector<unsigned char> originalData(volume.getData(), volume.getData() + volume.getWidth() * volume.getHeight() * volume.getDepth() * volume.getChannels());

    filter.medianFilter(volume, 5); // Example parameters

    // Check dimensions and channels
    if (volume.getWidth() != originalWidth || volume.getHeight() != originalHeight || volume.getDepth() != originalDepth || volume.getChannels() != originalChannels) {
        std::cerr << "Volume dimensions or channels changed after medianFilter." << std::endl;
    } else {
        std::cout << "Volume dimensions and channels unchanged after medianFilter, as expected." << std::endl;
    }

    // Check if data changed
    if (isVolumeDataChanged(originalData, std::vector<unsigned char>(volume.getData(), volume.getData() + volume.getWidth() * volume.getHeight() * volume.getDepth() * volume.getChannels()))) {
        std::cout << "Volume data changed after medianFilter, as expected." << std::endl;
    } else {
        std::cerr << "Volume data unchanged after medianFilter." << std::endl;
    }
}

