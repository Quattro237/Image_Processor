#pragma once

#include "MatrixFilter.h"

class EdgeDetectionFilter : public MatrixFilter {
public:
    explicit EdgeDetectionFilter(const double threshold);

    void ApplyFilter(Image& image) const override;

private:
    const double threshold_ = 0;
};
