#include "Image.h"
#include <algorithm>
#include <fstream>
#include <exception>


Size::Size(unsigned int w, unsigned int h) : width(w), height(h) {}

Image::Image() : m_data(nullptr), m_height(0), m_width(0) {}

Image::Image(unsigned int w, unsigned int h) : m_width(w), m_height(h) {
    allocate(w, h);
}

Image::Image(const Image& other) : m_width(other.m_width), m_height(other.m_height) {
    allocate(m_width, m_height);
    for (unsigned int i = 0; i < other.m_height; ++i) {
        for (unsigned int j = 0; j < other.m_width; ++j) {
            m_data[i][j] = other.m_data[i][j];
        }
    }
}

void Image::allocate(unsigned int w, unsigned int h) {
    m_data = new unsigned char* [h];
    for (int i = 0; i < h; ++i) {
        m_data[i] = new unsigned char [w];
    }
}

void Image::release() {
    if (m_data != nullptr) {
        for (unsigned int i = 0; i < m_height; ++i) {
            delete[] m_data[i];
        }
        delete[] m_data;
        m_data = nullptr;
    }
    m_width = m_height = 0;
}

Image::~Image() {
    release();
}

Image& Image::operator=(const Image& other) {
    if (this != &other) {
        release();
        m_width = other.m_width;
        m_height = other.m_height;
        allocate(m_width, m_height);
        for (unsigned int i = 0; i < m_height; ++i) {
            for (unsigned int j = 0; j < m_width; ++j) {
                m_data[i][j] = other.m_data[i][j];
            }
        }
    }
    return *this;
}

Image Image::operator+(const Image& other) {
    if (m_width != other.m_width || m_height != other.m_height) {
        throw std::exception();
    }

    Image result(m_width, m_height);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            int sum = m_data[i][j] + other.m_data[i][j];
            result.m_data[i][j] = static_cast<unsigned char>(std::clamp(sum, 0, 255));
        }
    }
    return result;
}

Image Image::operator-(const Image& other) {
    if (m_width != other.m_width || m_height != other.m_height) {
        throw std::exception();
    }

    Image result(m_width, m_height);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            int diff = m_data[i][j] - other.m_data[i][j];
            result.m_data[i][j] = static_cast<unsigned char>(std::clamp(diff, 0, 255));
        }
    }
    return result;
}

Image Image::operator+(unsigned char scalar) { 
    Image result(m_width, m_height);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            int sum = m_data[i][j] + scalar;
            result.m_data[i][j] = static_cast<unsigned char>(std::clamp(sum, 0, 255));
        }
    }
    return result;
}

Image Image::operator-(unsigned char scalar) {
    Image result(m_width, m_height);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            int diff = m_data[i][j] - scalar;
            result.m_data[i][j] = static_cast<unsigned char>(std::clamp(diff, 0, 255));
        }
    }
    return result;
}


Image Image::operator*(unsigned char scalar) {
    Image result(m_width, m_height);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            int prod = m_data[i][j] * scalar;
            result.m_data[i][j] = static_cast<unsigned char>(std::clamp(prod, 0, 255));
        }
    }
    return result;
}

bool Image::load(std::string imagePath) {
    std::ifstream file(imagePath);
    if (!file.is_open()) {
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;

    if (magicNumber != "P2") {
        return false;
    }

    unsigned int width, height, maxValue;
    file >> width >> height >> maxValue;

    release();
    m_width = width;
    m_height = height;
    allocate(width, height);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            int value;
            file >> value;
            m_data[i][j] = static_cast<unsigned char>(value);
        }
    }

    file.close();
    return true;
}

bool Image::save(std::string imagePath) {
    std::ofstream file(imagePath);

    if (!file.is_open()) {
        return false;
    }

    file << "P2\n";
    file << m_width << " " << m_height <<"\n";
    unsigned int maxValue = 255;
    file << maxValue << "\n";

    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            file << static_cast<unsigned int>(m_data[i][j]) << " ";
        }
        file << "\n";
    }

    file.close();
    return true;
}

bool Image::getROI(Image& roiImg, Rectangle roiRect) {
    return getROI(roiImg, roiRect.getX(), roiRect.getY(), roiRect.getWidth(), roiRect.getHeight());
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if (x + width > m_width || y + height > m_height) {
        return false;
    }
    
    roiImg.release();
    roiImg.m_height = height;
    roiImg.m_width = width;
    roiImg.allocate(height, width);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            roiImg.m_data[i][j] = m_data[y + i][x + j];
        }
    }

    return true;
}

unsigned int Image::width() const {
    return m_width;
}

unsigned int Image::height() const {
    return m_height;
}

Size Image::size() const {
    return Size(m_width, m_height);
}

bool Image::isEmpty() const {
    return m_data == nullptr || m_width == 0 || m_height == 0;
}

unsigned char& Image::at(unsigned int x, unsigned int y) {
    if (x >= m_width || y >= m_height) {
        throw std::exception();
    }
    return m_data[y][x];
}

unsigned char& Image::at(Point p) {
    return at(p.getX(), p.getY());
}

const unsigned char& Image::at(unsigned int x, unsigned int y) const {
    if (x >= m_width || y >= m_height) {
        throw std::exception();
    }
    return m_data[y][x];
}

const unsigned char& Image::at(Point p) const {
    return at(p.getX(), p.getY());
}

unsigned char* Image::row(int y) {
    if (y < 0 || static_cast<unsigned int>(y) >= m_height) {
        throw std::exception();
    }
    return m_data[y];
}

Image Image::zeros(unsigned int width, unsigned int height) {
    Image img(width, height);
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            img.m_data[i][j] = 0;
        }
    }
    return img;
}

Image Image::ones(unsigned int width, unsigned int height) {
    Image img(width, height);
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            img.m_data[i][j] = 1;
        }
    }
    return img;
}

std::ostream& operator<<(std::ostream& os, const Image& dt) {
    for (unsigned int i = 0; i < dt.m_height; ++i) {
        for (unsigned int j = 0; j < dt.m_width; ++j) {
            os << std::setw(3) << static_cast<int>(dt.m_data[i][j]) << " ";
        }
        os << "\n";
    }
    return os;
}
