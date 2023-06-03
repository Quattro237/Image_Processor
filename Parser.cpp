#include "Parser.h"

Parser::Parser(int argc, char** argv) : argc_(argc), argv_(argv){};

void Parser::ParseArgs() {
    if (argc_ > 2) {
        is_empty_ = false;

        args_.input_dir = argv_[1];
        args_.output_dir = argv_[2];

        for (size_t i = 3; i < argc_;) {
            std::string_view filter = argv_[i];
            ++i;
            args_.filters.push_back({filter, {}});
            auto iter = args_.filters.rbegin();
            while (i < argc_ && argv_[i][0] != '-') {
                iter->filter_args.push_back(argv_[i]);
                ++i;
            }
        }
    } else if (argc_ == 2) {
        throw InvalidArgumentsException();
    }
}

std::string_view Parser::GetInputDir() const {
    return args_.input_dir;
}

std::string_view Parser::GetOutputDir() const {
    return args_.output_dir;
}

std::vector<Parser::Filter> Parser::Getfilters() const {
    return args_.filters;
}

bool Parser::IsEmpty() const {
    return is_empty_;
}
