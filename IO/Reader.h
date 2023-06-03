#pragma once

#include "../BMPFile.h"

#include <string_view>

class Reader {
public:
    class InvalidFileException : public std::exception {};
    class InvalidFileFormatException : public std::exception {};

public:
    explicit Reader(const std::string_view path);

    void ReadToBMP(BMPFile& image) const;

    static const uint16_t BMPFORMAT;

private:
    std::string_view path_;
};
