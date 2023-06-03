#include "BMPFile.h"
#include "Interface.h"
#include "IO/Reader.h"
#include "IO/Writer.h"
#include "Parser.h"

#include <iostream>

int main(int argc, char** argv) {
    Parser data(argc, argv);

    try {
        data.ParseArgs();
    } catch (Parser::InvalidArgumentsException) {
        std::cout << "Invalid arguments amount (one given, two or more expected)" << std::endl;
        return 1;
    }

    if (data.IsEmpty()) {
        std::cout << Parser::INSTRUCTIONS << std::endl;
        return 0;
    }

    Reader reader(data.GetInputDir());
    BMPFile bmp_file;
    try {
        reader.ReadToBMP(bmp_file);
    } catch (Reader::InvalidFileException) {
        std::cout << "Can't open input file to read" << std::endl;
        return 1;
    } catch (Reader::InvalidFileFormatException) {
        std::cout << "Invalid input file format" << std::endl;
        return 1;
    }

    Interface interface;
    std::vector<std::unique_ptr<Filter>> filters;
    try {
        filters = interface.CreateFilters(data.Getfilters());
    } catch (const Interface::InvalidFilterArgumentsException& error) {
        std::cout << error.what() << std::endl;
        return 1;
    } catch (const Interface::InvalidFilterException& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }

    try {
        interface.ApplyFilters(bmp_file, filters);
    } catch (std::exception) {
        std::cout << "Unable to apply filter" << std::endl;
        return 1;
    }

    Writer writer(data.GetOutputDir());
    try {
        writer.WriteToFile(bmp_file);
    } catch (Writer::InvalidFileException) {
        std::cout << "Can't open output file to write" << std::endl;
        return 1;
    }

    return 0;
}
