#pragma once

#include "Image.h"

struct BMPHeader {
    uint16_t type = 0;
    uint32_t size_of_file = 0;
    uint16_t first_reserved = 0;
    uint16_t second_reserved = 0;
    uint32_t pixel_offset = 0;
};

struct DIBHeader {
    uint32_t size_of_header = 0;
    uint32_t width_of_image = 0;
    uint32_t height_of_image = 0;
    uint16_t num_of_planes = 0;
    uint16_t bits_per_pixel = 0;
    uint32_t compression = 0;
    uint32_t size_of_image = 0;
    uint32_t pixels_per_metre_x = 0;
    uint32_t pixels_per_metre_y = 0;
    uint32_t colors_used = 0;
    uint32_t important_colors = 0;
};

class BMPFile : public Image {
public:
    BMPFile() = default;

    BMPHeader& GetBMPHeader();
    DIBHeader& GetDIBHeader();

private:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
};
