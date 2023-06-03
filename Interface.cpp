#include "Interface.h"
#include "./Filters/GrayscaleFilter.h"
#include "./Filters/NegativeFilter.h"
#include "./Filters/SharpeningFilter.h"
#include "./Filters/EdgeDetectionFilter.h"
#include "./Filters/CropFilter.h"
#include "./Filters/GaussianBlurFilter.h"
#include "./Filters/TwirlFilter.h"

#include <stdexcept>
#include <string>

Interface::InvalidFilterArgumentsException::InvalidFilterArgumentsException(const std::string& message)
    : message_(std::move(message)){};

const char* Interface::InvalidFilterArgumentsException::what() const noexcept {
    return message_.c_str();
}

Interface::InvalidFilterException::InvalidFilterException(const std::string& message) : message_(std::move(message)){};

const char* Interface::InvalidFilterException::what() const noexcept {
    return message_.c_str();
}

std::string Interface::MakeErrorMessage(size_t given_count, size_t expected_count, std::string_view filter_name) {
    std::string message = "Unexpected arguments for filter ";
    message += filter_name;
    message += " : given " + std::to_string(given_count) + ", expected " + std::to_string(expected_count);
    return message;
}

std::vector<std::unique_ptr<Filter>> Interface::CreateFilters(std::vector<Parser::Filter> unparsed_filter) {
    std::vector<std::unique_ptr<Filter>> filters;
    filters.reserve(unparsed_filter.size());

    for (size_t i = 0; i < unparsed_filter.size(); ++i) {
        std::string_view filter_name = unparsed_filter[i].filter_name;
        if (filter_name == "-crop") {
            if (unparsed_filter[i].filter_args.size() != 2) {
                std::string message = MakeErrorMessage(unparsed_filter[i].filter_args.size(), 2, filter_name);
                throw InvalidFilterArgumentsException(message);
            }
            filters.push_back(
                std::make_unique<CropFilter>(CropFilter(std::stoi(std::string(unparsed_filter[i].filter_args[0])),
                                                        std::stoi(std::string(unparsed_filter[i].filter_args[1])))));
        } else if (filter_name == "-gs") {
            if (!unparsed_filter[i].filter_args.empty()) {
                std::string message = MakeErrorMessage(unparsed_filter[i].filter_args.size(), 0, filter_name);
                throw InvalidFilterArgumentsException(message);
            }
            filters.push_back(std::make_unique<GrayscaleFilter>(GrayscaleFilter()));
        } else if (filter_name == "-neg") {
            if (!unparsed_filter[i].filter_args.empty()) {
                std::string message = MakeErrorMessage(unparsed_filter[i].filter_args.size(), 0, filter_name);
                throw InvalidFilterArgumentsException(message);
            }
            filters.push_back(std::make_unique<NegativeFilter>(NegativeFilter()));
        } else if (filter_name == "-sharp") {
            if (!unparsed_filter[i].filter_args.empty()) {
                std::string message = MakeErrorMessage(unparsed_filter[i].filter_args.size(), 0, filter_name);
                throw InvalidFilterArgumentsException(message);
            }
            filters.push_back(std::make_unique<SharpeningFilter>(SharpeningFilter()));
        } else if (filter_name == "-edge") {
            if (unparsed_filter[i].filter_args.size() != 1) {
                std::string message = MakeErrorMessage(unparsed_filter[i].filter_args.size(), 1, filter_name);
                throw InvalidFilterArgumentsException(message);
            }
            filters.push_back(std::make_unique<EdgeDetectionFilter>(
                EdgeDetectionFilter(std::stod(std::string(unparsed_filter[i].filter_args[0])))));
        } else if (filter_name == "-blur") {
            if (unparsed_filter[i].filter_args.size() != 1) {
                std::string message = MakeErrorMessage(unparsed_filter[i].filter_args.size(), 1, filter_name);
                throw InvalidFilterArgumentsException(message);
            }
            filters.push_back(std::make_unique<GaussianBlurFilter>(
                GaussianBlurFilter(std::stod(std::string(unparsed_filter[i].filter_args[0])))));
        } else if (filter_name == "-twirl") {
            if (unparsed_filter[i].filter_args.size() != 1) {
                std::string message = MakeErrorMessage(unparsed_filter[i].filter_args.size(), 1, filter_name);
                throw InvalidFilterArgumentsException(message);
            }
            filters.push_back(
                std::make_unique<TwirlFilter>(TwirlFilter(std::stod(std::string(unparsed_filter[i].filter_args[0])))));
        } else {
            std::string message = "Unknown filter ";
            message += filter_name;
            throw InvalidFilterException(message);
        }
    }

    return filters;
}

void Interface::ApplyFilters(Image& image, std::vector<std::unique_ptr<Filter>>& filters) {
    for (const std::unique_ptr<Filter>& filter : filters) {
        filter->ApplyFilter(image);
    }
}