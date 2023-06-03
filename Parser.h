#pragma once

#include <string_view>
#include <vector>

class Parser {
public:
    class InvalidArgumentsException : std::exception {};

public:
    struct Filter {
        std::string_view filter_name;
        std::vector<std::string_view> filter_args;
    };

    struct Args {
        std::string_view input_dir;
        std::string_view output_dir;
        std::vector<Filter> filters;
    };

public:
    Parser(int argc, char** argv);

    void ParseArgs();
    std::string_view GetInputDir() const;
    std::string_view GetOutputDir() const;
    std::vector<Filter> Getfilters() const;
    bool IsEmpty() const;

public:
    static constexpr std::string_view INSTRUCTIONS =
        "Image Processor\n"
        "Utility for image manipulations\n"
        "\n"
        "Usage:\n"
        "/build/image_processor input_file output_file -{filter_one} [param 1] [param 2] ... -{filter_two} ...\n"
        "\n"
        "Filters:\n"
        "Crop {-crop} [width, height]\n"
        "Grayscale {-gs} []\n"
        "Negative {-neg} []\n"
        "Sharpening {-sharp} []\n"
        "Edge Detection {-edge} [threshold]\n"
        "Gaussian Blur {-blur} [sigma]\n"
        "Twirl {-twirl} [angle]";

private:
    int argc_;
    char** argv_;
    Args args_;
    bool is_empty_ = true;
};
