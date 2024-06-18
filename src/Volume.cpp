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
#include <filesystem>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;

Volume::Volume() : width(0), height(0), depth(0), channels(0) {}

Volume::~Volume() {}

const unsigned char* Volume::getData() const {
    return data.data();
}

void Volume::setData(const std::vector<unsigned char>& newData) {
    if (newData.size() == data.size()) {
        std::copy(newData.begin(), newData.end(), data.begin());
    }
}

int Volume::getWidth() const { return width; }
int Volume::getHeight() const { return height; }
int Volume::getDepth() const { return depth; }
int Volume::getChannels() const { return channels; }

