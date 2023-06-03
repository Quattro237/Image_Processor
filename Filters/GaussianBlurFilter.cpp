#include "GaussianBlurFilter.h"

#include <cmath>
#include <numbers>

GaussianBlurFilter::GaussianBlurFilter(const double sigma) : sigma_(sigma) {
    CreateVector();
};

void GaussianBlurFilter::CreateVector() {
    size_t vector_radius = static_cast<size_t>(std::numbers::pi * sigma_);
    size_t vector_size = 2 * vector_radius + 1;
    vector_.reserve(vector_size);

    double const_value = 1 / (std::sqrt(2 * std::numbers::pi) * sigma_);

    for (size_t i = 0; i < vector_size; ++i) {
        size_t diff = i > vector_radius ? i - vector_radius : vector_radius - i;

        vector_.push_back(const_value * std::pow(std::numbers::e, -(std::pow(diff, 2) / (2 * sigma_ * sigma_))));
    }
}

void GaussianBlurFilter::ApplyFilter(Image& image) const {
    int64_t image_width = image.GetWidth();
    int64_t image_height = image.GetHeight();
    std::vector<std::vector<Pixel>> new_pixel_table;
    new_pixel_table.reserve(image_height);

    int64_t center_value = static_cast<int64_t>(vector_.size()) / 2;

    for (int64_t row = 0; row < image_height; ++row) {
        new_pixel_table.push_back({});
        new_pixel_table[row].reserve(image_width);
        for (int64_t column = 0; column < image_width; ++column) {
            Pixel pixel;

            for (int64_t row_move = -center_value; row_move <= center_value; ++row_move) {
                int64_t final_row = std::max(static_cast<int64_t>(0), std::min(row + row_move, image_height - 1));

                pixel.red += image.At(final_row, column).red * vector_[center_value + row_move];
                pixel.green += image.At(final_row, column).green * vector_[center_value + row_move];
                pixel.blue += image.At(final_row, column).blue * vector_[center_value + row_move];
            }

            new_pixel_table[row].push_back(pixel);
        }
    }

    for (int64_t row = 0; row < image_height; ++row) {
        for (int64_t column = 0; column < image_width; ++column) {
            Pixel& pixel = image.At(row, column);
            pixel = {0, 0, 0};

            for (int64_t column_move = -center_value; column_move <= center_value; ++column_move) {
                int64_t final_column =
                    std::max(static_cast<int64_t>(0), std::min(column + column_move, image_width - 1));

                pixel.red += new_pixel_table[row][final_column].red * vector_[center_value + column_move];
                pixel.green += new_pixel_table[row][final_column].green * vector_[center_value + column_move];
                pixel.blue += new_pixel_table[row][final_column].blue * vector_[center_value + column_move];
            }

            pixel.red = std::min(1.0, std::max(0.0, pixel.red));
            pixel.green = std::min(1.0, std::max(0.0, pixel.green));
            pixel.blue = std::min(1.0, std::max(0.0, pixel.blue));
        }
    }
}