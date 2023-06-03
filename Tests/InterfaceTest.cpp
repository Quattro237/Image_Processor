#include <catch.hpp>
#include <vector>

#include "Parser.h"
#include "Interface.h"
#include "TestImage.h"

TEST_CASE("Run with valid filters and valid args") {
    const size_t args_count = 11;
    std::vector<const char*> args;
    args.push_back("./image_processor.cpp\0");
    args.push_back("../input_files/./lenna.bmp\0");
    args.push_back("../output_files/lenna_filtered.bmp\0");
    args.push_back("-crop\0");
    args.push_back("800\0");
    args.push_back("600\0");
    args.push_back("-gs\0");
    args.push_back("-neg\0");
    args.push_back("-sharp\0");
    args.push_back("-blur\0");
    args.push_back("7.5\0");

    char** argv = new char*[args_count];

    for (size_t i = 0; i < args_count; ++i) {
        argv[i] = new char[std::strlen(args[i])];
        std::strncpy(argv[i], args[i], std::strlen(args[i]));
    }

    int argc = args_count;

    Parser data(argc, argv);
    data.ParseArgs();

    Interface interface;
    std::vector<std::unique_ptr<Filter>> filters = interface.CreateFilters(data.Getfilters());

    const PixelTable pixels = {{{0.5, 0.3, 0.1}, {0.1, 1.0, 0.05}, {0.4, 0.0, 1.0}},
                               {{0.44, 0.22, 0.6}, {0.9, 0.4, 0.33}, {0.9, 0.8, 0.4}},
                               {{0.23, 0.9, 0.67}, {0.0, 1.0, 0.39}, {0.21, 0.65, 0.33}}};

    TestImage image(pixels);

    interface.ApplyFilters(image, filters);

    const PixelTable final_pixels = {{{0.685, 0.685, 0.685}, {0.705, 0.705, 0.705}, {0.725, 0.725, 0.725}},
                                     {{0.658, 0.658, 0.658}, {0.681, 0.681, 0.681}, {0.704, 0.704, 0.704}},
                                     {{0.632, 0.632, 0.632}, {0.657, 0.657, 0.657}, {0.683, 0.683, 0.683}}};

    REQUIRE(image.CheckPixelTable(final_pixels));
}

TEST_CASE("Run with valid filters, but invalid args") {
    const size_t args_count = 7;
    std::vector<const char*> args;
    args.push_back("./image_processor.cpp\0");
    args.push_back("../input_files/./lenna.bmp\0");
    args.push_back("../output_files/lenna_filtered.bmp\0");
    args.push_back("-crop\0");
    args.push_back("600\0");
    args.push_back("-gs\0");
    args.push_back("22\0");

    char** argv = new char*[args_count];

    for (size_t i = 0; i < args_count; ++i) {
        argv[i] = new char[std::strlen(args[i])];
        std::strncpy(argv[i], args[i], std::strlen(args[i]));
    }

    int argc = args_count;

    Parser data(argc, argv);
    data.ParseArgs();

    Interface interface;
    REQUIRE_THROWS_AS(interface.CreateFilters(data.Getfilters()), Interface::InvalidFilterArgumentsException);
}

TEST_CASE("Run invalid filters") {
    const size_t args_count = 4;
    std::vector<const char*> args;
    args.push_back("./image_processor.cpp\0");
    args.push_back("../input_files/./lenna.bmp\0");
    args.push_back("../output_files/lenna_filtered.bmp\0");
    args.push_back("-kek\0");
    args.push_back("0.2\0");

    char** argv = new char*[args_count];

    for (size_t i = 0; i < args_count; ++i) {
        argv[i] = new char[std::strlen(args[i])];
        std::strncpy(argv[i], args[i], std::strlen(args[i]));
    }

    int argc = args_count;

    Parser data(argc, argv);
    data.ParseArgs();

    Interface interface;
    REQUIRE_THROWS_AS(interface.CreateFilters(data.Getfilters()), Interface::InvalidFilterException);
}
