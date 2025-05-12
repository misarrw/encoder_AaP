#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

std::string file_to_string(const std::string& file_path) {
    std::ifstream file(file_path);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + file_path);
    }
    
    // More efficient way to read whole file
    return std::string((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
}


void string_to_file(const std::string& file_path, std::string& data) {
    std::ofstream file(file_path);
    file << data;
    file.close();
}