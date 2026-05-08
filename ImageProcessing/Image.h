#pragma once
#include <iostream>
#include <string>
#include <iomanip> 
#include "Point.h"
#include "Rectangle.h"

/**
 * @class Size
 * @brief Represents a 2D size with width and height.
 */
class Size {
private:
    unsigned int width;  /// Width of the size.
    unsigned int height; /// Height of the size.

public:
    /**
     * @brief Constructs a Size object with specified width and height.
     * @param w Width.
     * @param h Height.
     */
    Size(unsigned int w, unsigned int h);
};

/**
 * @class Image
 * @brief Represents a 2D grayscale image.
 */
class Image {
private:
    unsigned char** m_data; /// 2D array of pixel data.
    unsigned int m_width;   /// Width of the image.
    unsigned int m_height;  /// Height of the image.

    /**
     * @brief Allocates memory for the image of specified width and height.
     * @param width Width of the image.
     * @param height Height of the image.
     */
    void allocate(unsigned int width, unsigned int height);

public:
    /**
     * @brief Default constructor. Creates an empty image.
     */
    Image();

    /**
     * @brief Constructs an image with specified width and height.
     * @param w Width.
     * @param h Height.
     */
    Image(unsigned int w, unsigned int h);

    /**
     * @brief Copy constructor.
     * @param other The image to copy from.
     */
    Image(const Image& other);

    /**
     * @brief Destructor. Releases memory used by the image.
     */
    ~Image();

    /**
     * @brief Assignment operator.
     * @param other The image to assign from.
     * @return Reference to this image.
     */
    Image& operator=(const Image& other);

    /**
     * @brief Adds two images.
     * @param other The other image.
     * @return The resulting image.
     */
    Image operator+(const Image& other);

    /**
     * @brief Subtracts another image.
     * @param other The other image.
     * @return The resulting image.
     */
    Image operator-(const Image& other);

    /**
     * @brief Adds a scalar.
     * @param scalar Value to add.
     * @return The resulting image.
     */
    Image operator+(unsigned char scalar);

    /**
     * @brief Subtracts a scalar.
     * @param scalar Value to subtract.
     * @return The resulting image.
     */
    Image operator-(unsigned char scalar);

    /**
     * @brief Multiplies by a scalar.
     * @param scalar Value to multiply with.
     * @return The resulting image.
     */
    Image operator*(unsigned char scalar);

    /**
     * @brief Loads image data from a file.
     * @param imagePath Path to the image file.
     * @return True if loading was successful, false otherwise.
     */
    bool load(std::string imagePath);

    /**
     * @brief Saves image data to a file.
     * @param imagePath Path to save the image.
     * @return True if saving was successful, false otherwise.
     */
    bool save(std::string imagePath);

    /**
     * @brief Extracts a region of interest (ROI) from the image.
     * @param roiImg Output image to store the ROI.
     * @param roiRect Rectangle defining the ROI.
     * @return True if ROI extraction was successful.
     */
    bool getROI(Image& roiImg, Rectangle roiRect);

    /**
     * @brief Extracts a region of interest (ROI) from the image.
     * @param roiImg Output image to store the ROI.
     * @param x X-coordinate of the top-left corner.
     * @param y Y-coordinate of the top-left corner.
     * @param width Width of the ROI.
     * @param height Height of the ROI.
     * @return True if ROI extraction was successful.
     */
    bool getROI(Image& roiImg, unsigned int x, unsigned int y,
        unsigned int width, unsigned int height);

    /**
     * @brief Checks if the image is empty.
     * @return True if image has no data.
     */
    bool isEmpty() const;

    /**
     * @brief Returns the size of the image.
     * @return A Size object representing image dimensions.
     */
    Size size() const;

    /**
     * @brief Returns the width of the image.
     * @return Image width.
     */
    unsigned int width() const;

    /**
     * @brief Returns the height of the image.
     * @return Image height.
     */
    unsigned int height() const;

    /**
     * @brief Accesses a pixel at (x, y) with write access.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @return Reference to the pixel.
     */
    unsigned char& at(unsigned int x, unsigned int y);

    /**
     * @brief Accesses a pixel at a given point with write access.
     * @param pt A Point object.
     * @return Reference to the pixel.
     */
    unsigned char& at(Point pt);

    /**
     * @brief Accesses a pixel at (x, y) with read-only access.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @return Const reference to the pixel.
     */
    const unsigned char& at(unsigned int x, unsigned int y) const;

    /**
     * @brief Accesses a pixel at a given point with read-only access.
     * @param pt A Point object.
     * @return Const reference to the pixel.
     */
    const unsigned char& at(Point pt) const;

    /**
     * @brief Returns a pointer to the beginning of the specified row.
     * @param y Row index.
     * @return Pointer to the row's data.
     */
    unsigned char* row(int y);

    /**
     * @brief Releases the memory used by the image.
     */
    void release();

    /**
     * @brief Creates a zero-initialized image of specified size.
     * @param width Width of the image.
     * @param height Height of the image.
     * @return A new image filled with zeros.
     */
    static Image zeros(unsigned int width, unsigned int height);

    /**
     * @brief Creates a one-initialized image of specified size.
     * @param width Width of the image.
     * @param height Height of the image.
     * @return A new image filled with ones.
     */
    static Image ones(unsigned int width, unsigned int height);

    /**
     * @brief Overloaded output stream operator for displaying image info.
     * @param os Output stream.
     * @param dt Image object.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Image& dt);
};
