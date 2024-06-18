/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
**/

#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <filesystem>

// Include STB libraries and your header files
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
 
#include "Image.h"
#include "ColorFilter.h"
#include "BlurFilter.h"
#include "EdgeDetector.h"
#include "Volume.h"
#include "ThreeDFilter.h"
#include "Projection.h"
#include "Slice.h"

namespace fs = std::filesystem;
 
// Add loadImage and saveImage utility functions
Image loadImage(const std::string& filePath) {
    int width, height, channels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data == nullptr) {
        std::cerr << "Failed to load image from " << filePath << std::endl;
        exit(1);
    }
    return Image(data, width, height, channels);
}
 
void saveImage(const std::string& filePath, const Image& image) {
    if (image.getImageData() == nullptr) {
        std::cerr << "No image data to save." << std::endl;
        return;
    }
   if (!stbi_write_png(filePath.c_str(), image.getWidth(), image.getHeight(), image.getChannels(), image.getImageData(), image.getWidth() * image.getChannels())) {
        std::cerr << "Failed to save image: " << filePath << std::endl;
    } else {
        std::cout << "Image saved successfully: " << filePath << std::endl;
    }
}
 
Volume loadFromFolder(Volume& volume, const std::string& folderPath) {
    int width = 0;
    int height, channels, depth = 0;
    std::vector<fs::path> filePaths;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
            filePaths.push_back(entry.path());
        }
    }
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < filePaths.size(); i++) {
            if (filePaths[i - 1].filename() > filePaths[i].filename()) {
                std::swap(filePaths[i - 1], filePaths[i]);
                swapped = true;
            }
        }
    } while (swapped);

    for (const auto& path : filePaths) {
        int w, h, c;
        unsigned char* img = stbi_load(path.string().c_str(), &w, &h, &c, 0);
        if (img == nullptr) {
            std::cerr << "Failed to load image: " << path << std::endl;
            exit(1);
        }
        if (width == 0) { 
            volume.width = w;
            volume.height = h;
            volume.channels = c;
        }
        volume.data.insert(volume.data.end(), img, img + w * h * c);
        stbi_image_free(img);
        depth++;
    }
    volume.depth = depth;
    return volume;
}
 
void saveSingleImage(const std::string& filename, const std::vector<std::vector<unsigned char>>& image) {
    int width = image[0].size();
    int height = image.size();    

    std::vector<unsigned char> flattenedData(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            flattenedData[y * width + x] = image[y][x];
        }
    }
    if (!stbi_write_png(filename.c_str(), width, height, 1, flattenedData.data(), width)) {
        std::cerr << "Failed to save image: " << filename << std::endl;
    } else {
        std::cout << "Image saved successfully: " << filename << std::endl;
    }
}

