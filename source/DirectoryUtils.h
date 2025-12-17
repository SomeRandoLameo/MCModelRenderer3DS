//
// Created by elias on 17.12.25.
//

#ifndef MC_MODEL_RENDERER_DIRECTORYUTILS_H
#define MC_MODEL_RENDERER_DIRECTORYUTILS_H


#include <string>
#include <vector>

class DirectoryUtils {
public:
    static std::vector<std::string> ListDirectories(const std::string& path);
    static bool FileExists(const std::string& path);
};


#endif //MC_MODEL_RENDERER_DIRECTORYUTILS_H
