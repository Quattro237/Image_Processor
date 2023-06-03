#include <catch.hpp>
#include <string>

#include "BitwiseFileComprassion.h"
#include "IO/Writer.h"
#include "IO/Reader.h"
#include "Image.h"
#include "BMPFile.h"
#include "../Filters/CropFilter.h"
#include "../Filters/GrayscaleFilter.h"
#include "../Filters/NegativeFilter.h"
#include "../Filters/GaussianBlurFilter.h"
#include "../Filters/EdgeDetectionFilter.h"
#include "../Filters/SharpeningFilter.h"
#include "../Filters/TwirlFilter.h"

const std::string INPUT_PATH = "../tasks/image_processor/Tests/Images/Test_Image.BMP";
const std::string OUTPUT_PATH = "../tasks/image_processor/Tests/Images/Test_Image_Written.BMP";

namespace {
BMPFile CreateBMPImage() {
    Reader reader(INPUT_PATH);
    BMPFile bmp_file;
    reader.ReadToBMP(bmp_file);
    return bmp_file;
}

void WriteBMPToFile(BMPFile& file) {
    Writer writer(OUTPUT_PATH);
    writer.WriteToFile(file);
}
}  // namespace

TEST_CASE("Crop test") {
    BMPFile image = CreateBMPImage();
    const size_t new_width = 300;
    const size_t new_height = 400;
    CropFilter crop(new_width, new_height);
    crop.ApplyFilter(image);
    WriteBMPToFile(image);
    REQUIRE(FileComprassion(OUTPUT_PATH, "../tasks/image_processor/Tests/Images/Test_Image_Crop_300x400.BMP"));
}

TEST_CASE("Grayscale test") {
    BMPFile image = CreateBMPImage();
    GrayscaleFilter gs;
    gs.ApplyFilter(image);
    WriteBMPToFile(image);
    REQUIRE(FileComprassion(OUTPUT_PATH, "../tasks/image_processor/Tests/Images/Test_Image_Grayscale.BMP"));
}

TEST_CASE("Negative test") {
    BMPFile image = CreateBMPImage();
    NegativeFilter neg;
    neg.ApplyFilter(image);
    WriteBMPToFile(image);
    REQUIRE(FileComprassion(OUTPUT_PATH, "../tasks/image_processor/Tests/Images/Test_Image_Negative.BMP"));
}

TEST_CASE("GaussianBlur test") {
    BMPFile image = CreateBMPImage();
    const double sigma = 3.5;
    GaussianBlurFilter blur(sigma);
    blur.ApplyFilter(image);
    WriteBMPToFile(image);
    REQUIRE(FileComprassion(OUTPUT_PATH, "../tasks/image_processor/Tests/Images/Test_Image_GaussianBlur.BMP"));
}

TEST_CASE("EdgeDetection test") {
    BMPFile image = CreateBMPImage();
    const double threshold = 0.1;
    EdgeDetectionFilter blur(threshold);
    blur.ApplyFilter(image);
    WriteBMPToFile(image);
    REQUIRE(FileComprassion(OUTPUT_PATH, "../tasks/image_processor/Tests/Images/Test_Image_EdgeDetection.BMP"));
}

TEST_CASE("Sharpening test") {
    BMPFile image = CreateBMPImage();
    SharpeningFilter sharp;
    sharp.ApplyFilter(image);
    WriteBMPToFile(image);
    REQUIRE(FileComprassion(OUTPUT_PATH, "../tasks/image_processor/Tests/Images/Test_Image_Sharpening.BMP"));
}

TEST_CASE("Twirl test") {
    BMPFile image = CreateBMPImage();
    const double angle = 240.0;
    TwirlFilter twirl(angle);
    twirl.ApplyFilter(image);
    WriteBMPToFile(image);
    REQUIRE(FileComprassion(OUTPUT_PATH, "../tasks/image_processor/Tests/Images/Test_Image_Twirl.BMP"));
}
