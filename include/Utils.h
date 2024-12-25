#pragma once
#include <string>
#include <vector>

namespace Utils {
    std::string urlDecode(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delim);
    std::string getMimeType(const std::string& path);
    bool fileExists(const std::string& path);
} 