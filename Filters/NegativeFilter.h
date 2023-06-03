#pragma once

#include "Filter.h"

class NegativeFilter : public Filter {
public:
    void ApplyFilter(Image& image) const override;
};
