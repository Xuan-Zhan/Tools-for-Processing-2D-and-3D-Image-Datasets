/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "../src/Projection.h"
#include <iostream>
#include <cassert>
#include <sstream>

/**
 * @brief Run a unit test and record the result.
 * 
 * @param testName The name of the test.
 * @param testFunction The function implementing the test.
 * @param testResults Array to record the result of each test.
 * @param i Index to record the result of the current test.
 */
void runTest(const std::string& testName, bool (*testFunction)(), bool testResults[], int i) {
    std::cout << "——————Running test: " << testName << "——————" << std::endl;
    if (testFunction()) {
        testResults[i] = true;
        std::cout << "\033[32m[PASSED]\033[0m" << std::endl;
    } else {
        testResults[i] = false;
        std::cout << "\033[31m[FAILED]\033[0m" << std::endl;
    }
}

/**
 * @brief Test the Maximum Intensity Projection (MIP) method for reading all images.
 * 
 * @return true if the test passes, false otherwise.
 */

bool testPerformMIPEntireVolume() {
    // Create Projection objects and test data
    Projection projection(2, 2);
    std::vector<std::vector<std::vector<unsigned char>>> testData;
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {1, 2}, {3, 4} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {5, 6}, {7, 8} }});

    std::string input = "true\n"; // Simulate user input
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf()); // Redirect cin to read from iss to aviod read from terminal
  
    auto result = projection.performMIP(testData);

    // Verify that the results meet expectations
    return result[0][0] == 5 && result[0][1] == 6 &&
           result[1][0] == 7 && result[1][1] == 8;
}

/**
 * @brief Test the Maximum Intensity Projection (MIP) method for thin slab (2 to 4).
 * 
 * @return true if the test passes, false otherwise.
 */
bool testPerformMIPThinSlab() {
    Projection projection(2, 2);
    std::vector<std::vector<std::vector<unsigned char>>> testData;
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {1, 2}, {9, 4} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {5, 6}, {7, 8} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {10, 0}, {3, 3} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {0, 10}, {5, 9} }});

    std::string input = "false\n2\n4\n"; // Simulate user input (false-2-4)
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf()); 

    auto result = projection.performMIP(testData);

    return result[0][0] == 10 && result[0][1] == 10 &&
           result[1][0] == 7 && result[1][1] == 9;
}

/**
 * @brief Test the Minimum Intensity Projection (MinIP) method for reading all images.
 * 
 * @return true if the test passes, false otherwise.
 */
bool testPerformMinIPEntireVolume() {
    Projection projection(2, 2);
    std::vector<std::vector<std::vector<unsigned char>>> testData;
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {1, 2}, {3, 4} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {5, 6}, {7, 8} }});

    std::string input = "true\n"; 
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf()); 

    auto result = projection.performMinIP(testData);

    return result[0][0] == 1 && result[0][1] == 2 &&
           result[1][0] == 3 && result[1][1] == 4;
}

/**
 * @brief Test the Minimum Intensity Projection (MinIP) method for thin slab (2 to 4).
 * 
 * @return true if the test passes, false otherwise.
 */
bool testPerformMinIPThinSlab() {
    Projection projection(2, 2);
    std::vector<std::vector<std::vector<unsigned char>>> testData;
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {1, 2}, {9, 4} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {5, 6}, {7, 8} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {10, 0}, {3, 3} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {0, 10}, {5, 9} }});

    std::string input = "false\n2\n4\n"; // Simulate user input (false-2-4)
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf()); 

    auto result = projection.performMinIP(testData);

    return result[0][0] == 0 && result[0][1] == 0 &&
           result[1][0] == 3 && result[1][1] == 3;
}

/**
 * @brief Test the Average Intensity Projection (AIP) method for reading all images.
 * 
 * @return true if the test passes, false otherwise.
 */
bool testPerformAIPEntireVolume() {
    Projection projection(2, 2);
    std::vector<std::vector<std::vector<unsigned char>>> testData;
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {1, 2}, {3, 4} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {5, 6}, {7, 8} }});

    std::string input = "true\n"; // Simulate user input
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf()); 

    auto result = projection.performAIP(testData);

    return result[0][0] == 3 && result[0][1] == 4 &&
           result[1][0] == 5 && result[1][1] == 6;
}

