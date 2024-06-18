/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

#ifndef PROJECTION_H
#define PROJECTION_H

#include "Volume.h"
#include <vector>

/**
 * @brief Class for performing various types of projections on volumetric data.
 */
class Projection {
public:
    /**
     * @brief Constructor to initialize width and height of the projection.
     * @param width The width of the projection.
     * @param height The height of the projection.
     */
    Projection(int width, int height);

    /**
     * @brief Perform Maximum Intensity Projection (MIP) on the volume data.
     * @param volumeData The volumetric data to perform the projection on.
     * @return The 2D projection result.
     */
    std::vector<std::vector<unsigned char>> performMIP(const std::vector<std::vector<std::vector<unsigned char>>>& volumeData);

    /**
     * @brief Perform Minimum Intensity Projection (MinIP) on the volume data.
     * @param volumeData The volumetric data to perform the projection on.
     * @return The 2D projection result.
     */
    std::vector<std::vector<unsigned char>> performMinIP(const std::vector<std::vector<std::vector<unsigned char>>>& volumeData);

    /**
     * @brief Perform Average Intensity Projection (AIP) on the volume data.
     * @param volumeData The volumetric data to perform the projection on.
     * @return The 2D projection result.
     */
    std::vector<std::vector<unsigned char>> performAIP(const std::vector<std::vector<std::vector<unsigned char>>>& volumeData);

   /**
     * @brief Get the start and end indices based on user input.
     * @param volumeSize The size of the volume.
     * @param startIdx Reference to the start index.
     * @param endIdx Reference to the end index.
     */
    void getStartEndIndices(int volumeSize, int& startIdx, int& endIdx); 

    /**
     * @brief Perform the specified projection type on the given volume data.
     * @param volume The volumetric data to perform the projection on.
     * @param projectionType The type of projection to perform ("MIP", "MinIP", or "AIP").
     * @return The 2D projection result.
     */
    std::vector<std::vector<unsigned char>> performProjection(const Volume& volume, const std::string& projectionType);

private:
    int width; /**< The width of the projection. */
    int height;  /**< The height of the projection. */
};

#endif // PROJECTION_H
