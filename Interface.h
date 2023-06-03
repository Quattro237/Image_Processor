#pragma once

#include "BMPFile.h"
#include "Filters/Filter.h"
#include "Parser.h"

#include <memory>
#include <string>

class Interface {
public:
    class InvalidFilterArgumentsException : std::exception {
    public:
        explicit InvalidFilterArgumentsException(const std::string& message);

        const char* what() const noexcept override;

    private:
        const std::string message_;
    };
    class InvalidFilterException : std::exception {
    public:
        explicit InvalidFilterException(const std::string& message);

        const char* what() const noexcept override;

    private:
        const std::string message_;
    };

public:
    static std::vector<std::unique_ptr<Filter>> CreateFilters(std::vector<Parser::Filter> unparsed_filter);
    static void ApplyFilters(Image& image, std::vector<std::unique_ptr<Filter>>& filters);

private:
    static std::string MakeErrorMessage(size_t given_count, size_t expected_count, std::string_view filter_name);
};
