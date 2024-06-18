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
 * @file Edge_test.cpp
 * @brief Test cases for edge detection algorithms using different methods.
 */
#include <iostream>
#include <cmath>
#include <filesystem>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace fs = std::filesystem;

/**
 * @brief Calculate the Mean Squared Error (MSE) between two images.
 * 
 * @param imgPath1 Path to the first image.
 * @param imgPath2 Path to the second image.
 * @return double The MSE value.
 */
double calculate_mse(const std::string& imgPath1, const std::string& imgPath2) {
    int w1, h1, c1, w2, h2, c2;
    unsigned char* data1 = stbi_load(imgPath1.c_str(), &w1, &h1, &c1, 0);
    unsigned char* data2 = stbi_load(imgPath2.c_str(), &w2, &h2, &c2, 0);

    if (!data1 || !data2 || w1 != w2 || h1 != h2 || c1 != c2) {
        std::cerr << "Error: Images do not match in size or channels.\n";
        stbi_image_free(data1);
        stbi_image_free(data2);
        return -1; // return -1 means error
    }

    double mse = 0.0;
    int size = w1 * h1 * c1;
    for (int i = 0; i < size; ++i) {
        mse += pow((data1[i] - data2[i]), 2);
    }
    mse /= size;

    stbi_image_free(data1);
    stbi_image_free(data2);

    return mse;
}

/**
 * @brief Check if the MSE value indicates similarity between images.
 * 
 * @param mse The Mean Squared Error (MSE) value.
 * @param threshold The threshold for considering images as similar.
 * @return true if the images are similar, false otherwise.
 */
bool is_similar(double mse, double threshold = 100.0) {
    return mse <= threshold;
}

/**
 * @brief Test function for the Prewitt edge detection method.
 */
void test_prewitt() {
    std::string outputPath = "2Dedge_test/edge_output_image/prewitt_gracehopper.png";
    std::string testPath = "2Dedge_test/edge_test_image/prewitt_gracehopper.png";
    double mse = calculate_mse(outputPath, testPath);
    std::cout << "Method 1 - MSE: " << mse << (is_similar(mse) ? " - Similar" : " - Not Similar") << std::endl;
}

/**
 * @brief Test function for the Roberts Cross edge detection method.
 */
void test_robertscross() {
    std::string outputPath = "2Dedge_test/edge_output_image/robertscross_gracehopper.png";
    std::string testPath = "2Dedge_test/edge_test_image/robertscross_gracehopper.png";
    double mse = calculate_mse(outputPath, testPath);
    std::cout << "Method 2 - MSE: " << mse << (is_similar(mse) ? " - Similar" : " - Not Similar") << std::endl;
}

/**
 * @brief Test function for the Scharr edge detection method.
 */
void test_scharr() {
    std::string outputPath = "2Dedge_test/edge_output_image/scharr_gracehopper.png";
    std::string testPath = "2Dedge_test/edge_test_image/scharr_gracehopper.png";
    double mse = calculate_mse(outputPath, testPath);
    std::cout << "Method 3 - MSE: " << mse << (is_similar(mse) ? " - Similar" : " - Not Similar") << std::endl;
}

/**
 * @brief Test function for the Sobel edge detection method.
 */
void test_sobel() {
    std::string outputPath = "2Dedge_test/edge_output_image/sobel_gracehopper.png";
    std::string testPath = "2Dedge_test/edge_test_image/sobel_gracehopper.png";
    double mse = calculate_mse(outputPath, testPath);
    std::cout << "Method 4 - MSE: " << mse << (is_similar(mse) ? " - Similar" : " - Not Similar") << std::endl;
}

/**
 * @brief Main function to run edge detection tests.
 * 
 * @return int 0 on success, non-zero on failure.
 */
int main() {
    // Call each method's test function
    test_prewitt();
    test_robertscross();
    test_sobel();
    test_scharr();

    return 0;
}

// to run the test:
// g++ -o EdgeDetectorTest Edge_test.cpp -std=c++17
// ./EdgeDetectorTest    
