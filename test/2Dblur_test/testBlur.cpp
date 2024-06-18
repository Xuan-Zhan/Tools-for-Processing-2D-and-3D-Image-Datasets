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
 * @file main.cpp
 * @brief Test cases for image blurring using different filters.
 */

#include <iostream>
#include <cassert>

#include "Image.h"
#include "BlurFilter.h"

// Simple assertion macro
#define ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "Assertion failed: " << message << std::endl; \
        assert(false); \
    }

/**
 * @brief Test function for median blur (one channel).
 */

void testMedianBlur() {
    // Create a test image (4x4) with single channel
    unsigned char testData[] = {
        10, 20, 30, 40,
        50, 60, 70, 80,
        90, 100, 110, 120,
        130, 140, 150, 160
    };
    Image testImage(testData, 4, 4, 1);

    // Apply median blur with kernel size 3
    BlurFilter blurFilter;
    Image result = blurFilter.medianBlur(testImage, 3);

    // Check if the result is as expected
    unsigned char expectedData[] = {
        50, 50, 60, 70,
        60, 60, 70, 80,
        100, 100, 110, 120,
        130, 130, 140, 150
    };

    ASSERT(result.getWidth() == 4 && result.getHeight() == 4 && result.getChannels() == 1, "Median blur result dimensions are incorrect.");

    const unsigned char* resultData = result.getImageData();
    for (int i = 0; i < 4 * 4; ++i) {
        ASSERT(resultData[i] == expectedData[i], "Median blur result pixel value mismatch.");
    }

    std::cout << "Median blur one-channel test passed." << std::endl;
}

/**
 * @brief Test function for median blur (three channel).
 */
void testMedianBlurThreeChannels() {
    // Create a test image (4x4) with three channels
    unsigned char testData[] = {
        // Channel 1 (R)
        10, 20, 30, 40,
        50, 60, 70, 80,
        90, 100, 110, 120,
        130, 140, 150, 160,
        // Channel 2 (G)
        20, 30, 40, 50,
        60, 70, 80, 90,
        100, 110, 120, 130,
        140, 150, 160, 170,
        // Channel 3 (B)
        30, 40, 50, 60,
        70, 80, 90, 100,
        110, 120, 130, 140,
        150, 160, 170, 180
    };
    Image testImage(testData, 4, 4, 3);

    // Apply median blur with kernel size 3
    BlurFilter blurFilter;
    Image result = blurFilter.medianBlur(testImage, 3);

    const unsigned char* resultData_1 = result.getImageData();

    // Check if the result is as expected
    unsigned char expectedData[] = {
        // Channel 1 (R)
        130, 50, 60, 70,
        50, 60, 70, 80,
        90, 70, 80, 90,
        130, 110, 120, 100,
        // Channel 2 (G)
        80, 60, 70, 80,
        60, 70, 80, 90,
        130, 110, 120, 130,
        110, 120, 130, 110,
        // Channel 3 (B)
        90, 130, 140, 90,
        100, 110, 120, 130,
        140, 120, 130, 140,
        150, 160, 170, 150
    };

    ASSERT(result.getWidth() == 4 && result.getHeight() == 4 && result.getChannels() == 3, "Median blur result dimensions are incorrect for three channels.");

    const unsigned char* resultData = result.getImageData();
    for (int i = 0; i < 4 * 4 * 3; ++i) {
        ASSERT(resultData[i] == expectedData[i], "Median blur result pixel value mismatch for three channels.");
    }

    std::cout << "Median blur three-channel test passed." << std::endl;
}

/**
 * @brief Test function for box blur (one channel).
 */
void testBoxBlur() {
    // Create a test image (4x4) with single channel
    unsigned char testData[] = {
        10, 20, 30, 40,
        50, 60, 70, 80,
        90, 100, 110, 120,
        130, 140, 150, 160
    };
    Image testImage(testData, 4, 4, 1);

    // Apply box blur with kernel size 3
    BlurFilter blurFilter;
    Image result = blurFilter.boxBlur(testImage, 3);

    // Check if the result is as expected
    unsigned char expectedData[] = {
        26, 33, 43, 50,
        53, 60, 70, 76,
        93, 100, 110, 116,
        120, 126, 136, 143
    };

    ASSERT(result.getWidth() == 4 && result.getHeight() == 4 && result.getChannels() == 1, "Box blur result dimensions are incorrect.");

    const unsigned char* resultData = result.getImageData();
    for (int i = 0; i < 4 * 4; ++i) {
        ASSERT(resultData[i] == expectedData[i], "Box blur result pixel value mismatch.");
    }
    std::cout << "Box blur one-channel test passed." << std::endl;
}

/**
 * @brief Test function for box blur (three channel).
 */