int main() {
 
    bool applyOtherFile = true;

    while (applyOtherFile){
        std::string inputFilePath, outputFilePath;
        std::string filename = "_nofilter.png"; // Default filename suffix if no filter is applied
        int modelChoice, choice1, choice2, choice3, filterChoice, kernelSize;
        float noisePercent;
        int brightnessChange;
        unsigned char thresholdValue;
        float sigma = 2.0f; // Default sigma for Gaussian blur

        std::cout << "Please enter the path to the input file: ";
        std::getline(std::cin, inputFilePath);

        // Ask user for the output file path
        std::cout << "Please enter the path to the folder for the output image : ";
        std::getline(std::cin, outputFilePath);


        while (true) {
        std::cout << "Please select 1.2D 2.3D" << std::endl;
        std::cin >> modelChoice;

        if (modelChoice == 1 || modelChoice == 2) {
            break;
        } else {
            std::cerr << "Invalid input, please enter 1 or 2." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }   

    if (modelChoice == 1){

        Image inputImage = loadImage(inputFilePath);
        
        bool applyMoreFilters = true;
        while (applyMoreFilters){

            std::cout << "Select a filter to apply to the image:\n";
            std::cout << "1. Grayscale\n";
            std::cout << "2. Adjust Brightness\n";
            std::cout << "3. Histogram Equalization\n";
            std::cout << "4. Thresholding\n";
            std::cout << "5. Salt and Pepper Noise\n";
            std::cout << "6. Image Blur\n";  // Combined option for all blurs
            std::cout << "7. Edge Detection\n";
            std::cout << "Enter your choice (1-7): ";
            std::cin >> filterChoice;
        
            // Validate and clear input stream
            while(std::cin.fail() || filterChoice < 1 || filterChoice > 12) {
                std::cin.clear(); // Clear the error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the incorrect input
                std::cout << "Invalid input, please enter a number between 1 and 7: ";
                std::cin >> filterChoice;
            }
            
            Image outputImage;

            switch (filterChoice) {
            case 1: {
                outputImage = ColorFilter::toGrayscale(inputImage);
                break;
            }
            case 2: {
                std::cout << "Enter brightness change value (-255 to 255): ";
                std::cin >> brightnessChange;
                outputImage = ColorFilter::adjustBrightness(inputImage, brightnessChange);
                break;
            }
            case 3: {
                if (inputImage.getChannels() == 1) {
                    // Grayscale image: Apply histogram equalization directly.
                    outputImage = ColorFilter::histogramEqualization(inputImage, "HSV"); // No color space needed for grayscale
                    std::cout << "Applied histogram equalization to grayscale image." << std::endl;
                } else {
                    // RGB image: Ask the user for the desired color space.
                    std::string colorSpaceChoice;
                    std::cout << "The image is in RGB. Choose the color space for histogram equalization:\n";
                    std::cout << "1. HSL\n";
                    std::cout << "2. HSV\n";
                    std::cout << "Enter your choice (1-2): ";
                    std::cin >> colorSpaceChoice;

                    // Validate and clear input stream
                    while (std::cin.fail() || (colorSpaceChoice != "1" && colorSpaceChoice != "2")) {
                        std::cin.clear(); // Clear the error flags
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the incorrect input
                        std::cout << "Invalid input, please enter a number between 1 and 2: ";
                        std::cin >> colorSpaceChoice;
                    }

                    if (colorSpaceChoice == "1") {
                        outputImage = ColorFilter::histogramEqualization(inputImage, "HSL");
                        std::cout << "Applied histogram equalization using HSL color space." << std::endl;
                    } else if (colorSpaceChoice == "2") {
                        outputImage = ColorFilter::histogramEqualization(inputImage, "HSV");
                        std::cout << "Applied histogram equalization using HSV color space." << std::endl;
                    }
                } 
                break;
            }
            case 4: {
                unsigned char thresholdValue;  
                std::cout << "Enter threshold value (0-255): ";
                int tempThreshold;
                std::cin >> tempThreshold;
    
                // Validate and clear input stream for threshold value
                while (std::cin.fail() || tempThreshold < 0 || tempThreshold > 255) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input, please enter a number between 0 and 255: ";
                    std::cin >> tempThreshold;
                }
    
                thresholdValue = static_cast<unsigned char>(tempThreshold);

                if (inputImage.getChannels() == 1) {
                    // If the image is grayscale, directly apply thresholding without specifying color space.
                    outputImage = ColorFilter::thresholdImage(inputImage, thresholdValue, "HSV");
                    std::cout << "Applied thresholding to grayscale image." << std::endl;
                } else  {
                    // If the image is RGB, ask the user whether to use HSL or HSV for thresholding.
                    std::string colorSpaceChoice;
                    std::cout << "The image is in RGB. Choose the color space for thresholding:\n";
                    std::cout << "1. HSL\n";
                    std::cout << "2. HSV\n";
                    std::cout << "Enter your choice (1-2): ";
                    std::cin >> colorSpaceChoice;

                    // Validate and clear input stream for color space choice
                    while (std::cin.fail() || (colorSpaceChoice != "1" && colorSpaceChoice != "2")) {
                        std::cin.clear(); // Clear the error flags
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the incorrect input
                        std::cout << "Invalid input, please enter a number between 1 and 2: ";
                        std::cin >> colorSpaceChoice;
                    }

                    const char* colorSpace = colorSpaceChoice == "1" ? "HSL" : "HSV";
                    outputImage = ColorFilter::thresholdImage(inputImage, thresholdValue, colorSpace);
                    std::cout << "Applied thresholding using " << colorSpace << " color space." << std::endl;
                } 
                break;
            }
            case 5: {
                std:: cout <<"salt" ; 
                std::cout << "Enter noise percentage (0.0-1.0): ";
                std::cin >> noisePercent;
                outputImage = ColorFilter::addSaltAndPepperNoise(inputImage, noisePercent);
                break;
            }
            case 6: {
                std::cout << "Select type of blur to apply:\n";
                std::cout << "1. Box Blur\n";
                std::cout << "2. Gaussian Blur\n";
                std::cout << "3. Median Blur\n";
                std::cout << "Enter your choice (1-3): ";
                int blurChoice;
                std::cin >> blurChoice;

                // Validate and clear input stream for blur type
                while (std::cin.fail() || blurChoice < 1 || blurChoice > 3) {
                    std::cin.clear(); // Clear the error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input
                    std::cout << "Invalid input, please enter a number between 1 and 3: ";
                    std::cin >> blurChoice;
                }

                std::cout << "Enter kernel size (must be odd number): ";
                std::cin >> kernelSize;  // Add additional validation if needed

                if (blurChoice == 1) {
                    outputImage = BlurFilter::boxBlur(inputImage, kernelSize);
                } else if (blurChoice == 2) {
                    std::cout << "Enter sigma value: ";
                    std::cin >> sigma;  // Add additional validation if needed
                    outputImage = BlurFilter::gaussianBlur(inputImage, kernelSize, sigma);
                } else if (blurChoice == 3) {
                    outputImage = BlurFilter::medianBlur(inputImage, kernelSize);
                }
                break;
            }
            case 7: {
                std::cout << "Select the type of edge detection to apply:\n";
                std::cout << "1. Sobel\n";
                std::cout << "2. Prewitt\n";
                std::cout << "3. Scharr\n";
                std::cout << "4. Roberts Cross\n";
                std::cout << "Enter your choice (1-4): ";
                int edgeChoice;
                std::cin >> edgeChoice;

                // Validate and clear input stream for edge detection choice
                while (std::cin.fail() || edgeChoice < 1 || edgeChoice > 4) {
                    std::cin.clear(); // Clear the error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input
                    std::cout << "Invalid input, please enter a number between 1 and 4: ";
                    std::cin >> edgeChoice;
                }

                // Apply edge detection based on user choice
                if (edgeChoice == 1) {
                    outputImage = EdgeDetector::applySobel(inputImage);
                    std::cout << "Applied Sobel edge detection." << std::endl;
                } else if (edgeChoice == 2) {
                    outputImage = EdgeDetector::applyPrewitt(inputImage);
                    std::cout << "Applied Prewitt edge detection." << std::endl;
                } else if (edgeChoice == 3) {
                    outputImage = EdgeDetector::applyScharr(inputImage);
                    std::cout << "Applied Scharr edge detection." << std::endl;
                } else if (edgeChoice == 4) {
                    outputImage = EdgeDetector::applyRobertsCross(inputImage);
                    std::cout << "Applied Roberts Cross edge detection." << std::endl;
                } else {
                    std::cerr << "Invalid edge detection option." << std::endl;
                    return -1; // This case should be unreachable due to validation.
                }

                break;
            }
            default:
                std::cerr << "Invalid filter option." << std::endl;
                return -1; // Exit program with an error state.
            }

            std::string suffix;
            std::cout << "Please enter the file name you want to save with '.png' (for example: yourFileName.png) " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, suffix);

            saveImage(outputFilePath + "/" + suffix, outputImage);
            
            // Ask if the user wants to apply more filters
            std::cout << "Do you want to apply another filter? (yes/no): ";
            std::string answer;
            std::cin >> answer;
            applyMoreFilters = (answer == "yes");

            // If applying another filter, the modified image becomes the new base for further modifications
            if (applyMoreFilters) {
                inputImage =  outputImage ;
            }
        }
    }
    else {
        Volume volume;
        loadFromFolder(volume, inputFilePath);

        // Select the 3D filter type
        while (true) {
            std::cout << "Please select the 3D filter: 1. Gaussian 2. Median 3. None" << std::endl;

            std::cin >> choice1;

            if (choice1 >= 1 && choice1 <= 3) {
                break;
            } else {
                std::cerr << "Invalid input, please enter a number between 1 and 3." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        
        // If Gaussian or Median filter is selected
        if (choice1 == 1 || choice1 == 2){
            int kernelSize; 
            while (true) {
                std::cout << "Please enter the kernel size (3 or 5): " << std::endl;
                std::cin >> kernelSize;

                if (kernelSize != 3 && kernelSize != 5) {
                    std::cerr << "The kernel size must be 3 or 5, please re-enter." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    break;
                }
            }
            // Apply the selected filter and update the filename suffix accordingly
            if (choice1 == 1){
                float sigma = 2.0f;
                std::stringstream ss;
                ss << "_gaussian_" << kernelSize << ".png";
                filename = ss.str();
                ThreeDFilter::gaussianBlur(volume, kernelSize, sigma);
                std::cout << "Applied 3D Gaussian Blur with kernel size " << kernelSize
                << " and sigma " << sigma << std::endl;
            }
            else {
                std::stringstream ss;
                ss << "_median_" << kernelSize << ".png";
                filename = ss.str();
                ThreeDFilter::medianFilter(volume, kernelSize);
                std::cout << "Applied 3D Median Blur with kernel size " << kernelSize << std::endl;
            }
        }

        // Select the projection method
        while (true) {
            std::cout << "Please select the projection method: 1. Maximum 2. Minimum 3. Average 4. None" << std::endl;
            std::cin >> choice2;

            if (choice2 >= 1 && choice2 <= 4) {
                break;
            } else {
                std::cerr << "Invalid input, please enter a number between 1 and 4." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // If a projection method is selected
        if (choice2 == 1 || choice2 == 2 || choice2 == 3){
            Projection projection(volume.getWidth(), volume.getHeight());
            std::string projectionType;
            if (choice2 == 1){
                projectionType = "MIP";
            }
            else if (choice2 == 2){
                projectionType = "MinIP";
            }
            else {
                projectionType = "AIP";
            }
            // Perform the selected projection and save the resulting image
            std::vector<std::vector<unsigned char>> result = projection.performProjection(volume, projectionType);
            saveSingleImage(outputFilePath + "/" + projectionType + filename, result);
        }

        // Select whether to slice
        while (true) {
            std::cout << "Select whether to slice: 1. Yes 2. No" << std::endl;
            std::cin >> choice3;

            if (choice3 == 1 || choice3 == 2) {
                break;
            } else {
                std::cerr << "Invalid input, please enter 1 or 2." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // If slicing is selected
        if (choice3 == 1){
            int xz, yz;
            // Prompt user to select slice ranges
            std::cout << "Please select the xz slice range:" << std::endl;
            std::cin >> xz;
            std::cout << "Please select yz slice range:" << std::endl;
            std::cin >> yz;

            // Save the X-Z and Y-Z slices
            if (saveSliceXZ(volume, outputFilePath, xz)) {
                std::cout << "X-Z slice saved successfully." << std::endl;
            }

            if (saveSliceYZ(volume, outputFilePath, yz)) { 
                std::cout << "Y-Z slice saved successfully." << std::endl;
            }
        }
    }
        // Ask if the user wants to apply more file
        std::cout << "Do you want to process an other data ? (yes/no): ";
        std::string userAnswer;
        std::cin >> userAnswer;
        applyOtherFile = (userAnswer == "yes");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
    return 0; 
}

// g++ -std=c++17 src/userInterface.cpp src/Volume.cpp src/Projection.cpp src/ThreeDFilter.cpp src/Slice.cpp src/Image.cpp src/ColorFilter.cpp src/BlurFilter.cpp src/EdgeDetector.cpp -o src/userinterface && ./src/userinterface