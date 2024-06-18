/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "Image.h"

Image::Image() : imageData(nullptr), width(0), height(0), channels(0) {}

Image::Image(unsigned char* imageData, int w, int h, int ch)
    : imageData(imageData), width(w), height(h), channels(ch) {}

Image::~Image() {
    if (imageData != nullptr) {
        std::cout << "Destructor of Image object called." << std::endl;
        delete[] imageData;
    }
}

Image& Image::operator=(const Image& other) {
    if (this != &other) {
        // Free the existing memory
        delete[] imageData;

        // Perform a deep copy of the other object
        width = other.width;
        height = other.height;
        channels = other.channels;
        imageData = new unsigned char[width * height * channels];
        memcpy(imageData, other.imageData, width * height * channels);
    }
    return *this;
}

Image::Image(const Image& other) {
    // Perform a deep copy of the other object
    width = other.width;
    height = other.height;
    channels = other.channels;
    imageData = new unsigned char[width * height * channels];
    memcpy(imageData, other.imageData, width * height * channels);
}

unsigned char* Image::getPixel(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return &(imageData[(y * width + x) * channels]);
    } else {
        std::cout << "Invalid coordinates" << std::endl;
        return nullptr;
    }
}

void Image::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < width && y >= 0 && y < height && channels == 3) {
        int index = (y * width + x) * channels;
        imageData[index] = r;
        imageData[index + 1] = g;
        imageData[index + 2] = b;
    } else {
        std::cout << "Invalid coordinates or channels" << std::endl;
    }
}

void Image::displayImageInfo() {
    std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << std::endl;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

int Image::getChannels() const {
    return channels;
}

unsigned char* Image::getImageData() const {
    return imageData;
}