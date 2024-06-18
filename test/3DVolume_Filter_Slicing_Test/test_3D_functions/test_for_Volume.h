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
 * @file Volume.h
 * @brief Definition of Volume class for handling volumetric data.
 */

#ifndef VOLUME_H
#define VOLUME_H

#include <vector>
#include <string>

/**
 * @brief Class for handling 3D volume data.
 */

class test_Volume {
public:
    /**
     * @brief Default constructor.
     */
    test_Volume();
    /**
     * @brief Destructor.
     */
    ~test_Volume();

     /**
     * @brief Load data from a folder containing PNG images.
     * @param folderPath The path to the folder containing PNG images.
     * @return True if loading is successful, false otherwise.
     */
    bool loadFromFolder(const std::string& folderPath);

    /**
     * @brief Save volumetric data slices to a folder as PNG images.
     * @param folderPath The path to the folder where images will be saved.
     * @return True if saving is successful, false otherwise.
     */
    bool saveToFolder(const std::string& folderPath) const;

    /**
     * @brief Save a 2D image to a file.
     * @param filename The filename to save the image to.
     * @param image The 2D image data to save.
     */
    void saveImage(const std::string& filename, const std::vector<std::vector<unsigned char>>& image);
    
    /**
     * @brief Get a pointer to the raw volumetric data.
     * @return Pointer to the raw volumetric data.
     */
    const unsigned char* getData() const;
    
    /**
     * @brief Set the raw volumetric data.
     * @param newData The new volumetric data.
     */
    void setData(const std::vector<unsigned char>& newData);
    
    /**
     * @brief Get the width of the volumetric data.
     * @return The width of the volumetric data.
     */
    int getWidth() const;
    /**
     * @brief Get the height of the volumetric data.
     * @return The height of the volumetric data.
     */
    int getHeight() const;
    /**
     * @brief Get the depth of the volumetric data.
     * @return The depth of the volumetric data.
     */
    int getDepth() const;
    /**
     * @brief Get the number of channels in the volumetric data.
     * @return The number of channels in the volumetric data.
     */
    int getChannels() const;
    

private:
    int width, height, depth, channels; /**< Width/High/Depth/Number of channels of the volumetric data. */
    std::vector<unsigned char> data;  /**< Raw volumetric data. */
};

#endif

