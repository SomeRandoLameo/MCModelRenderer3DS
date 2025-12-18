#include <filesystem>
#include <fstream>
#include "DirectoryUtils.h"

// this is a very basic fs wrapper

std::vector<std::string> DirectoryUtils::ListDirectories(const std::string &path) {
    std::vector<std::string> directories;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_directory()) {
                directories.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        // TODO: Handle error in some form
    }

    return directories;
}

bool DirectoryUtils::FileExists(const std::string &path) {
    return std::filesystem::exists(path);
}
