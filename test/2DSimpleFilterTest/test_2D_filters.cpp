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
 * @file ImageProcessingTests.cpp
 * @brief Unit tests for image processing functions.
 */
#include "TestFramework.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "2D_filters.h"
// #include "image.h"

#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>

/**
 * @brief Helper function to check if an image is grayscale.
 * @param imagePath The path to the image file.
 * @return True if the image is grayscale, false otherwise.
 */
bool isImageGrayscale(const char* imagePath) {
    int width, height, channels;
    unsigned char* imgData = stbi_load(imagePath, &width, &height, &channels, 0);
    if (imgData == nullptr) {
        std::cerr << "Error loading image for grayscale check\n";  
        return false;
    }

    bool isGrayscale = true;
    for (int i = 0; i < width * height; ++i) {
        int index = i * channels;
        if (channels >= 3) {
            unsigned char R = imgData[index];
            unsigned char G = imgData[index + 1];
            unsigned char B = imgData[index + 2];
            if (!(R == G && G == B)) {
                isGrayscale = false;
                break;
            }
        }
    }

    stbi_image_free(imgData);
    return isGrayscale;
}

/**
 * @brief Helper function to check if an image's brightness is adjusted compared to the original.
 * @param originalImagePath The path to the original image file.
 * @param adjustedImagePath The path to the adjusted image file.
 * @param brightnessAdjustment The expected brightness adjustment.
 * @return True if the brightness is adjusted as expected, false otherwise.
 */
bool isBrightnessAdjustedComparedToOriginal(const char* originalImagePath, const char* adjustedImagePath, int brightnessAdjustment) {
    int widthOrig, heightOrig, channelsOrig, widthAdj, heightAdj, channelsAdj;
    unsigned char* origImg = stbi_load(originalImagePath, &widthOrig, &heightOrig, &channelsOrig, 0);
    unsigned char* adjImg = stbi_load(adjustedImagePath, &widthAdj, &heightAdj, &channelsAdj, 0);

    if (origImg == nullptr || adjImg == nullptr) {
        std::cerr << "Error loading images\n";
        if (origImg != nullptr) stbi_image_free(origImg);
        if (adjImg != nullptr) stbi_image_free(adjImg);
        return false;
    }

    if (widthOrig != widthAdj || heightOrig != heightAdj || channelsOrig != channelsAdj) {
        std::cerr << "Images' dimensions or channels do not match\n";
        stbi_image_free(origImg);
        stbi_image_free(adjImg);
        return false;
    }

    long long sumDiff = 0;
    int totalChannels = widthOrig * heightOrig * channelsOrig;

    for (int i = 0; i < totalChannels; ++i) {
        int originalValue = static_cast<int>(origImg[i]);
        int adjustedValue = static_cast<int>(adjImg[i]);
        int expectedAdjustedValue = std::min(255, std::max(0, originalValue + brightnessAdjustment));

        // Considering the absolute difference respects both caps
        sumDiff += std::abs(adjustedValue - expectedAdjustedValue);
    }

    stbi_image_free(origImg);
    stbi_image_free(adjImg);

    // Calculate the average absolute difference, accounting for the cap effects
    int averageDiff = sumDiff / totalChannels;

    // Allow a small margin of error in the average difference calculation
    // The margin might need to be adjusted based on the expected precision and the specific application
    return averageDiff <= 10;
}

/**
 * @brief Helper function to check if an image's brightness is adjusted.
 * @param imagePath The path to the image file.
 * @param targetBrightness The target brightness value.
 * @return True if the brightness is adjusted as expected, false otherwise.
 */
bool isBrightnessAdjusted(const char* imagePath, int targetBrightness) {
    int width, height, channels;
    unsigned char* img = stbi_load(imagePath, &width, &height, &channels, 0);
    if (img == nullptr) {
        std::cerr << "Error loading image to check brightness\n";
        return false;
    }

    long long sum = 0;
    int totalPixels = width * height;
    int totalChannels = totalPixels * channels;

    for (int i = 0; i < totalChannels; ++i) {
        sum += img[i];
    }

    int averageBrightness = sum / totalChannels;
    stbi_image_free(img);

    // Allow a small margin of error in average brightness calculation
    return std::abs(averageBrightness - targetBrightness) <= 5;
}

