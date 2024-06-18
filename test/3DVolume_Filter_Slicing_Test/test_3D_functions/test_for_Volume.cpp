/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "test_Volume.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <filesystem>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;

test_Volume::test_Volume() : width(0), height(0), depth(0), channels(0) {}

test_Volume::~test_Volume() {}

bool test_Volume::loadFromFolder(const std::string& folderPath) {
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
            return false;
        }
        if (width == 0) { 
            width = w;
            height = h;
            channels = c;
        }
        data.insert(data.end(), img, img + w * h * c);
        stbi_image_free(img);
        depth++;
    }
    return true;
}


bool test_Volume::saveToFolder(const std::string& folderPath) const {
    fs::path dir(folderPath);
    if (!fs::exists(dir)) {
        try {
            if (!fs::create_directories(dir)) {
                std::cerr << "Failed to create directories: " << folderPath << std::endl;
                return false;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Exception caught: " << e.what() << '\n';
            std::cerr << "Current path is " << fs::current_path() << '\n';
            return false;
        }
    }

    for (int z = 0; z < depth; ++z) {
        std::string filePath = folderPath + "/slice_" + std::to_string(z) + ".png";
        stbi_write_png(filePath.c_str(), width, height, channels, data.data() + z * width * height * channels, width * channels);
    }
    return true;
}

const unsigned char* test_Volume::getData() const {
    return data.data();
}

void test_Volume::setData(const std::vector<unsigned char>& newData) {
    if (newData.size() == data.size()) {
        std::copy(newData.begin(), newData.end(), data.begin());
    }
}

int test_Volume::getWidth() const { return width; }
int test_Volume::getHeight() const { return height; }
int test_Volume::getDepth() const { return depth; }
int test_Volume::getChannels() const { return channels; }


void test_Volume::saveImage(const std::string& filename, const std::vector<std::vector<unsigned char>>& image) {
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

