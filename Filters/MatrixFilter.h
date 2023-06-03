#pragma once

#include "Filter.h"

using Matrix = std::vector<std::vector<double>>;

class MatrixFilter : public Filter {
public:
    explicit MatrixFilter(Matrix matrix);

    void ApplyFilter(Image& image) const override;

    static const Matrix EDGE_MATRIX;
    static const Matrix SHARP_MATRIX;

protected:
    Matrix matrix_;
};
