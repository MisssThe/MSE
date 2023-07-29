//
// Created by MisThe on 2023/5/21.
// 禁止用户手动删除指针，用户只能通过ptr = null的方式去减少指针引用
// 禁止用户手动开辟线程操作，只能通过提供的线程池进行线程操作
// 使用非Custom Ptr类型的指针要注意手动释放
//

#ifndef CANVAS_1_0_CUSTOMPTR_H
#define CANVAS_1_0_CUSTOMPTR_H

#include <string>
#include <functional>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include "Reflect.h"

// 参数个数范围为1~15，超过需要手动扩展
#define COUNT_IMP( _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, NUM, ...) NUM
#define COUNT(...) COUNT_IMP(__VA_ARGS__, 29,28,27,26,,25,24,23,22,21,20,19,18,17,16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define IS_ZERO(...) COUNT_IMP(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1, 0)

#define REFLECT_0(arg)
#define REFLECT_1(Ptr, arg) call(this->arg);
#define REFLECT_2(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_1(Ptr, __VA_ARGS__)
#define REFLECT_3(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_2(Ptr, __VA_ARGS__)
#define REFLECT_4(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_3(Ptr, __VA_ARGS__)
#define REFLECT_5(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_4(Ptr, __VA_ARGS__)
#define REFLECT_6(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_5(Ptr, __VA_ARGS__)
#define REFLECT_7(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_6(Ptr, __VA_ARGS__)
#define REFLECT_8(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_7(Ptr, __VA_ARGS__)
#define REFLECT_9(Ptr, arg, ...)  REFLECT_1(Ptr, arg) REFLECT_8(Ptr, __VA_ARGS__)
#define REFLECT_10(Ptr, arg, ...) REFLECT_1(Ptr, arg) REFLECT_9(Ptr, __VA_ARGS__)
#define REFLECT_11(Ptr, arg, ...) REFLECT_1(Ptr, arg) REFLECT_10(Ptr, __VA_ARGS__)
#define REFLECT_12(Ptr, arg, ...) REFLECT_1(Ptr, arg) REFLECT_11(Ptr, __VA_ARGS__)
#define REFLECT_13(Ptr, arg, ...) REFLECT_1(Ptr, arg) REFLECT_12(Ptr, __VA_ARGS__)
#define REFLECT_14(Ptr, arg, ...) REFLECT_1(Ptr, arg) REFLECT_13(Ptr, __VA_ARGS__)
#define REFLECT_15(Ptr, arg, ...) REFLECT_1(Ptr, arg) REFLECT_14(Ptr, __VA_ARGS__)


#define SERIALIZE_READ_0(arg)
#define SERIALIZE_READ_1(Ptr, arg) archive(type); Reflect::S_Instance(type, reinterpret_cast<CustomPtr *&>(this->arg));
#define SERIALIZE_READ_2(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_1(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_3(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_2(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_4(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_3(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_5(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_4(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_6(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_5(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_7(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_6(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_8(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_7(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_9(Ptr, arg, ...)  SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_8(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_10(Ptr, arg, ...) SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_9(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_11(Ptr, arg, ...) SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_10(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_12(Ptr, arg, ...) SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_11(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_13(Ptr, arg, ...) SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_12(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_14(Ptr, arg, ...) SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_13(Ptr, __VA_ARGS__)
#define SERIALIZE_READ_15(Ptr, arg, ...) SERIALIZE_READ_1(Ptr, arg) SERIALIZE_READ_14(Ptr, __VA_ARGS__)




#define SYMBOL_CATENATE(arg1, arg2) arg1##arg2
#define SYMBOL_CATENATE_WITH_MACRO(arg1, arg2) SYMBOL_CATENATE(arg1, arg2)

#define REFLECT(...)  bool Iterator(const std::function<void(CustomPtr *)> &call) const override { SYMBOL_CATENATE_WITH_MACRO(REFLECT_, COUNT(__VA_ARGS__))(__VA_ARGS__) return true;}
#define MARCO(marco) marco

#define SERIALIZE_READ(...)                                                                                          \
void ReadPtr(cereal::BinaryInputArchive &archive) override {                                                         \
    std::string type;                                                                                                \
    SYMBOL_CATENATE_WITH_MACRO(SERIALIZE_READ_, COUNT(__VA_ARGS__))(__VA_ARGS__)                                     \
    this->Iterator([&archive](CustomPtr *ptr)->void {                                                                \
        if (ptr == nullptr)                                                                                          \
            return;                                                                                                  \
        ptr->serialize(archive);                                                                                     \
    });                                                                                                              \
}

#define CUSTOM_PTR(...)         \
public:                         \
MARCO(REFLECT(__VA_ARGS__))     \
protected:                      \
void MarkSelf() override { this->Iterator([](CustomPtr *ptr) ->void { if (ptr == nullptr) return; ptr->Mark(); }); } \
SERIALIZE_READ(__VA_ARGS__)                                                                                          \
void WritePtr(cereal::BinaryOutputArchive &archive) override{                                                        \
    this->Iterator([&archive](CustomPtr *ptr)->void{                                                                 \
        std::string type; if(ptr != nullptr) type = ptr->Type(); archive(type);                                      \
    });                                                                                                              \
    this->Iterator([&archive](CustomPtr *ptr)->void{                                                                 \
        if (ptr == nullptr)                                                                                          \
            return;                                                                                                  \
        ptr->serialize(archive);                                                                                     \
    });                                                                                                              \
}

#define SERIALIZE_VAL_0(...)
#define SERIALIZE_VAL_1(VAL, ...) archive(__VA_ARGS__);


#define CUSTOM_VAL(...)     \
protected:                  \
void ReadVal(cereal::BinaryInputArchive &archive) override { SYMBOL_CATENATE_WITH_MACRO(SERIALIZE_VAL_, IS_ZERO(__VA_ARGS__))(__VA_ARGS__) }    \
void WriteVal(cereal::BinaryOutputArchive &archive) override { SYMBOL_CATENATE_WITH_MACRO(SERIALIZE_VAL_, IS_ZERO(__VA_ARGS__))(__VA_ARGS__) }  \
public:                                                                                 \
std::string Type() override;

#define REGISTER(type)      \
bool type##Register = Reflect::S_Register(#type, []()->CustomPtr*{ return new type(); }); \
std::string type::Type() { return #type; }

class CustomPtr
{
    //CUSTOM_PTR(PTR)
    //CUSTOM_VAL(VAL)
public:
    CustomPtr();
public:
    void Release();
    void Mark();
    [[nodiscard]] virtual size_t Hash() const;
    virtual bool Equal(const CustomPtr* ptr) const;
    virtual std::string Type() = 0;
public:
    bool isMark = false;
protected:
    virtual void MarkSelf();
    virtual ~CustomPtr() = default;
public:
    void serialize(cereal::BinaryInputArchive& archive);
    void serialize(cereal::BinaryOutputArchive& archive);
protected:
    virtual void ReadPtr(cereal::BinaryInputArchive& archive) = 0;
    virtual void ReadVal(cereal::BinaryInputArchive& archive) = 0;
    virtual void WritePtr(cereal::BinaryOutputArchive& archive) = 0;
    virtual void WriteVal(cereal::BinaryOutputArchive& archive) = 0;
public:
    virtual bool Iterator(const std::function<void(CustomPtr *)> &call) const;;
};

#endif //CANVAS_1_0_CUSTOMPTR_H
