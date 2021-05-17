//
// Created by Decision on 2021/3/30.
//

#include "SkipReader.h"

void SkipReader::setSkip(int _num) {
    skipBlockNum = _num;
}

void SkipReader::record() {
    if (record_ptr == cache_ptr) return ;
    skiped = false;
    record_ptr = cache_ptr;
    record_pos = cache_pos;
}

void SkipReader::cache() {
    cache_ptr = ptr;
    cache_pos = _position;
}

uint32_t SkipReader::fnReadBits(int bit_nums, bool _move) {
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
            if (prev != 0xFF || *ptr != 0x00) {
                res = (res << 8) + _tmp;
                _position = 0;
                prev = *ptr;
                nextPosition -= 8;
            }
            else if (prev == 0xFF && *ptr != 0x00) {
                err = true;
            }
            ptr++;
            offset++;


            if (skipBlockNum != 0 && offset == 512) {
                ptr += 512 * skipBlockNum;
                offset = 0;
                skipBlockNum = 0;
            }
            if (offset == 512) offset = 0;
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

void SkipReader::back() {
    skiped = true;
    ptr = record_ptr;
    _position = record_pos;
    offset = (ptr - start_ptr) % 512;
    err = false;
}

bool SkipReader::isSkiped() {
    return skiped;
}