#include "Reader.h"

#include <exception>
#include <fstream>

const uint16_t Reader::BMPFORMAT = 0x4D42;

template <typename Type>
void Read(std::ifstream& file, Type& result, std::streamsize size) {
    file.read(reinterpret_cast<char*>(&result), size);
}

Reader::Reader(const std::string_view path) : path_(path) {
}

void Reader::ReadToBMP(BMPFile& image) const {

    // Opening file
    std::ifstream file((std::string(path_)));
    if (!file.is_open()) {
        throw InvalidFileException();
    }

    // Getting DIB and BMP headers
    BMPHeader& bmp_header = image.GetBMPHeader();
    DIBHeader& dib_header = image.GetDIBHeader();

    // Reading of BMP header
    Read(file, bmp_header.type, sizeof(bmp_header.type));

    // Checking whether file has BMP format
    if (bmp_header.type != BMPFORMAT) {
        throw InvalidFileFormatException();
    }

    // Continuing reading of BMP header
    Read(file, bmp_header.size_of_file, sizeof(bmp_header.size_of_file));
    Read(file, bmp_header.first_reserved, sizeof(bmp_header.first_reserved));
    Read(file, bmp_header.second_reserved, sizeof(bmp_header.second_reserved));
    Read(file, bmp_header.pixel_offset, sizeof(bmp_header.pixel_offset));

    // Reading of DIB Header
    Read(file, dib_header.size_of_header, sizeof(dib_header.size_of_header));
    Read(file, dib_header.width_of_image, sizeof(dib_header.width_of_image));
    Read(file, dib_header.height_of_image, sizeof(dib_header.height_of_image));
    Read(file, dib_header.num_of_planes, sizeof(dib_header.num_of_planes));
    Read(file, dib_header.bits_per_pixel, sizeof(dib_header.bits_per_pixel));
    Read(file, dib_header.compression, sizeof(dib_header.compression));
    Read(file, dib_header.size_of_image, sizeof(dib_header.size_of_image));
    Read(file, dib_header.pixels_per_metre_x, sizeof(dib_header.pixels_per_metre_x));
    Read(file, dib_header.pixels_per_metre_y, sizeof(dib_header.pixels_per_metre_y));
    Read(file, dib_header.colors_used, sizeof(dib_header.colors_used));
    Read(file, dib_header.important_colors, sizeof(dib_header.important_colors));

    // Reading pixels
    PixelTable new_pixel_table(dib_header.height_of_image, std::vector<Pixel>(dib_header.width_of_image));
    image.SetPixelTable(new_pixel_table);
    uint32_t bufer = 0;
    uint32_t line_padding = (4 - (dib_header.width_of_image * 3) % 4) & 3;

    for (int64_t i = 0; i < dib_header.height_of_image; ++i) {
        for (int64_t j = 0; j < dib_header.width_of_image; ++j) {
            Pixel& pixel = image.At(i, j);
            Read(file, bufer, 1);
            pixel.blue = static_cast<double>(bufer) / Pixel::MaxValueDouble;
            Read(file, bufer, 1);
            pixel.green = static_cast<double>(bufer) / Pixel::MaxValueDouble;
            Read(file, bufer, 1);
            pixel.red = static_cast<double>(bufer) / Pixel::MaxValueDouble;
        }
        file.seekg(line_padding, std::ios_base::cur);
    }

    // CLosing file
    file.close();
}
