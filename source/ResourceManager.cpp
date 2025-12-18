#include <format>
#include <fstream>
#include "ResourceManager.h"
#include "DirectoryUtils.h"

bool ResourceManager::CheckRootAssets() {
    //TODO: If there are multiple resource packs with .mcassetsroot, we need a list and selection logic based on version

    if (m_rootAssetsChecked) return !m_rootAssetsPath.empty();

    auto directories = DirectoryUtils::ListDirectories(m_rootPackPath);

    for (const auto& dir : directories) {
        std::string packMeta      = m_rootPackPath + dir + "/assets/pack.mcmeta";
        std::string packIcon      = m_rootPackPath + dir + "/assets/icons/icon_32x32.png";

        bool packMetaExists  = DirectoryUtils::FileExists(packMeta);
        bool packIconExists  = DirectoryUtils::FileExists(packIcon);

        if ( packMetaExists && packIconExists ) {
            m_rootAssetsPath = m_rootPackPath + dir;
            m_rootAssetsChecked = true;
            return true;
        }
    }

    m_rootAssetsChecked = true;
    return false;
}

ResourcePack ResourceManager::GetRootResourcePack() {
    return GetResourcePack(m_rootAssetsPath);
}

ResourcePack ResourceManager::GetResourcePack(const std::string &resourcePackPath) {

    if( resourcePackPath == m_rootAssetsPath ){
        std::ifstream f(resourcePackPath);
        nlohmann::json packMeta = nlohmann::json::parse(f);
        return ResourcePack(true, nlohmann::json(), "", resourcePackPath);
    } else{
        std::ifstream f(resourcePackPath + "/assets/pack.mcmeta");
        nlohmann::json packMeta = nlohmann::json::parse(f);
        return ResourcePack(false, packMeta, resourcePackPath + "/assets/icons/icon_32x32.png", resourcePackPath);
    }
}

