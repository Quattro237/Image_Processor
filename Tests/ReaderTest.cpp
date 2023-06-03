#include <catch.hpp>

#include "../BMPFile.h"
#include "../IO/Reader.h"

TEST_CASE("Run with JPG image") {
    Reader reader("../tasks/image_processor/Tests/Images/Test_Image.jpg");
    BMPFile bmp_file;
    REQUIRE_THROWS_AS(reader.ReadToBMP(bmp_file), Reader::InvalidFileFormatException);
}

TEST_CASE("Run with non-existing file") {
    Reader reader("../tasks/image_processor/Tests/Images/Non-existing.bmp");
    BMPFile bmp_file;
    REQUIRE_THROWS_AS(reader.ReadToBMP(bmp_file), Reader::InvalidFileException);
}

TEST_CASE("Run with BMP image") {
    Reader reader("../tasks/image_processor/Tests/Images/Test_Image.BMP");
    BMPFile bmp_file;
    reader.ReadToBMP(bmp_file);

    REQUIRE(bmp_file.GetHeight() == 1001);
    REQUIRE(bmp_file.GetWidth() == 1419);
}