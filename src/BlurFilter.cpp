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
#include "BlurFilter.h"

#include <iostream>
#include <cmath>
#include <vector>


// Simple insertion sort for sorting neighbor pixels
void insertionSort(std::vector<unsigned char>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        unsigned char key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }

}

// Function to apply median blur on a single channel
void applyMedianBlurSingleChannel(unsigned char* src, unsigned char* dst, int w, int h, int kernelSize) {
    int edge = kernelSize / 2;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            std::vector<unsigned char> neighbors;
            for (int ky = -edge; ky <= edge; ++ky) {
                for (int kx = -edge; kx <= edge; ++kx) {
                    int nx = x + kx;
                    int ny = y + ky;
                    if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                        neighbors.push_back(src[ny * w + nx]);
                    }
                }
            }

            insertionSort(neighbors);
            dst[y * w + x] = neighbors[neighbors.size() / 2];
        }
    }
}

// Wrapper function to apply median blur depending on the number of channels
Image BlurFilter::medianBlur(const Image& image, int kernelSize) {

    int w = image.getWidth();
    int h = image.getHeight();
    int c = image.getChannels();
    unsigned char* src = image.getImageData();

    unsigned char* dst = new unsigned char[w * h * c];

    if (c == 1 || c == 3 || c == 4) {
        unsigned char* channelData = new unsigned char[w * h];
        unsigned char* blurredChannelData = new unsigned char[w * h];

        for (int channel = 0; channel < std::min(c, 3); ++channel) {
            // Extract channel
            for (int i = 0; i < w*h; ++i) {
                channelData[i] = src[i*c + channel];
            }

            // Apply median blur to this channel
            applyMedianBlurSingleChannel(channelData, blurredChannelData, w, h, kernelSize);

            // Merge channel back
            for (int i = 0; i < w*h; ++i) {
                dst[i*c + channel] = blurredChannelData[i];
            }
        }

        if (c == 4) { // Copy alpha channel untouched if present
            for (int i = 0; i < w*h; ++i) {
                dst[i*c + 3] = src[i*c + 3];
            }
        }

        delete[] channelData;
        delete[] blurredChannelData;
    } else {
        std::cerr << "Unsupported channel count: " << c << std::endl;
    }

    return Image(dst, w, h, c);
}

// Custom function to replace std::max
inline int customMax(int a, int b) {
    return (a > b) ? a : b;
}

// Custom function to replace std::min
inline int customMin(int a, int b) {
    return (a < b) ? a : b;
}

// Function to apply box blur on a single channel
void applyBoxBlurSingleChannel(unsigned char* src, unsigned char* dst, int w, int h, int kernelSize) {
    int edge = kernelSize / 2;
    float invKernelSize = 1.0f / (kernelSize * kernelSize);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int sum = 0;
            for (int ky = -edge; ky <= edge; ++ky) {
                for (int kx = -edge; kx <= edge; ++kx) {
                    int nx = customMax(0, customMin(w - 1, x + kx));
                    int ny = customMax(0, customMin(h - 1, y + ky));
                    sum += src[ny * w + nx];
                }
            }
            dst[y * w + x] = static_cast<unsigned char>(std::floor(sum * invKernelSize));
        }
    }
}

// Wrapper function to apply box blur depending on the number of channels
Image BlurFilter::boxBlur(const Image& image, int kernelSize) {

    int w = image.getWidth();
    int h = image.getHeight();
    int c = image.getChannels();
    unsigned char* src = image.getImageData();

    unsigned char* dst = new unsigned char[w * h * c];

    if (c == 1 || c == 3 || c == 4) {
        unsigned char* channelData = new unsigned char[w * h];
        unsigned char* blurredChannelData = new unsigned char[w * h];

        for (int channel = 0; channel < std::min(c, 3); ++channel) {
            // Extract channel
            for (int i = 0; i < w*h; ++i) {
                channelData[i] = src[i*c + channel];
            }

            // Apply box blur to this channel
            applyBoxBlurSingleChannel(channelData, blurredChannelData, w, h, kernelSize);

            // Merge channel back
            for (int i = 0; i < w*h; ++i) {
                dst[i*c + channel] = blurredChannelData[i];
            }
        }

        if (c == 4) { // Copy alpha channel untouched if present
            for (int i = 0; i < w*h; ++i) {
                dst[i*c + 3] = src[i*c + 3];
            }
        }

        delete[] channelData;
        delete[] blurredChannelData;
    } else {
        std::cerr << "Unsupported channel count: " << c << std::endl;
    }

    return Image(dst, w, h, c);
}

std::vector<std::vector<float>> generateGaussianKernel(int kernelSize, float sigma = 2.0f) {
    std::vector<std::vector<float>> kernel(kernelSize, std::vector<float>(kernelSize));
    float sum = 0.0f;
    int edge = kernelSize / 2;

    // Generate Gaussian kernel
    for (int x = -edge; x <= edge; x++) {
        for (int y = -edge; y <= edge; y++) {
            float value = (1.0f / (2.0f * M_PI * sigma * sigma)) * exp(- (x * x + y * y) / (2 * sigma * sigma));
            kernel[x + edge][y + edge] = value;
            sum += value;
        }
    }

    // Normalize the kernel
    for (int x = 0; x < kernelSize; x++) {
        for (int y = 0; y < kernelSize; y++) {
            kernel[x][y] /= sum;
        }
    }

    return kernel;
}


void applyGaussianBlurSingleChannel(const unsigned char* src, unsigned char* dst, int w, int h, const std::vector<std::vector<float>>& kernel) {
    int edge = static_cast<int>(kernel.size()) / 2;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float sum = 0;
            float weightSum = 0;
            for (int ky = -edge; ky <= edge; ++ky) {
                for (int kx = -edge; kx <= edge; ++kx) {
                    int nx = std::max(0, std::min(w - 1, x + kx));
                    int ny = std::max(0, std::min(h - 1, y + ky));
                    float weight = kernel[ky + edge][kx + edge];
                    sum += src[ny * w + nx] * weight;
                    weightSum += weight;
                }
            }
            dst[y * w + x] = static_cast<unsigned char>(round(sum / weightSum));
        }
    }
}


Image BlurFilter::gaussianBlur(const Image& image, int kernelSize, float sigma = 2.0f) {

    int w = image.getWidth();
    int h = image.getHeight();
    int c = image.getChannels();
    unsigned char* src = image.getImageData();

    unsigned char* dst = new unsigned char[w * h * c];

    auto kernel = generateGaussianKernel(kernelSize, sigma);

    if (c < 1 || c > 4) {
            std::cerr << "Unsupported channel count: " << c << std::endl;
        }
        std::vector<unsigned char> channelData(w * h);
        std::vector<unsigned char> blurredChannelData(w * h);
        for (int channel = 0; channel < std::min(c, 3); ++channel) {
            // Extract channel
            for (int i = 0; i < w * h; ++i) {
                channelData[i] = src[i * c + channel];
            }
            // Apply Gaussian blur to this channel
            applyGaussianBlurSingleChannel(channelData.data(), blurredChannelData.data(), w, h, kernel);
            // Merge channel back
            for (int i = 0; i < w * h; ++i) {
                dst[i * c + channel] = blurredChannelData[i];
            }
        }
        if (c == 4) { // Copy alpha channel untouched if present
            for (int i = 0; i < w * h; ++i) {
                dst[i * c + 3] = src[i * c + 3];
            }
        }
    
    return Image(dst, w, h, c);
}

