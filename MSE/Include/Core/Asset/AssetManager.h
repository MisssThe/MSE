//
// Created by MisThe on 2023/7/28.
//

#ifndef MSE_ASSETMANAGER_H
#define MSE_ASSETMANAGER_H

#include <fstream>
#include "CustomPtr.h"
#include "../../General/Container/Map.h"
#include "../../General/Tool/Debug.h"
#include "Asset.h"
#include "CustomVal.h"


class AssetManager : public CustomPtr {
CUSTOM_PTR(PTR)      //将所有继承自Ptr数据存放到此处
CUSTOM_VAL(VAL)      //需要序列化基础数据类型时填充到此处
public:
    AssetManager();
protected:
    ~AssetManager() override;
private:
    Map *assetMap = nullptr;
//    void RefreshCache(const std::string_view& directory = "Canvas/Assets");
public:
    template<class T> T *Create(const std::string& path) {
        T *temp = this->Instance<T>(path);
        if (temp != nullptr) {
            Debug::Warn("Asset Create", {"The Asset Existed [", path, "]"});
            return temp;
        }
        temp = new T();
        this->SetInfo(temp, path);
        return temp;
    }
    template<class T> T *Instance(const std::string& path) {
        auto* cv = new CustomVal(path);
        T *temp = dynamic_cast<T *>(this->assetMap->Get(cv));
        if (temp != nullptr)
            return temp;
        std::ifstream is(path);
        try {
            if (is.is_open()) {
                cereal::BinaryInputArchive archive(is);
                temp = new T();
                archive(*temp);
            }
        } catch (...) {
            Debug::Warn("Asset Instance", {"The Asset Format Does Not Match [", path, "]"});
            return nullptr;
        }
        is.close();
        if (temp == nullptr)
            return temp;
        this->SetInfo(temp, path);
        return temp;
    }
    void Invoke();
    void Clear();
    void Remove(const std::string& path);
    void Remove(Asset *asset);
private:
    void Update(Asset *asset);
    void SetInfo(Asset *asset, const std::string& path);
};


#endif //MSE_ASSETMANAGER_H
