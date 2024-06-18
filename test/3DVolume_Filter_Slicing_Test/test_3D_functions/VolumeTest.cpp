/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "Volume.h"
#include <iostream>

void testLoadFromFolder() {
    Volume vol;
    bool result = vol.loadFromFolder("3DVolume_Filter_Slicing_Test/test_images_3D");
    if (result) {
        std::cout << "loadFromFolder passed." << std::endl;
    } else {
        std::cout << "loadFromFolder failed." << std::endl;
    }
}

void testGetData() {
    Volume vol;
    vol.loadFromFolder("3DVolume_Filter_Slicing_Test/test_images_3D");
    const unsigned char* data = vol.getData();
    if (data != nullptr) {
        std::cout << "getData passed." << std::endl;
    } else {
        std::cout << "getData failed." << std::endl;
    }
}


void testDimensionsAndChannels() {
    Volume vol;
    vol.loadFromFolder("3DVolume_Filter_Slicing_Test/test_images_3D");
    int expectedWidth = 843; 
    int expectedHeight = 275; 
    int expectedDepth = 3; 
    int expectedChannels = 1; 

    if (vol.getWidth() == expectedWidth && vol.getHeight() == expectedHeight &&
        vol.getDepth() == expectedDepth && vol.getChannels() == expectedChannels) {
        std::cout << "Dimension and channel tests passed." << std::endl;
    } else {
        std::cout << "Dimension and channel tests failed. Received dimensions: "
                  << vol.getWidth() << "x" << vol.getHeight() << "x" << vol.getDepth()
                  << ", Channels: " << vol.getChannels() << std::endl;
    }
}

