//
// Created by Decision on 2021/3/30.
//

#ifndef PROJECT_EXPORTER_H
#define PROJECT_EXPORTER_H

#include <cstdio>
#include "typedef.h"

class Exporter {
public:
    static void output(uint8_t* _ptr, int _start, int _end);
};


#endif //PROJECT_EXPORTER_H
