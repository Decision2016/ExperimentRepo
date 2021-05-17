//
// Created by Decision on 2021/3/30.
//

#ifndef PROJECT_SKIPREADER_H
#define PROJECT_SKIPREADER_H

#include "BitReader.h"
#include "typedef.h"

class SkipReader : public BitReader {
private:
    int skipBlockNum = 0;
    uint8_t *start_ptr = nullptr,
            *record_ptr = nullptr,
            *cache_ptr = nullptr;
    int offset = 0,
        record_pos,
        cache_pos;
    bool skiped = false;
    uint8_t prev = 0;

public:
    SkipReader(uint8_t *_ptr, uint8_t *_sptr, int _pos) :
            BitReader(_ptr, _pos),
            start_ptr(_sptr){}
    void setSkip(int _num);
    void back();
    void record();
    void cache();
    uint32_t fnReadBits(int bit_nums, bool _move = true);
    bool isSkiped();
};


#endif //PROJECT_SKIPREADER_H
