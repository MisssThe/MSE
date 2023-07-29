//
// Created by MisThe on 2023/7/26.
//

#ifndef MSE_ASSET_H
#define MSE_ASSET_H

#include "CustomPtr.h"

class Asset : public CustomPtr {
CUSTOM_PTR(PTR)                  //将所有继承自Ptr数据存放到此处
CUSTOM_VAL(VAL,name,path)        //需要序列化基础数据类型时填充到此处
public:
    std::string name;
    std::string path;
protected:
    ~Asset() override = default;
};


#endif //MSE_ASSET_H
