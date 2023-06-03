#include "MatrixFilter.h"

#include <cmath>

const Matrix MatrixFilter::SHARP_MATRIX = {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};
const Matrix MatrixFilter::EDGE_MATRIX = {{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}};

MatrixFilter::MatrixFilter(Matrix matrix) : matrix_(std::move(matrix)){};

void MatrixFilter::ApplyFilter(Image& image) const {
    int64_t image_width = image.GetWidth();
    int64_t image_height = image.GetHeight();
    PixelTable new_pixel_table;
    new_pixel_table.reserve(image_height);

    int64_t center_value_row = static_cast<int64_t>(matrix_.size()) / 2;
    int64_t center_value_column = static_cast<int64_t>(matrix_[0].size()) / 2;

    for (int64_t row = 0; row < image_height; ++row) {
        new_pixel_table.push_back({});
        new_pixel_table[row].reserve(image_width);
        for (int64_t column = 0; column < image_width; ++column) {
            Pixel pixel({0, 0, 0});

            for (int64_t row_move = -center_value_row; row_move <= center_value_row; ++row_move) {
                for (int64_t column_move = -center_value_column; column_move <= center_value_column; ++column_move) {
                    int64_t final_row = std::max(static_cast<int64_t>(0), std::min(row + row_move, image_height - 1));
                    int64_t final_column =
                        std::max(static_cast<int64_t>(0), std::min(column + column_move, image_width - 1));

                    pixel.red += image.At(final_row, final_column).red *
                                 matrix_[center_value_row + row_move][center_value_column + column_move];
                    pixel.green += image.At(final_row, final_column).green *
                                   matrix_[center_value_row + row_move][center_value_column + column_move];
                    pixel.blue += image.At(final_row, final_column).blue *
                                  matrix_[center_value_row + row_move][center_value_column + column_move];
                }
            }

            pixel.red = std::min(1.0, std::max(0.0, pixel.red));
            pixel.green = std::min(1.0, std::max(0.0, pixel.green));
            pixel.blue = std::min(1.0, std::max(0.0, pixel.blue));

            new_pixel_table[row].push_back(pixel);
        }
    }

    image.SetPixelTable(new_pixel_table);
}
