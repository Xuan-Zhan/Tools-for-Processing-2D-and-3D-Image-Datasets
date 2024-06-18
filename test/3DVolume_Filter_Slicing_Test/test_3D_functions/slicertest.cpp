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
#include <assert.h>  
#include "slice.h"
#include "Volume.h"
#include "stb_image.h" 

void testSaveSliceXZ() {
    Volume vol;
    std::string directoryPath = "3DVolume_Filter_Slicing_Test/test_images_3D";
    bool loaded = vol.loadFromFolder(directoryPath);
    assert(loaded);  // Ensure volume is loaded successfully

    std::string outputPath = "3DVolume_Filter_Slicing_Test/test_images_3D/slice_output"; // Adjust with the correct output path
    int yIndex = 50;  // Use the same Y index as in your main function, adjust if needed

    bool saved = saveSliceXZ(vol, outputPath, yIndex);
    assert(saved);  // Ensure the slice is saved successfully

    std::string savedImagePath = outputPath + "/slice_xz_50.png"; 
    
    int width, height, channels;
    unsigned char *img = stbi_load(savedImagePath.c_str(), &width, &height, &channels, 0);
    assert(img != nullptr); // Check the image was loaded successfully
    assert(width == vol.getWidth()); // Width should be equal to the X dimension of volume
    assert(height == vol.getDepth()); // Height should be equal to the Z dimension of volume
    assert(channels == 1); // Assuming output is grayscale

    std::cout << "testSaveSliceXZ passed." << std::endl;
    stbi_image_free(img); 
}

void testSaveSliceYZ() {
    Volume vol;
    std::string directoryPath = "3DVolume_Filter_Slicing_Test/test_images_3D"; // Use the same directory as in your main function
    bool loaded = vol.loadFromFolder(directoryPath);
    assert(loaded);  // Ensure volume is loaded successfully

    std::string outputPath = "3DVolume_Filter_Slicing_Test/test_images_3D/slice_output"; // Adjust with the correct output path
    int xIndex = 50;  // Use the same X index as in your main function

    bool saved = saveSliceYZ(vol, outputPath, xIndex);
    assert(saved);  // Ensure the slice is saved successfully

    std::string savedImagePath = outputPath + "/slice_yz_50.png"; // Fixed name as per your description
    
    int width, height, channels;
    unsigned char *img = stbi_load(savedImagePath.c_str(), &width, &height, &channels, 0);
    assert(img != nullptr); // Check the image was loaded successfully
    assert(width == vol.getHeight()); // Width should be equal to the Y dimension of volume
    assert(height == vol.getDepth()); // Height should be equal to the Z dimension of volume
    assert(channels == 1); // Assuming output is grayscale

    std::cout << "testSaveSliceYZ passed." << std::endl;
    stbi_image_free(img); 
}
