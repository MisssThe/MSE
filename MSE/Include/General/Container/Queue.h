//
// Created by MisThe on 2023/7/26.
//

#ifndef MSE_QUEUE_H
#define MSE_QUEUE_H

#include <queue>
#include "CustomPtr.h"

class Queue final : public CustomPtr {
//CUSTOM_PTR(PTR)
CUSTOM_VAL(VAL)
public:
    //禁止调用，queue的遍历限制了const的使用会破坏规则
    bool Iterator(const std::function<void(CustomPtr *)> &call) const override;
protected:
    void MarkSelf() override;
    void ReadPtr(cereal::BinaryInputArchive &archive) override;
    void WritePtr(cereal::BinaryOutputArchive &archive) override;
private:
    std::queue<CustomPtr*> queue;
protected:
    ~Queue() override = default;
public:
    Queue(std::initializer_list<CustomPtr*> init);
    Queue() = default;
public:
    void Push(CustomPtr* temp);
    CustomPtr* Front();
    CustomPtr* Pop();
    CustomPtr* Next();
    void Remove(CustomPtr* t);
    int Size();
    void Clear();
    void IteratorWithout(std::function<void(CustomPtr*)> func);
    bool IteratorWithRemove(const std::function<bool(CustomPtr*)>& func);
    bool IteratorWithResult(const std::function<bool(CustomPtr*)>& func);
    bool Contain(CustomPtr* temp);
};


#endif //MSE_QUEUE_H