void testBoxBlurThreeChannels() {
    // Create a test image (4x4) with three channels
    unsigned char testData[] = {
        // Channel 1 (R)
        10, 20, 30, 40,
        50, 60, 70, 80,
        90, 100, 110, 120,
        130, 140, 150, 160,
        // Channel 2 (G)
        20, 30, 40, 50,
        60, 70, 80, 90,
        100, 110, 120, 130,
        140, 150, 160, 170,
        // Channel 3 (B)
        30, 40, 50, 60,
        70, 80, 90, 100,
        110, 120, 130, 140,
        150, 160, 170, 180
    };
    Image testImage(testData, 4, 4, 3);

    // Apply box blur with kernel size 3
    BlurFilter blurFilter;
    Image result = blurFilter.boxBlur(testImage, 3);

    // Check if the result is as expected
    unsigned char expectedData[] = {
        // Channel 1 (R)
        60, 53, 63, 63,
        56, 66, 76, 70,
        80, 80, 90, 100,
        90, 83, 93, 93,
        // Channel 2 (G)
        86, 80, 90, 83,
        76, 76, 86, 80,
        110, 103, 113, 113,
        106, 100, 110, 103,
        // Channel 3 (B)
        96, 96, 106, 100,
        90, 100, 110, 110,
        120, 113, 123, 133,
        126, 126, 136, 130
    };

    ASSERT(result.getWidth() == 4 && result.getHeight() == 4 && result.getChannels() == 3, "Box blur result dimensions are incorrect for three channels.");

    const unsigned char* resultData = result.getImageData();
    for (int i = 0; i < 4 * 4 * 3; ++i) {
        ASSERT(resultData[i] == expectedData[i], "Box blur result pixel value mismatch for three channels.");
    }
    std::cout << "Box blur three-channel test passed." << std::endl;
}

// Test function for Gaussian blur (one channel)
void testGaussianBlur() {
    // Create a test image (4x4) with single channel
    unsigned char testData[] = {
        10, 20, 30, 40,
        50, 60, 70, 80,
        90, 100, 110, 120,
        130, 140, 150, 160
    };
    Image testImage(testData, 4, 4, 1);

    // Apply Gaussian blur with kernel size 3 and sigma 2.0
    BlurFilter blurFilter;
    Image result = blurFilter.gaussianBlur(testImage, 3, 2.0f);

    // Check if the result is as expected
    unsigned char expectedData[] = {
        26, 33, 43, 50,
        53, 60, 70, 77,
        93, 100, 110, 117,
        120, 127, 137, 144
    };

    ASSERT(result.getWidth() == 4 && result.getHeight() == 4 && result.getChannels() == 1, "Gaussian blur result dimensions are incorrect.");

    const unsigned char* resultData = result.getImageData();
    for (int i = 0; i < 4 * 4; ++i) {
        ASSERT(resultData[i] == expectedData[i], "Gaussian blur result pixel value mismatch.");
    }
    std::cout << "Guassian blur one-channel test passed." << std::endl;
}

// Test function for Gaussian blur (three channel)
void testGaussianBlurThreeChannels() {
    // Create a test image (4x4) with three channels
    unsigned char testData[] = {
        // Channel 1 (R)
        10, 20, 30, 40,
        50, 60, 70, 80,
        90, 100, 110, 120,
        130, 140, 150, 160,
        // Channel 2 (G)
        20, 30, 40, 50,
        60, 70, 80, 90,
        100, 110, 120, 130,
        140, 150, 160, 170,
        // Channel 3 (B)
        30, 40, 50, 60,
        70, 80, 90, 100,
        110, 120, 130, 140,
        150, 160, 170, 180
    };
    Image testImage(testData, 4, 4, 3);

    // Apply Gaussian blur with kernel size 3 and sigma 2.0
    BlurFilter blurFilter;
    Image result = blurFilter.gaussianBlur(testImage, 3, 2.0f);

    // Check if the result is as expected
    unsigned char expectedData[] = {
        // Channel 1 (R)
        58, 53, 63, 63,
        56, 66, 76, 70,
        80, 81, 91, 101,
        92, 84, 94, 95,
        // Channel 2 (G)
        85, 80, 90, 83,
        75, 76, 86, 80,
        110, 104, 114, 115,
        107, 100, 110, 105,
        // Channel 3 (B)
        95, 96, 106, 98,
        89, 99, 109, 110,
        120, 114, 124, 134,
        127, 127, 137, 132
    };

    ASSERT(result.getWidth() == 4 && result.getHeight() == 4 && result.getChannels() == 3, "Gaussian blur result dimensions are incorrect for three channels.");

    const unsigned char* resultData = result.getImageData();
    for (int i = 0; i < 4 * 4 * 3; ++i) {
        ASSERT(resultData[i] == expectedData[i], "Gaussian blur result pixel value mismatch for three channels.");
    }
    std::cout << "Guassian blur three-channel test passed." << std::endl;
}
int main() {
    // Run tests
    testMedianBlur();
    testMedianBlurThreeChannels();
    testBoxBlur();
    testBoxBlurThreeChannels();
    testGaussianBlur();
    testGaussianBlurThreeChannels();

    std::cout << "All tests passed." << std::endl;

    return 0;
}
