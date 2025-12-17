#pragma once

#include <string>
#include "../vendor/json/json.hpp"

struct ResourcePack {
    bool isRootPack;

    nlohmann::json packMCMeta; /** Guide: https://minecraft.wiki/w/Pack_format */
    std::string packIcon;
    std::string packPath;
};

class ResourceManager {
private:
    std::string m_basePath = "romfs:/resourcepacks/";

    bool m_rootAssetsChecked = false;
    std::string m_rootAssetsPath;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    bool CheckRootAssets();
    void ResetRootAssetCheck() {
        m_rootAssetsChecked = false;
        m_rootAssetsPath = "";
    }

    ResourcePack GetResourcePack(const std::string& resourcePackPath);

    std::string GetRootAssetsPath() const { return m_rootAssetsPath; }

    ResourcePack GetRootResourcePack();

//DEBUGGING PURPOSES ONLY
    std::string s1 = "";
    std::string s2 = "";
    std::string s3 = "";
    std::string s4 = "";
};
