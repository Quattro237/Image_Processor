#pragma once

#include "Filter.h"

class GrayscaleFilter : public Filter {
public:
    void ApplyFilter(Image& image) const override;

    static const double RED_COMPONENT;
    static const double GREEN_COMPONENT;
    static const double BLUE_COMPONENT;
};
