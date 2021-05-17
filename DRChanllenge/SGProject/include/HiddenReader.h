//
// Created by Decision on 2021/3/30.
//

#ifndef SGPROJECT_HIDDENREADER_H
#define SGPROJECT_HIDDENREADER_H


#include <cstdint>

#include "BitReader.h"
#include "constants.h"

class HiddenReader {
public:
    static void get(uint8_t* _start, int _len);
};


#endif //SGPROJECT_HIDDENREADER_H
