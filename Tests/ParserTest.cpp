#include <catch.hpp>
#include <cstring>

#include "../Parser.h"

TEST_CASE("Run without parametrs") {
    const char* program_location = "./image_processor.cpp\0";

    char** argv = new char*[1];
    argv[0] = new char[std::strlen(program_location)];
    std::strncpy(argv[0], program_location, std::strlen(program_location));

    int argc = 1;

    Parser data(argc, argv);

    REQUIRE(data.IsEmpty());
}

TEST_CASE("Run without filters") {
    const char* program_location = "./image_processor.cpp\0";
    const char* input_dir = "../input_files/./lenna.bmp\0";
    const char* output_dir = "../output_files/lenna_filtered.bmp\0";

    char** argv = new char*[3];
    argv[0] = new char[std::strlen(program_location)];
    std::strncpy(argv[0], program_location, std::strlen(program_location));
    argv[1] = new char[std::strlen(input_dir)];
    std::strncpy(argv[1], input_dir, std::strlen(input_dir));
    argv[2] = new char[std::strlen(output_dir)];
    std::strncpy(argv[2], output_dir, std::strlen(output_dir));

    int argc = 3;

    Parser data(argc, argv);
    data.ParseArgs();

    REQUIRE(data.GetInputDir() == input_dir);
    REQUIRE(data.GetOutputDir() == output_dir);
    REQUIRE(data.Getfilters().empty());
}

TEST_CASE("Run with filters") {
    const char* program_location = "./image_processor.cpp\0";
    const char* input_dir = "../input_files/./lenna.bmp\0";
    const char* output_dir = "../output_files/lenna_filtered.bmp\0";
    const char* filter_1 = "-blur\0";
    const char* filter_1_arg = "7.5\0";
    const char* filter_2 = "-sharp\0";

    const size_t args_count = 6;

    char** argv = new char*[args_count];
    argv[0] = new char[std::strlen(program_location)];
    std::strncpy(argv[0], program_location, std::strlen(program_location));
    argv[1] = new char[std::strlen(input_dir)];
    std::strncpy(argv[1], input_dir, std::strlen(input_dir));
    argv[2] = new char[std::strlen(output_dir)];
    std::strncpy(argv[2], output_dir, std::strlen(output_dir));
    argv[3] = new char[std::strlen(filter_1)];
    std::strncpy(argv[3], filter_1, std::strlen(filter_1));
    argv[4] = new char[std::strlen(filter_1_arg)];
    std::strncpy(argv[4], filter_1_arg, std::strlen(filter_1_arg));
    argv[args_count - 1] = new char[std::strlen(filter_2)];
    std::strncpy(argv[args_count - 1], filter_2, std::strlen(filter_2));

    int argc = args_count;

    Parser data(argc, argv);
    data.ParseArgs();

    REQUIRE(data.GetInputDir() == input_dir);
    REQUIRE(data.GetOutputDir() == output_dir);

    std::vector<Parser::Filter> filters = data.Getfilters();

    REQUIRE(filters.size() == 2);
    REQUIRE(filters[0].filter_args.size() == 1);
    REQUIRE(filters[1].filter_args.empty());
    REQUIRE(filters[0].filter_name == filter_1);
    REQUIRE(filters[0].filter_args[0] == filter_1_arg);
    REQUIRE(filters[1].filter_name == filter_2);
}

TEST_CASE("Run with invalid arguments amount") {
    const char* program_location = "./image_processor.cpp\0";
    const char* input_dir = "../input_files/./lenna.bmp\0";

    char** argv = new char*[2];
    argv[0] = new char[std::strlen(program_location)];
    std::strncpy(argv[0], program_location, std::strlen(program_location));
    argv[1] = new char[std::strlen(input_dir)];
    std::strncpy(argv[1], input_dir, std::strlen(input_dir));

    int argc = 2;

    Parser data(argc, argv);
    REQUIRE_THROWS_AS(data.ParseArgs(), Parser::InvalidArgumentsException);
}