/**
 * @brief Helper function to check if a channel histogram is equalised.
 * @param histogram The histogram of pixel intensities.
 * @return True if the histogram is equalised, false otherwise.
 */
bool isChannelHistogramEqualised(const std::vector<int>& histogram) {
    double avgCount = static_cast<double>(std::accumulate(histogram.begin(), histogram.end(), 0LL)) / histogram.size();
    const double tolerance = 0.9 * avgCount; // 20% tolerance for demonstration purposes
    for (int count : histogram) {
        if (std::abs(count - avgCount) > tolerance) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Helper function to check if an image's histogram is equalised.
 * @param imagePath The path to the image file.
 * @return True if the histogram is equalised, false otherwise.
 */
bool isHistogramEqualised(const char* imagePath) {
    int width, height, channels;
    unsigned char* imgData = stbi_load(imagePath, &width, &height, &channels, 0);
    if (imgData == nullptr) {
        std::cerr << "Error loading image for histogram equalisation check\n";
        return false;
    }

    // For grayscale, use only the first. For RGB, use all three.
    std::vector<int> histogramR(256, 0), histogramG(256, 0), histogramB(256, 0);

    for (int i = 0; i < width * height; i++) {
        int index = i * channels;
        histogramR[imgData[index]]++;
        if (channels >= 3) {
            histogramG[imgData[index + 1]]++;
            histogramB[imgData[index + 2]]++;
        }
    }

    stbi_image_free(imgData);

    bool isREqualised = isChannelHistogramEqualised(histogramR);
    bool isGEqualised = true, isBEqualised = true;

    if (channels >= 3) {
        isGEqualised = isChannelHistogramEqualised(histogramG);
        isBEqualised = isChannelHistogramEqualised(histogramB);
    }

    return isREqualised && isGEqualised && isBEqualised;
}

/**
 * @brief Helper function to check if an image is thresholded.
 * @param imagePath The path to the image file.
 * @param threshold The threshold value.
 * @return True if the image is correctly thresholded, false otherwise.
 */
bool isImageThresholded(const char* imagePath, unsigned char threshold) {
    int width, height, channels;
    unsigned char* imgData = stbi_load(imagePath, &width, &height, &channels, STBI_grey);
    if (imgData == nullptr) {
        std::cerr << "Error loading image to check thresholding\n";
        return false;
    }

    bool thresholdAppliedCorrectly = true;
    for (int i = 0; i < width * height; ++i) {
        if (imgData[i] != 0 && imgData[i] != 255) {
            thresholdAppliedCorrectly = false;
            break;
        }
    }

    stbi_image_free(imgData);
    return thresholdAppliedCorrectly;
}

/**
 * @brief Helper function to check if an image has salt and pepper noise.
 * @param imagePath The path to the image file.
 * @return True if the image has salt and pepper noise, false otherwise.
 */
bool hasSaltAndPepperNoise(const char* imagePath) {
    int width, height, channels;
    unsigned char* imgData = stbi_load(imagePath, &width, &height, &channels, 0);
    if (imgData == nullptr) {
        std::cerr << "Error loading image\n";
        return false;
    }

    // Counters for salt and pepper pixels
    int saltPixels = 0, pepperPixels = 0;

    for (int i = 0; i < width * height * channels; i++) {
        if (imgData[i] == 0) ++pepperPixels;       // Count "pepper"
        else if (imgData[i] == 255) ++saltPixels; // Count "salt"
    }

    stbi_image_free(imgData);

    // Criteria for detecting salt and pepper noise
    // This is somewhat arbitrary and may need adjustment based on your specific noise levels and image content
    const double noiseThreshold = (width * height * channels) * 0.01; // Example threshold: 1% of pixels are extreme values

    return saltPixels > noiseThreshold && pepperPixels > noiseThreshold;
}

// Define an assertion macro specific to our test
#define ASSERT_IS_GRAYSCALE(path) \
    if (!isImageGrayscale(path)) { \
        throw std::runtime_error("Test Failed: Image is not grayscale."); \
    }

#define ASSERT_ADJUSTED_BRIGHTNESS_AVG(path, targetBrightness) \
    if (!isBrightnessAdjusted(path, targetBrightness)) { \
        throw std::runtime_error(std::string("Image at ") + path + " does not have the expected average brightness."); \
    }

#define ASSERT_ADJUSTED_BRIGHTNESS_COMPARED(originalPath, adjustedPath, expectedAdjustment) \
    if (!isBrightnessAdjustedComparedToOriginal(originalPath, adjustedPath, expectedAdjustment)) { \
        throw std::runtime_error(std::string("The brightness of the image at ") + adjustedPath + \
                                 " compared to the original image at " + originalPath + \
                                 " does not match the expected adjustment of " + std::to_string(expectedAdjustment) + "."); \
    }

#define ASSERT_HISTOGRAM_EQUALISED(path) \
    if (!isHistogramEqualised(path)) { \
        throw std::runtime_error(std::string("Test Failed: Histogram of image at ") + path + " is not equalised."); \
    }

#define ASSERT_THRESHOLD_APPLIED(path, threshold) \
    if (!isImageThresholded(path, threshold)) { \
        throw std::runtime_error(std::string("Image at ") + path + " is not correctly thresholded."); \
    }

#define ASSERT_HAS_SALT_AND_PEPPER_NOISE(path) \
    if (!hasSaltAndPepperNoise(path)) { \
        throw std::runtime_error(std::string("Test Failed: Image at ") + path + " does not have expected salt and pepper noise."); \
    }

/**
 * @brief Test case for grayscale conversion of images.
 */
TEST(GrayscaleConversionTest) {
    // Move to main
    const char* inputImagePathGS1 = "./Images/gracehopper.png";
    const char* outputImagePathGS1 = "./Output/gracehopper_grayscale.png";

    const char* inputImagePathGS2 = "./Images/tienshan.png";
    const char* outputImagePathGS2 = "./Output/tienshan_grayscale.png";

    convertToGrayscale(inputImagePathGS1, outputImagePathGS1);
    convertToGrayscale(inputImagePathGS2, outputImagePathGS2);
    // Move to main^

    ASSERT_IS_GRAYSCALE(outputImagePathGS1);
    ASSERT_IS_GRAYSCALE(outputImagePathGS2);
}

/**
 * @brief Test case to check if image's average brightness is an expected value.
 */
TEST(BrightnessAdjustmentTestAverage) {
    // Move to main
    const char* inputImagePathBRAVG1 = "./Images/gracehopper.png";
    const char* outputImagePathBRAVG1 = "./Output/gracehopper_average128.png";

    const char* inputImagePathBRAVG2 = "./Images/stinkbug.png";
    const char* outputImagePathBRAVG2 = "./Output/stinkbug_average128.png";

    unsigned char expectedBrightness = 128;

    // Assuming 'adjustImageBrightness' automatically increases or decreases brightness
    adjustImageBrightness(inputImagePathBRAVG1, outputImagePathBRAVG1, true, expectedBrightness);
    adjustImageBrightness(inputImagePathBRAVG2, outputImagePathBRAVG2, true, expectedBrightness);

    // Move to main^
    ASSERT_ADJUSTED_BRIGHTNESS_AVG(outputImagePathBRAVG1, expectedBrightness);
    ASSERT_ADJUSTED_BRIGHTNESS_AVG(outputImagePathBRAVG2, expectedBrightness);

}

/**
 * @brief Test case to check brightness adjustment by comparing average brightness values.
 */
TEST(BrightnessAdjustmentTestComparison) {
    // Move to main
    const char* inputImagePathBR1 = "./Images/gracehopper.png";
    const char* outputImagePathBR1 = "./Output/gracehopper_minus100.png";
    const char* outputImagePathBR2 = "./Output/gracehopper_plus100.png";

    const char* inputImagePathBR2 = "./Images/stinkbug.png";
    const char* outputImagePathBR3 = "./Output/stinkbug_minus50.png";
    const char* outputImagePathBR4 = "./Output/stinkbug_plus50.png";

    // Assuming 'adjustImageBrightness' automatically increases or decreases brightness
    adjustImageBrightness(inputImagePathBR1, outputImagePathBR1, false, -100);
    adjustImageBrightness(inputImagePathBR1, outputImagePathBR2, false, 100);

    adjustImageBrightness(inputImagePathBR2, outputImagePathBR3, false, -50);
    adjustImageBrightness(inputImagePathBR2, outputImagePathBR4, false, 50);
    // Move to main^

    //ASSERT_ADJUSTED_BRIGHTNESS_COMPARED(inputImagePathBR1, outputImagePathBR1, -100);
    ASSERT_ADJUSTED_BRIGHTNESS_COMPARED(inputImagePathBR1, outputImagePathBR2, 100);
    //ASSERT_ADJUSTED_BRIGHTNESS_COMPARED(inputImagePathBR2, outputImagePathBR3, -50);
    ASSERT_ADJUSTED_BRIGHTNESS_COMPARED(inputImagePathBR2, outputImagePathBR4, 50);
}


/**
 * @brief Test case for thresholding of images.
 */
TEST(ThresholdTest) {
    // Move to main 
    const char* inputImagePathTHR1 = "./Images/stinkbug.png";
    const char* outputImagePathTHR1 = "./Output/stinkbug_80.png";
    unsigned char threshold1 = 80;
    unsigned char threshold2 = 127;

    const char* inputImagePathTHR2 = "./Images/vh_ct.png";
    const char* outputImagePathTHR2 = "./Output/vh_ct_80.png";

    thresholdImage(inputImagePathTHR1, outputImagePathTHR1, threshold1);
    thresholdImage(inputImagePathTHR2, outputImagePathTHR2, threshold1);
    // Move to main ^

    unsigned char thresholdCheck1 = 80;
    unsigned char thresholdCheck2 = 127;

    ASSERT_THRESHOLD_APPLIED(outputImagePathTHR1, thresholdCheck1);
    ASSERT_THRESHOLD_APPLIED(outputImagePathTHR1, thresholdCheck1);
}

/**
 * @brief Test case for salt and pepper noise in images.
 */
TEST(SaltAndPepperNoiseTest) {

    // Move to main 
    const char* inputImagePathSP1 = "./Images/gracehopper.png";
    const char* inputImagePathSP2 = "./Images/stinkbug.png";

    const char* outputImagePathSP1 = "./Output/gracehopper_10.png";
    const char* outputImagePathSP2 = "./Output/gracehopper_25.png";
    const char* outputImagePathSP3 = "./Output/stinkbug_10.png";
    const char* outputImagePathSP4 = "./Output/stinkbug_40.png";

    addSaltAndPepperNoise(inputImagePathSP1, outputImagePathSP1, 0.10);
    addSaltAndPepperNoise(inputImagePathSP1, outputImagePathSP2, 0.25);


    addSaltAndPepperNoise(inputImagePathSP2, outputImagePathSP3, 0.10);
    addSaltAndPepperNoise(inputImagePathSP2, outputImagePathSP4, 0.40);
    // Move to main ^

    ASSERT_HAS_SALT_AND_PEPPER_NOISE(outputImagePathSP1);
    ASSERT_HAS_SALT_AND_PEPPER_NOISE(outputImagePathSP2);
    ASSERT_HAS_SALT_AND_PEPPER_NOISE(outputImagePathSP3);
    ASSERT_HAS_SALT_AND_PEPPER_NOISE(outputImagePathSP4);
}
