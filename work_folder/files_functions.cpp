#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <filesystem>


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

namespace fs = std::filesystem;

bool validate_file_path(const std::string& path) {
    try {
        fs::path filePath(path);
        
        if (filePath.empty() || !filePath.has_filename()) {
            return false;
        }

        if (!fs::exists(filePath)) {
            return false;
        }

        if (!fs::is_regular_file(filePath)) {
            return false;
        }

        std::ifstream file(filePath);
        if (!file.is_open()) {
            return false;
        }
        
        return true;
    } 
    catch (const fs::filesystem_error&) {
        return false;
    }
}