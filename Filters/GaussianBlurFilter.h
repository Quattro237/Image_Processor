#pragma once

#include "Filter.h"

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(const double sigma);

    void ApplyFilter(Image& image) const override;

private:
    void CreateVector();

private:
    const double sigma_ = 0;
    std::vector<double> vector_;
};
