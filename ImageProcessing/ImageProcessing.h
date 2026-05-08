#pragma once
#include "Image.h"
#include <vector>

/**
 * @class ImageProcessing
 * @brief Abstract class for image processing operations.
 */
class ImageProcessing {
public:
    /**
     * @brief Processes an image.
     * @param src Source image.
     * @param dst Destination image after processing.
     */
    virtual void process(const Image& src, Image& dst) = 0;
};

/**
 * @class BrightnessContrast
 * @brief Adjusts brightness and contrast of an image.
 */
class BrightnessContrast : public ImageProcessing {
private:
    float alpha; /// Gain.
    float beta;  /// Bias.

public:
    /**
     * @brief Default constructor.
     */
    BrightnessContrast();

    /**
     * @brief Constructs with specific contrast and brightness.
     * @param alpha Gain.
     * @param beta Bias.
     */
    BrightnessContrast(float alpha, float beta);

    /**
     * @brief Applies brightness and contrast adjustment.
     * @param src Source image.
     * @param dst Destination image.
     */
    void process(const Image& src, Image& dst) override;
};

/**
 * @class GammaCorrection
 * @brief Applies gamma correction to an image.
 */
class GammaCorrection : public ImageProcessing {
private:
    float gamma; /// Gamma encoding factor.

public:
    /**
     * @brief Default constructor.
     */
    GammaCorrection();

    /**
     * @brief Constructs with a specific gamma value.
     * @param gamma Gamma encoding factor.
     */
    GammaCorrection(float gamma);

    /**
     * @brief Applies gamma correction.
     * @param src Source image.
     * @param dst Destination image.
     */
    void process(const Image& src, Image& dst) override;
};

/**
 * @class Convolution
 * @brief Applies a convolution filter to an image.
 */
class Convolution : public ImageProcessing {
private:
    std::vector<std::vector<float>> kernel; /// Convolution kernel.
    float (*scaleFunction)(const std::vector<std::vector<float>>&, float); /// Scaling function.

public:
    /**
     * @brief Constructs a convolution process.
     * @param kernel Convolution kernel matrix.
     * @param scaleFunction Function to scale pixel values.
     */
    Convolution(const std::vector<std::vector<float>>& kernel,
        float (*scaleFunction)(const std::vector<std::vector<float>>&, float));

    /**
     * @brief Applies the convolution filter.
     * @param src Source image.
     * @param dst Destination image.
     */
    void process(const Image& src, Image& dst) override;
};

/**
 * @brief Scales pixel value for blur effect.
 * @param kernel Convolution kernel.
 * @param value Raw pixel value.
 * @return Scaled pixel value.
 */
float scaleBlur(const std::vector<std::vector<float>>& kernel, float value);

/**
 * @brief Scales pixel value for Sobel edge detection.
 * @param kernel Convolution kernel.
 * @param value Raw pixel value.
 * @return Scaled pixel value.
 */
float scaleSobel(const std::vector<std::vector<float>>& kernel, float value);
