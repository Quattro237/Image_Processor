#include <fstream>
#include <string>

bool FileComprassion(std::string path_1, std::string path_2) {
    std::ifstream file_1(path_1);
    std::ifstream file_2(path_2);

    while (!(file_1.eof() || file_2.eof())) {
        uint8_t bit_1 = 0;
        uint8_t bit_2 = 0;

        file_1.read(reinterpret_cast<char*>(&bit_1), 1);
        file_2.read(reinterpret_cast<char*>(&bit_2), 1);

        if (bit_1 != bit_2) {
            return false;
        }
    }

    if (file_1.eof() && file_2.eof()) {
        return true;
    }

    return false;
}
