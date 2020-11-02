//
// Created by Decision on 2020/11/2.
//

#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H


#include <string>
#include "contants.h"

class Utils {
public:
    static Priorities getPriority(const std::string &_pri);
    static int castString2Int(const std::string &number);
};


#endif //SHELL_UTILS_H
