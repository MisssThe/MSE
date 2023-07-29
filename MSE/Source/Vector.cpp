//
// Created by MisThe on 2023/7/29.
//

#include "../Include/General/Container/Vector.h"
#include "Reflect.h"

REGISTER(Vector)

bool Vector::Iterator(const std::function<void(CustomPtr *)> &call) const {
    for (auto v : this->vec) {
        call(v);
    }
    return true;
}

void Vector::MarkSelf() {
    this->Iterator([](CustomPtr* ptr) {
        if (ptr == nullptr)
            return;
        ptr->Mark();
    });
    CustomPtr::MarkSelf();
}

void Vector::ReadPtr(cereal::BinaryInputArchive &archive) {
    int size;
    archive(size);
    for (int index = 0; index < size; ++index) {
        std::string type;
        archive(type);
        CustomPtr *ptr = Reflect::S_Instance(type);
        this->Add(ptr);
    }
    this->Iterator([&archive](CustomPtr *ptr) -> void {
        if (ptr != nullptr)
            ptr->serialize(archive);
    });
}

void Vector::WritePtr(cereal::BinaryOutputArchive &archive) {
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

void Vector::Add(CustomPtr *ptr) {
    this->vec.push_back(ptr);
}

CustomPtr *Vector::Get(unsigned int index) {
    if (index >= this->vec.size())
        return nullptr;
    return this->vec[index];
}

unsigned int Vector::Size() {
    return this->vec.size();
}
