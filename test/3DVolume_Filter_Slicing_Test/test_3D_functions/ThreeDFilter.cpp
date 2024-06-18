/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "ThreeDFilter.h"
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>

void ThreeDFilter::gaussianBlur(Volume& volume, int kernelSize, float sigma) {
    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();
    int channels = volume.getChannels();

    std::vector<float> kernel(kernelSize * kernelSize * kernelSize);
    int kCenter = kernelSize / 2;
    float sum = 0.0f;

    // Generate Gaussian kernel
    for (int x = 0; x < kernelSize; ++x) {
        for (int y = 0; y < kernelSize; ++y) {
            for (int z = 0; z < kernelSize; ++z) {
                int idx = z * kernelSize * kernelSize + y * kernelSize + x;
                kernel[idx] = gaussian(x - kCenter, y - kCenter, z - kCenter, sigma);
                sum += kernel[idx];
            }
        }
    }

    // Normalize kernel
    for (float& value : kernel) {
        value /= sum;
    }

    std::vector<unsigned char> src = std::vector<unsigned char>(volume.getData(), volume.getData() + width * height * depth * channels);
    std::vector<unsigned char> dest(width * height * depth * channels, 0);

    // Apply Gaussian blur
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < channels; ++c) {
                    float weightedSum = 0.0f;
                    float weight = 0.0f;
                    for (int kz = -kCenter; kz <= kCenter; ++kz) {
                        for (int ky = -kCenter; ky <= kCenter; ++ky) {
                            for (int kx = -kCenter; kx <= kCenter; ++kx) {
                                int nx = x + kx;
                                int ny = y + ky;
                                int nz = z + kz;
                                if (nx >= 0 && nx < width && ny >= 0 && ny < height && nz >= 0 && nz < depth) {
                                    int srcIdx = ((nz * height + ny) * width + nx) * channels + c;
                                    int kernelIdx = (kz + kCenter) * kernelSize * kernelSize + (ky + kCenter) * kernelSize + (kx + kCenter);
                                    weightedSum += src[srcIdx] * kernel[kernelIdx];
                                    weight += kernel[kernelIdx];
                                }
                            }
                        }
                    }
                    int destIdx = ((z * height + y) * width + x) * channels + c;
                    dest[destIdx] = static_cast<unsigned char>(std::min(std::max(int(weightedSum / weight), 0), 255));
                }
            }
        }
    }

    // Copy back to the volume
    volume.setData(dest);
    // std::copy(dest.begin(), dest.end(), volume.getData());
}

float ThreeDFilter::gaussian(float x, float y, float z, float sigma) {
    float coeff = 1.0f / (std::sqrt(2.0f * M_PI) * sigma);
    float exponent = -(x*x + y*y + z*z) / (2.0f * sigma * sigma);
    return coeff * std::exp(exponent);
}


void ThreeDFilter::medianFilter(Volume& volume, int kernelSize) {
    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();
    std::vector<unsigned char> src = std::vector<unsigned char>(volume.getData(), volume.getData() + width * height * depth);
    std::vector<unsigned char> dest(width * height * depth, 0);

    int kHalf = kernelSize / 2;

    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                unsigned char minVal = std::numeric_limits<unsigned char>::max();
                unsigned char maxVal = std::numeric_limits<unsigned char>::min();

                for (int kz = -kHalf; kz <= kHalf; ++kz) {
                    for (int ky = -kHalf; ky <= kHalf; ++ky) {
                        for (int kx = -kHalf; kx <= kHalf; ++kx) {
                            int nz = z + kz;
                            int ny = y + ky;
                            int nx = x + kx;

                            if (nx >= 0 && nx < width && ny >= 0 && ny < height && nz >= 0 && nz < depth) {
                                unsigned char voxelValue = src[nz * width * height + ny * width + nx];
                                minVal = std::min(minVal, voxelValue);
                                maxVal = std::max(maxVal, voxelValue);
                            }
                        }
                    }
                }

                unsigned char medianApprox = (minVal + maxVal) / 2;
                dest[z * width * height + y * width + x] = medianApprox;
            }
        }
    }

    // Copy back to the volume
    volume.setData(dest);
    // std::copy(dest.begin(), dest.end(), volume.getData());
}
