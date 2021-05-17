//
// Created by Decision on 2021/3/30.
//

#include "LSBEncoder.h"

void LSBEncoder::encode(uint8_t *_input, uint8_t *_data, int input_len, int data_len) {
    BitReader bitReader(_data);
    for (int i = 0; (i < input_len) && (i / 8 < data_len); i++) {
        uint8_t val = *_input;
        val >>= 1;
        val <<= 1;
        val |= bitReader.fnReadBits(1);
        *_input = val;
        _input++;
    }
}