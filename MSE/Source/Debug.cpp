//
// Created by MisThe on 2023/5/11.
//

#include <iostream>
#include "../Include/General/Tool/Time.h"
#include "../Include/General/Tool/Debug.h"

void Debug::Info(const std::string& title, std::initializer_list<std::string> context) {
    std::cout << "\033[32m[" <<
              Time::CanvasTimeWithStr() <<
              "] [" <<
              title <<
              "]: ";
    for (auto c : context) {
        std::cout << c;
    }
  std::cout << std::endl;
}

void Debug::Warn(const std::string& title, std::initializer_list<std::string> context) {
    std::cout << "\033[33m[" <<
              Time::CanvasTimeWithStr() <<
              "] [" <<
              title <<
              "]: ";
    for (auto c : context) {
        std::cout << c;
    }
    std::cout << std::endl;
}

void Debug::Error(const std::string& title, std::initializer_list<std::string> context) {
    std::cout << "\033[31m[" <<
              Time::CanvasTimeWithStr() <<
              "] [" <<
              title <<
              "]: ";
    for (auto c : context) {
        std::cout << c;
    }
    std::cout << std::endl;
}
