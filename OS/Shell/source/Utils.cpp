//
// Created by Decision on 2020/11/2.
//

#include "Utils.h"

int Utils::castString2Int(const std::string &number) {
    return std::stoi(number);
}

Priorities Utils::getPriority(const std::string &_pri) {
    if (_pri == "2") return Priorities::SYSTEM;
    else if (_pri == "1") return Priorities::USER;
    else if (_pri == "0") return Priorities::INITIAL;
    else return Priorities ::PRI_ERROR;
}