/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

/**
 * @brief Represents an image.
 */

#ifndef IMAGE_H
#define IMAGE_H
 
#include <iostream>
#include <cstring>
 
class Image {
private:
    unsigned char* imageData; /**< Pointer to the image data */
    int width; /**< Width of the image */
    int height; /**< Height of the image */
    int channels; /**< Number of color channels */
 
public:
    /**
     * @brief Default constructor.
     */
    Image();
 
    /**
     * @brief Constructor with image data, width, height, and channels.
     * @param imageData Pointer to the image data
     * @param w Width of the image
     * @param h Height of the image
     * @param ch Number of color channels
     */
    Image(unsigned char* imageData, int w, int h, int ch);
 
    /**
     * @brief Destructor.
     */
    ~Image();
    
    /**
     * @brief Copy constructor.
     * @param other Another Image object to be copied
     */
    Image(const Image& other);
 
    /**
     * @brief Copy assignment operator.
     * @param other Another Image object to be assigned
     * @return Reference to the modified Image object
     */
    Image& operator=(const Image& other);
 
    /**
     * @brief Get the pixel value at specified coordinates.
     * @param x X-coordinate
     * @param y Y-coordinate
     * @return Pointer to the pixel value
     */
    unsigned char* getPixel(int x, int y) const;
 
    /**
     * @brief Set the pixel value at specified coordinates.
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param r Red channel value
     * @param g Green channel value
     * @param b Blue channel value
     */
    void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
 
    /**
     * @brief Print image metadata.
     */
    void displayImageInfo();
 
    // Getters
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    unsigned char* getImageData() const;
};
 
#endif // IMAGE_H