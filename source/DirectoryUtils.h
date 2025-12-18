#pragma once

#include <string>
#include <vector>

class DirectoryUtils {
public:
    static std::vector<std::string> ListDirectories(const std::string& path);
    static bool FileExists(const std::string& path);
};