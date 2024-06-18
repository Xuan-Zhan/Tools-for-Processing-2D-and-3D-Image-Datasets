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

class Volume {
public:
    std::vector<unsigned char> data;  /**< Raw volumetric data. */
    int width, height, depth, channels; /**< Width/High/Depth/Number of channels of the volumetric data. */
    /**
     * @brief Default constructor.
     */
    Volume();
    /**
     * @brief Destructor.
     */
    ~Volume();
    
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
    
};

#endif

