#include "Image.h"

uint32_t Image::GetHeight() const {
    return height_;
}

uint32_t Image::GetWidth() const {
    return width_;
}

void Image::Resize(int64_t new_height, int64_t new_width) {
    int64_t height_delta = height_ > new_height ? height_ - new_height : 0;
    int64_t width_delta = width_ > new_width ? width_ - new_width : 0;
    PixelTable new_pixel_table;
    new_pixel_table.reserve(height_ - height_delta);

    for (size_t row = 0; row < height_ - height_delta; ++row) {
        new_pixel_table.push_back({});
        new_pixel_table[row].reserve(width_ - width_delta);
        for (size_t column = 0; column < width_ - width_delta; ++column) {
            new_pixel_table[row].push_back(pixels_[row + height_delta][column]);
        }
    }

    pixels_ = std::move(new_pixel_table);
    height_ = height_ - height_delta;
    width_ = width_ - width_delta;
}

void Image::SetPixelTable(const PixelTable& new_pixel_table) {
    pixels_ = std::move(new_pixel_table);
    height_ = pixels_.size();
    width_ = pixels_[0].size();
}

Pixel& Image::At(int64_t height, int64_t width) {
    return pixels_[height][width];
}

Image::~Image() = default;
