//
// Created by MisThe on 2023/5/11.
//

#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H

#include <string_view>

class Debug final {
private:
    Debug() = default;
public:
    static void Info(const std::string& title, std::initializer_list<std::string> context);
    static void Warn(const std::string& title, std::initializer_list<std::string> context);
    static void Error(const std::string& title, std::initializer_list<std::string> context);
};


#endif //ENGINE_DEBUG_H
