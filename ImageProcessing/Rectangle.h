#pragma once
#include "Point.h"

/**
 * @class Rectangle
 * @brief Represents a 2D rectangle.
 */
class Rectangle {
private:
    unsigned int x;      /// X-coordinate of top-left corner.
    unsigned int y;      /// Y-coordinate of top-left corner.
    unsigned int width;  /// Width of the rectangle.
    unsigned int height; /// Height of the rectangle.

public:
    /**
     * @brief Returns X-coordinate.
     */
    unsigned int getX() const;

    /**
     * @brief Returns Y-coordinate.
     */
    unsigned int getY() const;

    /**
     * @brief Returns width.
     */
    unsigned int getWidth() const;

    /**
     * @brief Returns height.
     */
    unsigned int getHeight() const;

    /**
     * @brief Default constructor.
     */
    Rectangle();

    /**
     * @brief Constructs a rectangle from top-left point coordinates and size.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param w Width.
     * @param h Height.
     */
    Rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    /**
     * @brief Constructs a rectangle from two corner points.
     * @param tl Top-left point.
     * @param br Bottom-right point.
     */
    Rectangle(Point tl, Point br);

    /**
     * @brief Intersection with another rectangle.
     * @param other Another rectangle.
     * @return Intersection rectangle.
     */
    Rectangle operator&(const Rectangle& other);

    /**
     * @brief Union with another rectangle.
     * @param other Another rectangle.
     * @return Union rectangle.
     */
    Rectangle operator|(const Rectangle& other);

    /**
     * @brief Moves rectangle by a point (translation).
     * @param t Translation point.
     * @return Translated rectangle.
     */
    Rectangle operator+(const Point& t);

    /**
     * @brief Moves rectangle in the opposite direction.
     * @param t Translation point.
     * @return Translated rectangle.
     */
    Rectangle operator-(const Point& t);

    /**
     * @brief Outputs a rectangle to a stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);

    /**
     * @brief Inputs a rectangle from a stream.
     */
    friend std::istream& operator>>(std::istream& is, Rectangle& rect);
};
