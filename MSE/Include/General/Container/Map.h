//
// Created by MisThe on 2023/7/26.
//

#ifndef MSE_MAP_H
#define MSE_MAP_H

#include "CustomPtr.h"
#include "unordered_map"

struct PtrHash {
    size_t operator() (const CustomPtr* ptr) const
    {
        return ptr->Hash();
    }
};

struct PtrEqual {
    bool operator() (const CustomPtr* ptr1, const CustomPtr* ptr2) const
    {
        return ptr1->Equal(ptr2);
    }
};

class Map final : public CustomPtr {
CUSTOM_VAL(VAL)
public:
    bool Iterator(const std::function<void(CustomPtr *)> &call) const override;
protected:
    void MarkSelf() override;
    void ReadPtr(cereal::BinaryInputArchive &archive) override;
    void WritePtr(cereal::BinaryOutputArchive &archive) override;
private:
    std::unordered_map<CustomPtr *, CustomPtr *, PtrHash, PtrEqual> map;
public:
    void Add(CustomPtr *key, CustomPtr *value);
    CustomPtr *Get(CustomPtr *key);
    unsigned int Size();
    void Remove(CustomPtr *key);
    void Iterator(const std::function<void(CustomPtr *, CustomPtr *)> &call) const;
    void Clear();
protected:
    ~Map() override = default;
};


#endif //MSE_MAP_H
