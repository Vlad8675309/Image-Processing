#include "ImageProcessing.h"
#include <algorithm>


BrightnessContrast::BrightnessContrast() : alpha(1), beta(0) {}

BrightnessContrast::BrightnessContrast(float alpha, float beta) : alpha(alpha), beta(beta) {}

void BrightnessContrast::process(const Image& src, Image& dst) {
	dst = Image(src.width(), src.height());

	for (unsigned int y = 0; y < src.height(); ++y) {
		for (unsigned int x = 0; x < src.width(); ++x) {
			float pixel = src.at(x, y);	
			float modified = alpha * pixel + beta;
			dst.at(x, y) = static_cast<unsigned char>(std::clamp(modified, 0.0f, 255.0f));
		}
	}
}

GammaCorrection::GammaCorrection() : gamma(1) {}

GammaCorrection::GammaCorrection(float gamma) : gamma(gamma) {}

void GammaCorrection::process(const Image& src, Image& dst) {
	dst = Image(src.width(), src.height());

	for (unsigned int y = 0; y < src.height(); ++y) {
		for (unsigned int x = 0; x < src.width(); ++x) {
			float pixel = src.at(x, y);
			float modified = 255 * std::pow(pixel / 255, gamma);
			dst.at(x, y) = static_cast<unsigned char>(std::clamp(modified, 0.0f, 255.0f));
		}
	}
}

Convolution::Convolution(const std::vector<std::vector<float>>& kernel, float (*scaleFunction)(const std::vector<std::vector<float>>&, float)) : 
    kernel(kernel), scaleFunction(scaleFunction) {}

void Convolution::process(const Image& src, Image& dst) {
    if (src.isEmpty() || kernel.empty()) return;

    dst = Image(src.width(), src.height());
    int kCenterX = kernel[0].size() / 2;
    int kCenterY = kernel.size() / 2;

    for (int y = 0; y < src.height(); ++y) {
        for (int x = 0; x < src.width(); ++x) {
            float sum = 0;

            for (int ky = 0; ky < kernel.size(); ++ky) {
                for (int kx = 0; kx < kernel[ky].size(); ++kx) {
                    int srcX = x + kx - kCenterX;
                    int srcY = y + ky - kCenterY;

                    srcX = std::clamp(srcX, 0, static_cast<int>(src.width()) - 1);
                    srcY = std::clamp(srcY, 0, static_cast<int>(src.height()) - 1);

                    sum += kernel[ky][kx] * src.at(srcX,srcY);
                }
            }

            sum = scaleFunction(kernel, sum);
            dst.at(x, y) = sum;
        }
    }
}

float scaleBlur(const std::vector<std::vector<float>>& kernel, float value) {
	float sum = 0;
	for (auto& row : kernel) {
		for (auto v : row) {
			sum += v;
		}
	}
	if (sum != 0) {
		value *= 1 / sum;
	}

	return std::clamp(value, 0.0f, 255.0f);

}

float scaleSobel(const std::vector<std::vector<float>>& kernel, float value) {
	float maxVal = 0;
	for (auto& row : kernel)
		for (auto v : row)
			maxVal += std::abs(v);

	float range = maxVal * 255;

	value = (value + range) * (255 / (2 * range));

	return std::clamp(value, 0.0f, 255.0f);
}