#pragma once
#include <iostream>

/**
 * @class Point
 * @brief Represents a 2D point.
 */
class Point {
private:
    unsigned int x; /// X-coordinate.
    unsigned int y; /// Y-coordinate.

public:
    /**
     * @brief Default constructor.
     */
    Point();

    /**
     * @brief Constructs a Point with specified coordinates.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     */
    Point(unsigned int x, unsigned int y);

    /**
     * @brief Returns the X-coordinate.
     * @return X value.
     */
    int getX() const;

    /**
     * @brief Returns the Y-coordinate.
     * @return Y value.
     */
    int getY() const;

    /**
     * @brief Outputs a point to a stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Point& pt);

    /**
     * @brief Inputs a point from a stream.
     */
    friend std::istream& operator>>(std::istream& is, Point& pt);
};
