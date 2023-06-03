#include "TwirlFilter.h"

#include <cmath>
#include <numbers>

const double TwirlFilter::MAX_ANGLE = 180.0;

TwirlFilter::TwirlFilter(const double angle) : pi_angle_(((angle - MAX_ANGLE) * std::numbers::pi) / MAX_ANGLE){};

void TwirlFilter::ApplyFilter(Image& image) const {
    int64_t image_width = image.GetWidth();
    int64_t image_height = image.GetHeight();

    PixelTable new_pixel_table(image_height);

    int64_t center_column = image_width / 2;
    int64_t center_row = image_height / 2;

    for (int64_t row = 0; row < image_height; ++row) {
        new_pixel_table[row] = std::vector<Pixel>(image_width);

        for (int64_t column = 0; column < image_width; ++column) {
            Pixel& pixel = new_pixel_table[row][column];

            int64_t row_diff = row > center_row ? row - center_row : center_row - row;
            int64_t column_diff = column > center_column ? column - center_column : center_column - column;

            double distance = std::sqrt(std::pow(row_diff, 2) + std::pow(column_diff, 2));

            double new_angle =
                std::atan2(row_diff, column_diff) +
                pi_angle_ * ((static_cast<double>(center_row) - distance) / static_cast<double>(center_row));

            int64_t new_row = center_row + static_cast<int64_t>(distance * std::sin(new_angle));
            int64_t new_column = center_column + static_cast<int64_t>(distance * std::cos(new_angle));

            new_row = std::min(image_height - 1, std::max(static_cast<int64_t>(0), new_row));
            new_column = std::min(image_width - 1, std::max(static_cast<int64_t>(0), new_column));

            pixel.red = image.At(new_row, new_column).red;
            pixel.green = image.At(new_row, new_column).green;
            pixel.blue = image.At(new_row, new_column).blue;
        }
    }

    image.SetPixelTable(new_pixel_table);
}