/**
 * @brief Test the Average Intensity Projection (AIP) method for thin slab (2 to 4).
 * 
 * @return true if the test passes, false otherwise.
 */
bool testPerformAIPThinSlab() {
    // 创建 Projection 对象和测试数据
    Projection projection(2, 2);
    std::vector<std::vector<std::vector<unsigned char>>> testData;
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {1, 2}, {9, 4} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {5, 6}, {7, 8} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {10, 0}, {3, 3} }});
    testData.push_back(std::vector<std::vector<unsigned char>>{{ {0, 12}, {5, 9} }});

    std::string input = "false\n2\n4\n"; // Simulate user input (false-2-4)
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf()); 

    auto result = projection.performAIP(testData);

    return result[0][0] == 5 && result[0][1] == 6 &&
           result[1][0] == 5 && result[1][1] == 6;
}

/**
 * @brief Test getting start and end indices for projection.
 * 
 * @return true if the test passes, false otherwise.
 */
bool testGetStartEndIndices() {
    Projection projection(2, 2); // Create a Projection object

    // Test when projecting entire data volume
    {
        std::string input = "true\n"; // Simulate user input
        std::istringstream iss(input);
        std::cin.rdbuf(iss.rdbuf()); // Redirect cin to read from iss

        int volumeSize = 5;
        int startIdx, endIdx;
        projection.getStartEndIndices(volumeSize, startIdx, endIdx);

        // Verify start and end indices
        if (startIdx != 0 || endIdx != volumeSize) {
            return false;
        }
    }

    // Test when projecting a specific range
    {
        std::string input = "false\n2\n4\n"; // Simulate user input (false-2-4)
        std::istringstream iss(input);
        std::cin.rdbuf(iss.rdbuf()); // Redirect cin to read from iss

        int volumeSize = 5;
        int startIdx, endIdx;
        projection.getStartEndIndices(volumeSize, startIdx, endIdx);

        // Verify start and end indices
        if (startIdx != 1 || endIdx != 4) {
            return false;
        }
    }

    // Test when user provides invalid input
    {
        // Test enter: 1. Invalid characters 2. The input is out of range
        std::string input = "invalid\nfalse\naaa\n-1\n2\n-5\n10\n5"; 
        std::istringstream iss(input);
        std::cin.rdbuf(iss.rdbuf()); // Redirect cin to read from iss

        int volumeSize = 5;
        int startIdx, endIdx;
        projection.getStartEndIndices(volumeSize, startIdx, endIdx);

        // Verify start and end indices 
        if (startIdx != 1 || endIdx != volumeSize) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Main function to run unit tests for the Projection class.
 * 
 * @return 0 on successful execution.
 */
int main() {
    bool testResults[7]; // Record test result for each test
    // Run unit test
    runTest("PerformMIP_EntireVolume", testPerformMIPEntireVolume, testResults, 0);
    runTest("PerformMIP_ThinSlab", testPerformMIPThinSlab, testResults, 1);
    runTest("PerformMinIP_EntireVolume", testPerformMinIPEntireVolume, testResults, 2);
    runTest("PerformMinIP_ThinSlab", testPerformMinIPThinSlab, testResults, 3);
    runTest("PerformAIP_EntireVolume", testPerformAIPEntireVolume, testResults, 4);
    runTest("PerformAIP_ThinSlab", testPerformAIPThinSlab, testResults, 5);
    runTest("testGetStartEndIndices", testGetStartEndIndices, testResults, 6);

    // Check each test result to see if any tests failed
    bool allPassed = true;
    for (int i = 0; i < 7; ++i) {
        if (!testResults[i]) {
            allPassed = false;
        }
    }

    // Output overall result
    if (allPassed) {
        std::cout << "\033[32mAll tests passed!\033[0m" << std::endl;
    } else {
        std::cout << "\033[31mSome tests failed.\033[0m" << std::endl;
    }
    return 0;
}
