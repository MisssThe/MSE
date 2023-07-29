//
// Created by MisThe on 2023/7/28.
//

#include "../Include/General/Container/Map.h"


REGISTER(Map)

bool Map::Iterator(const std::function<void(CustomPtr *)> &call) const{
    for (auto m: this->map) {
        call(m.first);
        call(m.second);
    }
    return true;
}

void Map::MarkSelf()  {
    this->Iterator([](CustomPtr *ptr) -> void {
        if (ptr == nullptr)
            return;
        ptr->Mark();
    });
}

void Map::ReadPtr(cereal::BinaryInputArchive &archive) {
    int size;
    archive(size);
    for (int index = 0; index < size; ++index) {
        std::string keyType, valueType;
        archive(keyType, valueType);
        CustomPtr *keyPtr = Reflect::S_Instance(keyType);
        CustomPtr *valuePtr = Reflect::S_Instance(valueType);
        this->Add(keyPtr, valuePtr);
    }
    this->Iterator([&archive](CustomPtr *key, CustomPtr *value) -> void {
        key->serialize(archive);
        if (value != nullptr)
            value->serialize(archive);
    });
}

void Map::WritePtr(cereal::BinaryOutputArchive &archive) {
    archive(this->Size());
    this->Iterator([&archive](CustomPtr *ptr) -> void {
        std::string type;
        if (ptr != nullptr)
            type = ptr->Type();
        archive(type);
    });
    this->Iterator([&archive](CustomPtr *ptr) -> void {
        if (ptr == nullptr)
            return;
        ptr->serialize(archive);
    });
}

void Map::Add(CustomPtr *key, CustomPtr *value) {
    this->map.insert(std::pair<CustomPtr *, CustomPtr *>(key, value));
}

CustomPtr *Map::Get(CustomPtr *key)  {
    if (this->map.find(key) == this->map.end())
        return nullptr;
    return this->map[key];
}

unsigned int Map::Size() {
    return this->map.size();
}

void Map::Remove(CustomPtr *key) {
    this->map.erase(key);
}

void Map::Iterator(const std::function<void(CustomPtr *, CustomPtr *)> &call) const {
    for (auto m: this->map) {
        call(m.first, m.second);
    }
}

void Map::Clear() {
    this->map.clear();
}