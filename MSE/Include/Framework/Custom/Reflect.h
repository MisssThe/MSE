//
// Created by MisThe on 2023/6/4.
// 只创建指针不记录指针，不参与垃圾回收
//

#ifndef CANVAS_1_0_REFLECT_H
#define CANVAS_1_0_REFLECT_H

#include "string"

class CustomPtr;

class Reflect final
{
public:
    static CustomPtr* S_Instance(const std::string& type);
    static void S_Instance(const std::string& type, CustomPtr* &ptr);
    static bool S_Register(const std::string& type, std::function<CustomPtr*()> func);
private:
    static std::unordered_map<std::string, std::function<CustomPtr*()>> S_instances;
private:
    Reflect() = default;
};

#endif //CANVAS_1_0_REFLECT_H
