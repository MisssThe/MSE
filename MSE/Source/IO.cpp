//
// Created by MisThe on 2023/7/26.
//

#include "../Include/General/Tool/IO.h"

void IO::PathToName(std::string &path) {
    unsigned long begin = path.find_last_of('/') + 1;
    begin = begin == std::string_view::npos ? 0 : begin;
    unsigned long end = path.find_last_of('.');
    end = end == std::string_view::npos ? path.length() : end;
    path = path.substr(begin, end - begin);
}
