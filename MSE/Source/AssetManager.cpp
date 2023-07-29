//
// Created by MisThe on 2023/7/28.
//

#include "../Include/Core/Asset/AssetManager.h"

#include "../Include/General/Tool/IO.h"

REGISTER(AssetManager)

AssetManager::AssetManager() {
    this->assetMap = new Map();
}

void AssetManager::Clear() {
    this->assetMap->Iterator([this](CustomPtr* path, CustomPtr* asset) {
        this->Update(dynamic_cast<Asset *>(asset));
    });
    this->assetMap->Clear();
}

void AssetManager::Invoke() {
    //更新Cache数据
}

void AssetManager::Update(Asset *asset) {
    Debug::Info("Asset", {"Update Asset [", asset->path, "]"});
    std::ofstream os(asset->path);
    if (os.is_open()) {
        cereal::BinaryOutputArchive archive(os);
        archive(*asset);
    }
    os.close();
}

void AssetManager::Remove(const std::string& path) {
    auto* cv = new CustomVal(path);
    Asset* asset = dynamic_cast<Asset *>(AssetManager::assetMap->Get(cv));
    if (asset == nullptr)
        return;
    this->assetMap->Remove(cv);
    this->Update(asset);
}

void AssetManager::Remove(Asset *asset) {
    if (asset == nullptr)
        return;
    this->Remove(asset->path);
}

AssetManager::~AssetManager() {
    this->Clear();
}

//void AssetManager::RefreshCache(const std::string_view& directory) {
//    if (this->assetMap == nullptr)
//        return;
//    Queue<std::string_view> *paths = IO::ChildrenFiles(directory);
//    paths->IteratorWithout([this](std::string_view path) {
//        //根据path生成cache
//        std::string_view extension = IO::PathToExtension(path);
//        std::string type(Static::S_SettingManager()->GetAssetSetting()->assetCacheMap->Get(extension));
//        if (type.empty())
//            return;
//        std::string_view cache = path;
//        String::ReplaceAll(cache, "/", "_");
//        String::ReplaceAll(cache, extension, type);
//        cache = String::Combine({"Canvas/Caches/", type, "/", std::string(cache)});
//        if (IO::Exist(cache))
//            return;
//        Asset *ptr = dynamic_cast<Asset *>(Reflect::S_Instance(type));
//        ptr->path = cache;
//        ptr->Cache(path);
//        this->assetMap->Insert(cache, ptr);
//        Debug::Info("Asset Manager", {"Create New Cache [", path, "]"});
//    });
//}

void AssetManager::SetInfo(Asset *asset, const std::string& path) {
    asset->name = path;
    IO::PathToName(asset->name);
    asset->path = path;
    this->assetMap->Add(new CustomVal(path), asset);
}
