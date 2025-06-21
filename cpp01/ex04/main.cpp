#include <iostream>
#include <fstream>
#include <string>

void replaceInFile(const std::string& filename, const std::string& s1, const std::string& s2) {
    std::ifstream input(filename.c_str());
    if (!input) {
        std::cerr << "Error: could not open input file" << std::endl;
        return;
    }

    std::ofstream output((filename + ".replace").c_str());
    if (!output) {
        std::cerr << "Error: could not create output file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        std::string newline;
        size_t pos = 0;
        while (pos < line.length()) {
            size_t found = line.find(s1, pos);
            if (found == std::string::npos) {
                newline += line.substr(pos);
                break;
            }
            newline += line.substr(pos, found - pos);
            newline += s2;
            pos = found + s1.length();
        }
        output << newline << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }
    if (std::string(argv[2]).empty()) {
        std::cerr << "Error: s1 must not be empty" << std::endl;
        return 1;
    }

    replaceInFile(argv[1], argv[2], argv[3]);
    return 0;
}