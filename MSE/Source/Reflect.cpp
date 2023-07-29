//
// Created by MisThe on 2023/6/4.
//

#include "Reflect.h"

std::unordered_map<std::string, std::function<CustomPtr*()>> Reflect::S_instances;

CustomPtr *Reflect::S_Instance(const std::string& type) {
    if (S_instances.find(type) == S_instances.end())
        return nullptr;
    return S_instances[type]();
}

bool Reflect::S_Register(const std::string& type, std::function<CustomPtr*()> func) {
    if (S_instances.find(type) != S_instances.end())
        return false;
    S_instances.insert(std::pair<std::string, std::function<CustomPtr*()>>(type,func));
    return true;
}

void Reflect::S_Instance(const std::string &type, CustomPtr *&ptr) {
    if (S_instances.find(type) == S_instances.end())
        ptr = nullptr;
    ptr = S_instances[type]();
}
