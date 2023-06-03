#include <catch.hpp>

#include "../BMPFile.h"
#include "../IO/Reader.h"
#include "../IO/Writer.h"
#include "BitwiseFileComprassion.h"

TEST_CASE("Run with non-existing path") {
    Reader reader("../tasks/image_processor/Tests/Images/Test_Image.BMP");
    BMPFile bmp_file;

    Writer writer("../tasks/image_processor/Tests/Images/New_folder/Output.bmp");
    REQUIRE_THROWS_AS(writer.WriteToFile(bmp_file), Writer::InvalidFileException);
}

TEST_CASE("Run with BMP image") {
    Reader reader("../tasks/image_processor/Tests/Images/Test_Image.BMP");
    BMPFile bmp_file;
    reader.ReadToBMP(bmp_file);

    Writer writer("../tasks/image_processor/Tests/Images/Test_Image_Written.BMP");
    writer.WriteToFile(bmp_file);

    REQUIRE(FileComprassion("../tasks/image_processor/Tests/Images/Test_Image.BMP",
                            "../tasks/image_processor/Tests/Images/Test_Image_Written.BMP"));
}
