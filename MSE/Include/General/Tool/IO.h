//
// Created by MisThe on 2023/7/26.
//

#ifndef MSE_IO_H
#define MSE_IO_H

#include <string>

class IO final {
private:
    IO() = default;
public:
    static void PathToName(std::string& path);
};


#endif //MSE_IO_H
