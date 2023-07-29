//
// Created by MisThe on 2023/7/26.
// 实现对基础值类型的存储，方便GC运作，环境统一
// 重载address操作方便比较
//

#ifndef CANVAS_1_0_CUSTOMVAL_H
#define CANVAS_1_0_CUSTOMVAL_H

#include "CustomPtr.h"


class CustomVal : public CustomPtr {
public:
    CUSTOM_PTR(PTR)  //将所有继承自Ptr数据存放到此处
protected:
    void ReadVal(cereal::BinaryInputArchive &archive) override;
    void WriteVal(cereal::BinaryOutputArchive &archive) override;
public:
    std::string Type() override;
public:
    CustomVal();
    explicit CustomVal(const std::string& code);
    explicit CustomVal(const char* code);
    explicit CustomVal(char code);
    explicit CustomVal(int code);
    explicit CustomVal(float code);
public:
    void SetString(const std::string& code);
public:
    std::string ToString();
    int ToInt();
//    int ToInt();
//    float ToFloat();
public:
    size_t Hash() const override;
    bool Equal(const CustomPtr *ptr) const override;
private:
    char* codes = nullptr;
    unsigned int length = 0;
protected:
    ~CustomVal() override;
};


#endif //CANVAS_1_0_CUSTOMVAL_H
