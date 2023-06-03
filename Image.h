#pragma once

#include <vector>
#include <cstdint>

struct Pixel {
    double red = 0;
    double green = 0;
    double blue = 0;

    static constexpr double MaxValueDouble = 255.0;
};

using PixelTable = std::vector<std::vector<Pixel>>;

class Image {
public:
    uint32_t GetHeight() const;
    uint32_t GetWidth() const;
    void Resize(int64_t height, int64_t width);
    Pixel& At(int64_t height, int64_t width);
    void SetPixelTable(const PixelTable& new_pixel_table);

    virtual ~Image();

protected:
    uint32_t height_ = 0;
    uint32_t width_ = 0;
    PixelTable pixels_;
};
