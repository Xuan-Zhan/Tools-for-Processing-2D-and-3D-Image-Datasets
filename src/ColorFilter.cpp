/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#include "ColorFilter.h"

#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <random>

// Convert RGB to a unified ColorSpace (either HSL or HSV)
ColorSpace RGBtoColorSpace(unsigned char r, unsigned char g, unsigned char b, const char* colorSpace) {
    float R = r / 255.0f;
    float G = g / 255.0f;
    float B = b / 255.0f;
    float max = std::max({R, G, B});
    float min = std::min({R, G, B});
    float delta = max - min;

    ColorSpace cs;
    if (strcmp(colorSpace, "HSV") == 0) {
        cs.l = max; // 'l' is used as 'v' for HSV
        cs.s = max == 0 ? 0 : delta / max;
    } else { // Default to HSL if not HSV
        cs.l = (max + min) / 2;
        cs.s = (max == min) ? 0 : (cs.l > 0.5 ? delta / (2 - max - min) : delta / (max + min));
    }

    if (delta == 0) { // Achromatic
        cs.h = 0;
    } else {
        if (R == max) cs.h = (G - B) / delta + (G < B ? 6 : 0);
        else if (G == max) cs.h = (B - R) / delta + 2;
        else cs.h = (R - G) / delta + 4;
        cs.h /= 6;
    }

    return cs;
}

// Convert a unified ColorSpace to RGB
void ColorSpaceToRGB(const ColorSpace& cs, unsigned char &r, unsigned char &g, unsigned char &b, const char* colorSpace) {
    float h = cs.h, s = cs.s, l = cs.l;
    float rOut, gOut, bOut;

    if (s == 0) { // Achromatic
        rOut = gOut = bOut = l;
    } else {
        auto hue2rgb = [](float p, float q, float t) -> float { // Add -> float to specify return type explicitly
            if (t < 0) t += 1;
            if (t > 1) t -= 1;
            if (t < 1.0f / 6) return p + (q - p) * 6 * t;
            if (t < 0.5f) return q; // Changed from 1.0/2 to 0.5f for consistency
            if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6; // Make sure all constants are float
            return p;
        };

        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;

        if (strcmp(colorSpace, "HSV") == 0) {  // Conversion from HSV to RGB
            int i = int(h * 6);
            float f = h * 6 - i;
            float p = l * (1 - s);
            float q = l * (1 - f * s);
            float t = l * (1 - (1 - f) * s);

            switch (i % 6) {
                case 0: rOut = l, gOut = t, bOut = p; break;
                case 1: rOut = q, gOut = l, bOut = p; break;
                case 2: rOut = p, gOut = l, bOut = t; break;
                case 3: rOut = p, gOut = q, bOut = l; break;
                case 4: rOut = t, gOut = p, bOut = l; break;
                case 5: rOut = l, gOut = p, bOut = q; break;
            }
        } else {  // Default conversion is from HSL to RGB
            rOut = hue2rgb(p, q, h + 1.0 / 3);
            gOut = hue2rgb(p, q, h);
            bOut = hue2rgb(p, q, h - 1.0 / 3);
        }
    }

    r = static_cast<unsigned char>(rOut * 255);
    g = static_cast<unsigned char>(gOut * 255);
    b = static_cast<unsigned char>(bOut * 255);
}

Image ColorFilter::toGrayscale(const Image& image) {

    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *img = image.getImageData();

    unsigned char* grayData = new unsigned char[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char* pixel = image.getPixel(x, y);
            int grayValue = 0.2126 * pixel[0] + 0.7152 * pixel[1] + 0.0722 * pixel[2];
            grayData[y * width + x] = static_cast<unsigned char>(grayValue);
        }
    }

    return Image(grayData, width, height, 1);
}

Image ColorFilter::adjustBrightness(const Image& image, int brightness) {

    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *img = image.getImageData();

    unsigned char* adjusted_img = new unsigned char[width * height * channels];

    int totalPixels = width * height;
    int totalChannels = totalPixels * channels;

    // If brightness value is not provided, set it to the average
    if (brightness == 0) {
        // Calculate total sum of pixel values for all channels
        int sum = 0;
        for (int i = 0; i < totalChannels; ++i) {
            sum += img[i];
        }

        // Calculate average pixel value for all channels
        int average = sum / totalChannels;
            brightness = 128 - average;
        }

    // Iterate over each pixel and adjust brightness
    for (int i = 0; i < totalChannels; ++i) {
        int val = img[i];
        int newValue = img[i] + brightness;

        // Ensure the new value is within the valid range [0, 255]
        if (newValue < 0) {
            newValue = 0;
        } else if (newValue > 255) {
            newValue = 255;
        }
        adjusted_img[i] = static_cast<unsigned char>(newValue);
    }

    Image adjusted(adjusted_img, width, height, channels);

    return adjusted;
}

