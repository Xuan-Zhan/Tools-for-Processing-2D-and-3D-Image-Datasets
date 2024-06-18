/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "VolumeTest.h"
#include "ThreeDFIlterTest.h"
#include "slicertest.h"
#include <iostream>

int main() {
    
    testLoadFromFolder();
    testGetData();
    testDimensionsAndChannels();
    std::cout << "Volume test completed." << std::endl;
    
    testGaussianBlur();
    testMedianFilter();
    std::cout << "3D Filter test completed." << std::endl;
    
    testSaveSliceXZ();
    testSaveSliceYZ();
    std::cout << "3D Slicing test completed." << std::endl;
    
    std::cout << "All tests completed." << std::endl;
    
    return 0;
}
