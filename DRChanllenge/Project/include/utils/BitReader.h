//
// Created by Decision on 2021/3/20.
//

#ifndef PROJECT_BITREADER_H
#define PROJECT_BITREADER_H

#include "typedef.h"
#include <iostream>

class BitReader {
protected:
    int _position;
    uint8_t *ptr = nullptr;
    bool err = false;
public:
    BitReader(uint8_t *_ptr, int pos = 0);
    virtual uint32_t fnReadBits(int bit_nums, bool _move = true);
    uint8_t *getPtr();
    int getPosition();
    bool checkErr();
    void debug(uint8_t *_data);
};


#endif //PROJECT_BITREADER_H
