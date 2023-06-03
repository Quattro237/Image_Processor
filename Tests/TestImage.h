#pragma once

#include "../Image.h"

class TestImage : public Image {
public:
    explicit TestImage(const std::vector<std::vector<Pixel>>& pixels);

    bool CheckPixelTable(std::vector<std::vector<Pixel>> other) const;
};
