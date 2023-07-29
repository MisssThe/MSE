//
// Created by MisThe on 2023/7/29.
//

#ifndef MSE_VECTOR_H
#define MSE_VECTOR_H

#include "CustomPtr.h"
#include "Reflect.h"


class Vector : public CustomPtr {
//CUSTOM_PTR(PTR)      //将所有继承自Ptr数据存放到此处
CUSTOM_VAL(VAL)      //需要序列化基础数据类型时填充到此处
public:
    bool Iterator(const std::function<void(CustomPtr *)> &call) const override;
protected:
    void MarkSelf() override;
    void ReadPtr(cereal::BinaryInputArchive &archive) override;
    void WritePtr(cereal::BinaryOutputArchive &archive) override;
protected:
    ~Vector() override = default;
private:
    std::vector<CustomPtr*> vec;
public:
    void Add(CustomPtr* ptr);
    CustomPtr* Get(unsigned int index);
    unsigned int Size();
};


#endif //MSE_VECTOR_H
