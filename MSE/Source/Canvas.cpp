//
// Created by MisThe on 2023/7/26.
//

#include "../Include/Canvas.h"
#include "../Include//Framework/GarbageCollection.h"
#include "Static.h"
#include "../Include/Core/Asset/AssetManager.h"
#include "../Include/Core/Asset/TestAsset.h"

Canvas::Canvas() {
    GarbageCollection::GarbageCollectionConfig config{
            0
    };
    GarbageCollection::S_Config(config);
//    ThreadPool::S_Config({});
    Static::S_Initial();
}

void Canvas::Invoke() {
    while (true) {
//        Canvas中提供线程操作以提高性能`
//        if (Canvas::S_notPause) {
//            Static::S_Components()->Invoke();
//        }
//        Static::S_Psycho()->Invoke();
//        Static::S_Graphic()->Invoke();
//        Static::S_AssetManager()->Invoke();
//        Canvas在执行垃圾回收时需要挂起其他线程
//        合理利用render的同步时间
        GarbageCollection::S_Invoke();
    }
}

Canvas::~Canvas() {
    Static::S_Release();
    GarbageCollection::S_Release();
}