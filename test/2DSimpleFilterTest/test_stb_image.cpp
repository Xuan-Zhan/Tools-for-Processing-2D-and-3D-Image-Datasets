/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <string>
#include <fstream> 

/**
 * @brief Test function for loading and writing an image using stb_image and stb_image_write.
 */
void test_imageLoadingAndWriting() {

    std::string inputImagePath = "Images/gracehopper.png";
    std::string outputImagePath = "Output/test_stb_image_gracehopper.png";

    // Load the image
    int width, height, channels;
    unsigned char* imageData = stbi_load(inputImagePath.c_str(), &width, &height, &channels, 0);

    // Check if image loading was successful
    assert(imageData != nullptr);

    // Write the image to a file
    stbi_write_png(outputImagePath.c_str(), width, height, channels, imageData, width * channels);
    stbi_image_free(imageData);

    // Check if image writing was successful
    assert(std::ifstream(outputImagePath).good());

    std::cout << "Test passed: Image successfully loaded and written to " << outputImagePath << std::endl;
}

/**
 * @brief Main function to execute the image loading and writing test.
 * @return 0 on successful execution.
 */
int main() {
    test_imageLoadingAndWriting();
    return 0;
}

// g++-13 src/test_stb_image.cpp -o test_stb_image && ./test_stb_image
// -> Test passed: Image successfully loaded and written to Output/test_stb_image_gracehopper.png
