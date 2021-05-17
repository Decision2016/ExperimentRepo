//
// Created by Decision on 2021/3/20.
//

#include "BitReader.h"

BitReader::BitReader(uint8_t *_ptr, int pos) {
    ptr = _ptr;
    _position = pos;
}

// input bit_num, read bit from left to right
uint32_t BitReader::fnReadBits(int bit_nums, bool _move) {
    if (bit_nums > 16) return 0;
    uint16_t res = 0;
    uint8_t _tmp;
    int savePos = _position;
    uint8_t *savePtr = ptr;
    int nextPosition = _position + bit_nums;


    for (int i = 0; i < 3; i++) {
        _tmp = *ptr << _position;
        _tmp >>= _position;
        if (nextPosition == -1) break;
        if (nextPosition >= 8) {
            res = (res << 8) + _tmp;
            _position = 0;
            if (*ptr == 0xFF && *(ptr + 1) == 0x00) ptr += 2;
            else if (*ptr == 0xFF && *(ptr + 1) != 0x00){
                err = true;
            }
            else ptr++;
            nextPosition -= 8;
        }
        else if(nextPosition < 8){
            int delta = 8 - nextPosition;
            res = (res << nextPosition) + (_tmp >> delta);
            _position = nextPosition;
            nextPosition = -1;
        }
    }

    if (!_move) {
        ptr = savePtr;
        _position = savePos;
    }

    return res;
}

void BitReader::debug(uint8_t *_data) {
    // std::cout<<"Count:"<<_position<<std::endl;
    std::cout<<std::hex<<(int)(ptr - _data)<<":"<<_position<<std::endl;
}

uint8_t* BitReader::getPtr() {
    return ptr;
}
bool BitReader::checkErr() {
    return err;
}
int BitReader::getPosition() {
    return _position;
}