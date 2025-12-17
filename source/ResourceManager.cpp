#include <format>
#include "ResourceManager.h"
#include "DirectoryUtils.h"

bool ResourceManager::CheckRootAssets() {
    //TODO: If there are multiple resource packs with .mcassetsroot, we need a list and selection logic based on version

    if (m_rootAssetsChecked) return !m_rootAssetsPath.empty();

    auto directories = DirectoryUtils::ListDirectories(m_basePath);

    for (const auto& dir : directories) {
        std::string assetRootFile = m_basePath + dir + "/.mcassetsroot";  //TODO: Why the hell won std::filesystem::exists detect dotfiles??
        std::string packMeta      = m_basePath + dir + "/pack.mcmeta";
        std::string packIcon      = m_basePath + dir + "/pack.png";

        bool assetRootExists = DirectoryUtils::FileExists(assetRootFile);
        //TODO: Why the hell wont  std::filesystem::exists detect dotfiles??
        assetRootExists ? s1 = "true" : s1 = std::format("false {}", assetRootFile);

        bool packMetaExists  = DirectoryUtils::FileExists(packMeta);
        packMetaExists ? s2 = "true" : s2 = "false";

        bool packIconExists  = DirectoryUtils::FileExists(packIcon);
        packIconExists ? s3 = "true" : s3 = "false";

        if ( assetRootExists && packMetaExists && packIconExists ) {

            m_rootAssetsPath = m_basePath + dir;

            s4 = m_rootAssetsPath;
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
    bool isRootPack = false;
    if( resourcePackPath == m_rootAssetsPath ) isRootPack = true;

    return ResourcePack(isRootPack, nlohmann::json(), "", resourcePackPath);
}

