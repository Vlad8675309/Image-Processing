#pragma once
#include "Image.h"

/**
 * @class DrawingModule
 * @brief Provides methods to draw basic shapes on an image.
 */
class DrawingModule {
public:
    /**
     * @brief Draws a circle on the image.
     * @param img Image to draw on.
     * @param center Center of the circle.
     * @param radius Radius of the circle.
     * @param color Grayscale color value.
     */
    static void drawCircle(Image& img, Point center, int radius, unsigned char color);

    /**
     * @brief Draws a line between two points.
     * @param img Image to draw on.
     * @param p1 Starting point.
     * @param p2 Ending point.
     * @param color Grayscale color value.
     */
    static void drawLine(Image& img, Point p1, Point p2, unsigned char color);

    /**
     * @brief Draws a rectangle on the image.
     * @param img Image to draw on.
     * @param r Rectangle to draw.
     * @param color Grayscale color value.
     */
    static void drawRectangle(Image& img, Rectangle r, unsigned char color);

    /**
     * @brief Draws a rectangle using two corner points.
     * @param img Image to draw on.
     * @param tl Top-left point.
     * @param br Bottom-right point.
     * @param color Grayscale color value.
     */
    static void drawRectangle(Image& img, Point tl, Point br, unsigned char color);
};
