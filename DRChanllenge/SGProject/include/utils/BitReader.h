//
// Created by Decision on 2021/3/20.
//

#ifndef PROJECT_BITREADER_H
#define PROJECT_BITREADER_H

#include "typedef.h"
#include <iostream>

class BitReader {
private:
    int _position;
    uint8_t *ptr = nullptr;
public:
    BitReader(uint8_t *_ptr);
    uint32_t fnReadBits(int bit_nums, bool _move = true);
    uint8_t *getPtr();
    void debug(uint8_t *_data);
};


#endif //PROJECT_BITREADER_H
