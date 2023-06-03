#include "TestImage.h"

#include <cmath>

TestImage::TestImage(const std::vector<std::vector<Pixel>>& pixels) {
    pixels_ = std::move(pixels);
    height_ = pixels_.size();
    width_ = pixels_[0].size();
}

bool TestImage::CheckPixelTable(std::vector<std::vector<Pixel>> other) const {
    if (other.size() != height_ || other[0].size() != width_) {
        return false;
    }

    const double epsilon = 0.01;

    for (size_t row = 0; row < height_; ++row) {
        for (size_t column = 0; column < width_; ++column) {
            if (std::fabs(pixels_[row][column].red - other[row][column].red) >= epsilon ||
                std::fabs(pixels_[row][column].green - other[row][column].green) >= epsilon ||
                std::fabs(pixels_[row][column].blue - other[row][column].blue) >= epsilon) {
                return false;
            }
        }
    }

    return true;
}