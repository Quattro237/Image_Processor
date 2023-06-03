#include "CropFilter.h"

CropFilter::CropFilter(const size_t width, const size_t height) : new_height_(height), new_width_(width){};

void CropFilter::ApplyFilter(Image& image) const {
    image.Resize(new_height_, new_width_);
}
