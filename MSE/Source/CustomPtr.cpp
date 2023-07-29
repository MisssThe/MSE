//
// Created by MisThe on 2023/5/21.
//

#include "../Include/Framework/GarbageCollection.h"
#include "../Include/Framework/Custom/CustomPtr.h"
//#include "../Include//Framework/ThreadPool.h"

CustomPtr::CustomPtr() {
    this->isMark = false;
    GarbageCollection::S_Register(this);
    //非主线程上创建的任务需要注册到线程池的数据集中
}

void CustomPtr::Release() {
    delete this;
}

void CustomPtr::Mark() {
    if (this->isMark)
        return;
    this->isMark = true;
    this->MarkSelf();
}

size_t CustomPtr::Hash() const {
    auto address = (unsigned long) this;
    return std::hash<unsigned long>()(address);
}

bool CustomPtr::Equal(const CustomPtr *ptr) const {
    return this == ptr;
}

void CustomPtr::serialize(cereal::BinaryInputArchive &archive) {
    this->ReadPtr(archive);
    this->ReadVal(archive);
}

void CustomPtr::serialize(cereal::BinaryOutputArchive &archive) {
    this->WritePtr(archive);
    this->WriteVal(archive);
}

void CustomPtr::MarkSelf() {

}

bool CustomPtr::Iterator(const std::function<void(CustomPtr *)> &call) const {
    return false;
}
