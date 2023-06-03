#include "Writer.h"

#include <exception>
#include <fstream>

const uint16_t Writer::BMPFORMAT = 0x4D42;

template <typename Type>
void Write(std::ofstream& file, Type& data, std::streamsize size) {
    file.write(reinterpret_cast<char*>(&data), size);
}

Writer::Writer(const std::string_view path) : path_(path) {
}

void Writer::WriteToFile(BMPFile& image) const {

    // Opening file
    std::ofstream file((std::string(path_)));
    if (!file.is_open()) {
        throw InvalidFileException();
    }

    // Getting DIB and BMP headers
    BMPHeader& bmp_header = image.GetBMPHeader();
    DIBHeader& dib_header = image.GetDIBHeader();

    // Writing current height and width to DIB header
    dib_header.height_of_image = image.GetHeight();
    dib_header.width_of_image = image.GetWidth();

    // Writing BMP header
    Write(file, bmp_header.type, sizeof(bmp_header.type));
    Write(file, bmp_header.size_of_file, sizeof(bmp_header.size_of_file));
    Write(file, bmp_header.first_reserved, sizeof(bmp_header.first_reserved));
    Write(file, bmp_header.second_reserved, sizeof(bmp_header.second_reserved));
    Write(file, bmp_header.pixel_offset, sizeof(bmp_header.pixel_offset));

    // Writing DIB Header
    Write(file, dib_header.size_of_header, sizeof(dib_header.size_of_header));
    Write(file, dib_header.width_of_image, sizeof(dib_header.width_of_image));
    Write(file, dib_header.height_of_image, sizeof(dib_header.height_of_image));
    Write(file, dib_header.num_of_planes, sizeof(dib_header.num_of_planes));
    Write(file, dib_header.bits_per_pixel, sizeof(dib_header.bits_per_pixel));
    Write(file, dib_header.compression, sizeof(dib_header.compression));
    Write(file, dib_header.size_of_image, sizeof(dib_header.size_of_image));
    Write(file, dib_header.pixels_per_metre_x, sizeof(dib_header.pixels_per_metre_x));
    Write(file, dib_header.pixels_per_metre_y, sizeof(dib_header.pixels_per_metre_y));
    Write(file, dib_header.colors_used, sizeof(dib_header.colors_used));
    Write(file, dib_header.important_colors, sizeof(dib_header.important_colors));

    // Writing pixels
    uint32_t line_padding = (4 - (dib_header.width_of_image * 3) % 4) & 3;
    uint32_t bufer = 0;

    for (int64_t i = 0; i < dib_header.height_of_image; ++i) {
        for (int64_t j = 0; j < dib_header.width_of_image; ++j) {
            Pixel& pixel = image.At(i, j);

            bufer = static_cast<uint8_t>(pixel.blue * Pixel::MaxValueDouble);
            Write(file, bufer, 1);
            bufer = static_cast<uint8_t>(pixel.green * Pixel::MaxValueDouble);
            Write(file, bufer, 1);
            bufer = static_cast<uint8_t>(pixel.red * Pixel::MaxValueDouble);
            Write(file, bufer, 1);
        }
        bufer = 0;
        Write(file, bufer, line_padding);
    }

    // Closing file
    file.close();
}
