//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
//
//#include "image.h"
//
//int main() {
//    const char* inputImagePath = "./Images/gracehopper.png";
//
//    int width, height, channels;
//    unsigned char* data = stbi_load(inputImagePath, &width, &height, &channels, 0);
//
//    // Create an instance of Images using the constructor
//    Image myImage(data, width, height, channels);
//
//    if (!data) {
//        std::cerr << "Error: Failed to load image inside the" << std::endl;
//        return 1;
//
//    }
//    // Display image metadata
//    myImage.displayImageInfo();
//    return 0;
//}
//
//// g++-13 src/test_image.cpp src/Image.cpp -o test_image && ./test_image
//// -> Width: 512, Height: 600, Channels: 4
