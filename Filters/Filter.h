#pragma once

#include "../BMPFile.h"

class Filter {
public:
    virtual void ApplyFilter(Image& image) const = 0;
    virtual ~Filter();
};
