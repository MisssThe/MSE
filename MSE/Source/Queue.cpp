//
// Created by MisThe on 2023/7/28.
//

#include "../Include/General/Container/Queue.h"


REGISTER(Queue)

bool Queue::Contain(CustomPtr *temp) {
    return !this->IteratorWithResult([&temp](CustomPtr* t) {
        return t != temp;
    });
}

bool Queue::IteratorWithResult(const std::function<bool(CustomPtr *)> &func) {
    int size = this->queue.size();
    bool result = true;
    for (int index = 0; index < size; ++index) {
        CustomPtr* temp = this->queue.front();
        this->queue.pop();
        result &= func(temp);
        this->queue.push(temp);
    }
    return result;
}

bool Queue::IteratorWithRemove(const std::function<bool(CustomPtr *)> &func) {
    int size = this->queue.size();
    for (int index = 0; index < size; ++index) {
        CustomPtr* temp = this->queue.front();
        this->queue.pop();
        if (func(temp))
            this->queue.push(temp);
    }
    return this->queue.size() == size;
}

void Queue::IteratorWithout(std::function<void(CustomPtr *)> func){
    this->IteratorWithRemove([&func](CustomPtr* temp) -> bool {
        func(temp);
        return true;
    });
}

void Queue::Clear() {
    std::queue<CustomPtr*> empty;
    std::swap(this->queue, empty);
}

int Queue::Size() {
    return this->queue.size();
}

void Queue::Remove(CustomPtr *t) {
    this->IteratorWithRemove([&t](CustomPtr* temp) {
        return temp != t;
    });
}

CustomPtr *Queue::Next() {
    CustomPtr *temp = this->Pop();
    this->Push(temp);
    return temp;
}

CustomPtr *Queue::Pop(){
    CustomPtr* temp = this->queue.front();
    this->queue.pop();
    return temp;
}

CustomPtr *Queue::Front() {
    return this->queue.front();
}

void Queue::Push(CustomPtr *temp) {
    this->queue.push(temp);
}

void Queue::WritePtr(cereal::BinaryOutputArchive &archive) {
    archive(this->Size());
    this->IteratorWithout([&archive](CustomPtr *ptr) -> void {
        std::string type;
        if (ptr != nullptr)
            type = ptr->Type();
        archive(type);
    });
    this->IteratorWithout([&archive](CustomPtr *ptr) -> void {
        if (ptr == nullptr)
            return;
        ptr->serialize(archive);
    });
}

void Queue::ReadPtr(cereal::BinaryInputArchive &archive) {
    int size = 0;
    archive(size);
    std::string type;
    for (int index = 0; index < size; ++index) {
        archive(type);
        CustomPtr *ptr = nullptr;
        ptr = Reflect::S_Instance(type);
        this->Push(ptr);
    }
    this->IteratorWithout([&archive](CustomPtr *ptr) -> void {
        if (ptr == nullptr)
            return;
        ptr->serialize(archive);
    });
}

void Queue::MarkSelf() {
    this->IteratorWithout([](CustomPtr *ptr)->void{
        if (ptr == nullptr)
            return;
        ptr->Mark();
    });
}

bool Queue::Iterator(const std::function<void(CustomPtr *)> &call) const {
    throw std::bad_alloc();
}

Queue::Queue(std::initializer_list<CustomPtr *> init) {
    for (auto info: init) {
        this->Push(info);
    }
}
