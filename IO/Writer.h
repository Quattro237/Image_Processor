#pragma once

#include "../BMPFile.h"

#include <string_view>

class Writer {
public:
    class InvalidFileException : std::exception {};

public:
    explicit Writer(const std::string_view path);

    void WriteToFile(BMPFile& image) const;

    static const uint16_t BMPFORMAT;

private:
    std::string_view path_;
};
