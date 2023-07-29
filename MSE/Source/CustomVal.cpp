//
// Created by MisThe on 2023/7/26.
//

#include "../Include/Framework/Custom/CustomVal.h"

REGISTER(CustomVal)

CustomVal::~CustomVal() {
    delete[] this->codes;
}

size_t CustomVal::Hash() const {
    size_t result = 0;
    std::hash<char> h;
    for (int i = 0; i < this->length; ++i) {
        result += h(this->codes[i]);
    }
    return result;
}

bool CustomVal::Equal(const CustomPtr *ptr) const {
    if (ptr == nullptr)
        return false;
    auto* cv = (CustomVal *) ptr;
    if (cv->codes == nullptr)
        return false;
    if (cv->length != this->length)
        return false;
    for (int i = 0; i < this->length; ++i) {
        if (this->codes[i] != cv->codes[i])
            return false;
    }
    return true;
}

CustomVal::CustomVal(const std::string &code) {
    this->SetString(code);
}

CustomVal::CustomVal(int code) {
    std::string strCodes = std::to_string(code);
    this->SetString(strCodes);
}

CustomVal::CustomVal(float code) {
    std::string strCodes = std::to_string(code);
    this->SetString(strCodes);
}

CustomVal::CustomVal(const char *code) {
    this->length = std::strlen(code);
    this->codes = new char[this->length];
    std::strcpy(this->codes, code);
}

CustomVal::CustomVal(char code) {
    this->length = 1;
    this->codes = new char[this->length];
    this->codes[0] = code;
}

CustomVal::CustomVal() {
    this->codes = new char[0];
}

void CustomVal::ReadVal(cereal::BinaryInputArchive &archive) {
    std::string str;
    archive(str);
    this->SetString(str);
}

void CustomVal::WriteVal(cereal::BinaryOutputArchive &archive) {
    std::string str(this->codes);
    archive(str);
}

void CustomVal::SetString(const std::string &code) {
    if (this->codes != nullptr)
        delete[] this->codes;
    this->length = code.length();
    this->codes = new char[this->length];
    std::strcpy(this->codes, code.c_str());
}

std::string CustomVal::ToString() {
    return {this->codes};
}

int CustomVal::ToInt() {
    int result = 0;
    for (int index = 0; index < this->length; ++index) {
        result *= 10;
        result += (this->codes[index] - 48);
    }
    return result;
}
