/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "Projection.h"
#include "Volume.h"
#include <algorithm>
#include <numeric>   
#include <iostream>

// Constructor to initialize width and height of the projection
Projection::Projection(int width, int height) : width(width), height(height) {}

// Function to perform Maximum Intensity Projection 
// Input: volumeData - 3D volume data
// Output: 2D projection result
std::vector<std::vector<unsigned char>> Projection::performMIP(const std::vector<std::vector<std::vector<unsigned char>>>& volumeData) {
    // Initialize result projection with all zeros
    std::vector<std::vector<unsigned char>> result(height, std::vector<unsigned char>(width, 0));
    int startIdx, endIdx;

    // Get the start and end indices based on user input
    getStartEndIndices(volumeData.size(), startIdx, endIdx);

    // Iterate through each pixel of the projection
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char maxIntensity = 0;
            for (int z = startIdx; z < endIdx; ++z) { // Iterate through the volume data along the z-axis
                maxIntensity = std::max(maxIntensity, volumeData[z][y][x]); // Find the maximum intensity at the current pixel position
            }
            result[y][x] = maxIntensity; // Assign the maximum intensity to the corresponding pixel in the result
        }
    }
    return result;
}

// Function to perform Minimum Intensity Projection 
// Input: volumeData - 3D volume data
// Output: 2D projection result
std::vector<std::vector<unsigned char>> Projection::performMinIP(const std::vector<std::vector<std::vector<unsigned char>>>& volumeData) {
    std::vector<std::vector<unsigned char>> result(height, std::vector<unsigned char>(width, 255));
    int startIdx, endIdx;

    getStartEndIndices(volumeData.size(), startIdx, endIdx);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char minIntensity = 255;
            for (int z = startIdx; z < endIdx; ++z) {
                minIntensity = std::min(minIntensity, volumeData[z][y][x]); // Find the minimum intensity at the current pixel position
            }
            result[y][x] = minIntensity; // Assign the minimum intensity to the corresponding pixel in the result
        }
    }

    return result;
}

// Function to perform Average Intensity Projection 
// Input: volumeData - 3D volume data
// Output: 2D projection result
std::vector<std::vector<unsigned char>> Projection::performAIP(const std::vector<std::vector<std::vector<unsigned char>>>& volumeData) {
    std::vector<std::vector<unsigned char>> result(height, std::vector<unsigned char>(width, 0));
    int startIdx, endIdx;

    getStartEndIndices(volumeData.size(), startIdx, endIdx);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sumIntensity = 0;
            for (int z = startIdx; z < endIdx; ++z) {
                sumIntensity += volumeData[z][y][x]; // Accumulate intensity values at the current pixel position
            }
            // Calculate the average intensity and assign to the corresponding pixel in the result
            result[y][x] = static_cast<unsigned char>(sumIntensity / (endIdx - startIdx)); 
        }
    }

    return result;
}

// Function to get the start and end indices based on user input
void Projection::getStartEndIndices(int volumeSize, int& startIdx, int& endIdx) {
    bool operateOverEntireVolume = true;
    std::string userChoice; // Record user input
    int minZ, maxZ; // start and end indices

    // Ask the user whether to project the entire volume or a specific range
    // If true then project entire data volume
    while (true) {
        std::cout << "Project all volume data? (true/false): ";
        std::cin >> userChoice;

        // Check whether the user input is valid. If it is not, re-enter it
        if (userChoice != "true" && userChoice != "false") {
            std::cout << "Invalid input. Please enter 'true' or 'false'." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            break;
        }
    }

    // Check whether the user input is a number with correct range. If it is not, re-enter it
    // If it is a floating number, take an integer part
    if (userChoice == "false") {
        operateOverEntireVolume = false;
        while (true) {
            std::cout << "Enter the minimum number: ";
            if (!(std::cin >> minZ) || minZ < 1 || minZ > volumeSize) { // The input number range is limited to 0 to the number of images
                std::cout << "Invalid input. Please enter a valid integer within the range of 1 and " << volumeSize << "." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        while (true) {
            std::cout << "Enter the maximum number: ";
            if (!(std::cin >> maxZ) || maxZ < 1 || maxZ > volumeSize) {
                std::cout << "Invalid input. Please enter a valid integer within the range of 1 and " << volumeSize  << "." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }
    }
    // Set start and end indices based on user choice
    startIdx = operateOverEntireVolume ? 0 : minZ - 1;
    endIdx = operateOverEntireVolume ? volumeSize : maxZ;
}

std::vector<std::vector<unsigned char>> Projection::performProjection(const Volume& volume, const std::string& projectionType) {
    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();
    const unsigned char* linearData = volume.getData();

    // Convert a one-dimensional array to a three-dimensional vector
    std::vector<std::vector<std::vector<unsigned char>>> volumeData(depth, std::vector<std::vector<unsigned char>>(height, std::vector<unsigned char>(width)));
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = z * height * width + y * width + x;
                volumeData[z][y][x] = linearData[index];
            }
        }
    }

    // Call the corresponding projection function based on the projectionType
    if (projectionType == "MIP") {
        return performMIP(volumeData);
    } else if (projectionType == "MinIP") {
        return performMinIP(volumeData);
    } else if (projectionType == "AIP") {
        return performAIP(volumeData);
    } else {
        std::cerr << "Invalid projection type: " << projectionType << std::endl;
        return {}; // Returns an empty two-dimensional vector
    }
}
