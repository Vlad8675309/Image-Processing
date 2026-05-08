#include "Rectangle.h"

unsigned int Rectangle::getX() const { return x; }

unsigned int Rectangle::getY() const { return y; }

unsigned int Rectangle::getWidth() const { return width; }

unsigned int Rectangle::getHeight() const { return height; }

Rectangle::Rectangle() : x(0), y(0), width(0), height(0) {}

Rectangle::Rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : x(x), y(y), width(w), height(h) {}

Rectangle::Rectangle(Point tl, Point br) : x(tl.getX()), y(tl.getY()), width(br.getX() - tl.getX()), height(tl.getY() - br.getY()) {}

std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
    os << "Top Left: Point(" << rect.getX() << ", " << rect.getY() << "\nHeight: " << rect.getHeight() << "\nWidth: " << rect.getWidth();
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& rect) {
    is >> rect.x >> rect.y >> rect.width >> rect.height;
    return is;
}

Rectangle Rectangle::operator&(const Rectangle& other) {
    unsigned int left = std::max(this->getX(), other.getX());
    unsigned int right = std::min(this->getX() + this->getWidth(), other.getX() + other.getWidth());
    unsigned int top = std::max(this->getY(), other.getY());
    unsigned int bottom = std::min(this->getY() + this->getHeight(), other.getY() + other.getHeight());
    if (right > left && bottom > top) {
        return Rectangle(left, top, right - left, bottom - top);
    }
    else {
        return Rectangle(0, 0, 0, 0);
    }
}

Rectangle Rectangle::operator|(const Rectangle& other) {
    unsigned int left = std::min(this->getX(), other.getX());
    unsigned int right = std::max(this->getX() + this->getWidth(), other.getX() + other.getWidth());
    unsigned int top = std::min(this->getY(), other.getY());
    unsigned int bottom = std::max(this->getY() + this->getHeight(), other.getY() + other.getHeight());
    return Rectangle(left, top, right - left, bottom - top);
}

Rectangle Rectangle::operator+(const Point& t) {
    return Rectangle(this->getX() + t.getX(), this->getY() + t.getY(), this->getWidth(), this->getHeight());
}

Rectangle Rectangle::operator-(const Point& t) {
    return Rectangle(this->getX() - t.getX(), this->getY() - t.getY(), this->getWidth(), this->getHeight());
}
