#pragma once

#include "Filter.h"

class CropFilter : public Filter {
public:
    CropFilter(const size_t width, const size_t height);

    void ApplyFilter(Image& image) const override;

private:
    const uint32_t new_height_ = 0;
    const uint32_t new_width_ = 0;
};