Image ColorFilter::histogramEqualization(const Image& image, const char* colorSpace) {

    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char *img = image.getImageData();

    // Create a copy of the original image data
    unsigned char* newData = new unsigned char[width * height * channels];
    std::memcpy(newData, img, width * height * channels);

    std::vector<float> lvChannel(width * height); // For lightness (HSL) or value (HSV) or grayscale
    std::vector<float> hChannel(width * height);  // Only used for color images
    std::vector<float> sChannel(width * height);  // Only used for color images

    // Process each pixel, convert to grayscale intensity, HSL, or HSV and collect values
    for (int i = 0; i < width * height; ++i) {
        int index = i * channels;
        if (channels >= 3) { // Color image
            ColorSpace cs = RGBtoColorSpace(img[index], img[index + 1], img[index + 2], colorSpace);
            hChannel[i] = cs.h;
            sChannel[i] = cs.s;
            lvChannel[i] = cs.l;
        } else { // Grayscale image
            lvChannel[i] = newData[i] / 255.0f;  
        }
    }

    // Histogram equalization on lightness, value, or grayscale intensity
    const int numBins = 256;
    std::vector<int> histogram(numBins, 0), cdf(numBins, 0);

    // Compute histogram
    for (auto lv : lvChannel) {
        histogram[static_cast<int>(lv * 255)]++;
    }

    // Compute cumulative distribution function (CDF)
    cdf[0] = histogram[0];
    for (int i = 1; i < numBins; ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    // Normalize the CDF
    float cdfMin = cdf.front();
    float scale = 255.0f / (width * height - cdfMin);
    for (int i = 0; i < numBins; ++i) {
        cdf[i] = static_cast<int>((cdf[i] - cdfMin) * scale);
    }

    // Apply the equalized histogram to the image
    for (int i = 0; i < width * height; ++i) {
        int index = i * channels;
        lvChannel[i] = cdf[static_cast<int>(lvChannel[i] * 255)] / 255.0f;
        if (channels >= 3) { // Color image
            ColorSpace cs = {hChannel[i], sChannel[i], lvChannel[i]};
            unsigned char r, g, b;
            ColorSpaceToRGB(cs, r, g, b, colorSpace);
            newData[index] = r;
            newData[index + 1] = g;
            newData[index + 2] = b;
        } else { // Grayscale image
            newData[i] = static_cast<unsigned char>(lvChannel[i] * 255);
        }
    }

    Image equalizedImg(newData, width, height, channels);

    return equalizedImg;
 }


Image ColorFilter::thresholdImage(const Image& image, unsigned char threshold, const char* colorSpace) {
 
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    unsigned char* image_data = image.getImageData();
 
    // Allocate memory for the thresholded grayscale image, not using 'channels' as we output grayscale
    unsigned char* thresholded_img = new unsigned char[width * height];
 
    // Check if we are operating on a grayscale or RGB image
    if (channels >= 3) { // RGB or RGBA
        for (int i = 0; i < width * height; i++) {
            int index = i * channels;
            unsigned char r = image_data[index];
            unsigned char g = image_data[index + 1];
            unsigned char b = image_data[index + 2];
 
            // Convert RGB to the specified color space (HSL or HSV)
            ColorSpace cs = RGBtoColorSpace(r, g, b, colorSpace);
 
            float lv = cs.l;
 
            // Apply threshold
            unsigned char pixelValue = (lv * 255 > threshold) ? 255 : 0;
 
            thresholded_img[i] = pixelValue; // Grayscale output, single channel
        }
    } else { // Grayscale
        for (int i = 0; i < width * height; i++) {
            // Apply threshold directly for grayscale images
            thresholded_img[i] = (image_data[i] >= threshold) ? 255 : 0;
        }
    }
 
    // Create a new Image object for the thresholded image
    Image thresholded(thresholded_img, width, height, 1); 
 
    // Return the new Image object
    return thresholded;
}

Image ColorFilter::addSaltAndPepperNoise(const Image& img, float noisePercent) {

    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels();
    unsigned char* imgData = img.getImageData();

    // Create a copy of the original image data
    unsigned char* noisyData = new unsigned char[width * height * channels];
    std::memcpy(noisyData, imgData, width * height * channels);

    int totalPixels = width * height;
    int noisePixels = static_cast<int>(totalPixels * noisePercent);

    std::mt19937 rng(static_cast<unsigned long>(time(nullptr))); // intitialisation of the random number generator
    std::uniform_int_distribution<int> uniDist(0, totalPixels - 1); // Distribution for pixels

    std::mt19937 rng1(static_cast<unsigned long>(time(nullptr))); // Create a vector containing all pixel indices.
    std::vector<int> indices(totalPixels);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), rng1);


    for (int i = 0; i < noisePixels; ++i) {
        int pixelNumber = indices[i];
        int pixelIndex = pixelNumber * channels;

        unsigned char noiseColor = rng() % 2 * 255; // 0 or 255
        for (int c = 0; c < channels; ++c) {
            if (c < 3) { 
                noisyData[pixelIndex + c] = noiseColor;
            }
        }
    }

    Image noisyImg(noisyData, width, height, channels);

    return noisyImg;
}








