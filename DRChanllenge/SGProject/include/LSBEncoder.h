//
// Created by Decision on 2021/3/30.
//

#ifndef SGPROJECT_LSBENCODER_H
#define SGPROJECT_LSBENCODER_H


#include <cstdint>
#include "BitReader.h"

class LSBEncoder {
public:
    /*
     * @param input: Carrier file data
     * @param data: Hidden file data
     */
    static void encode(uint8_t *_input, uint8_t *_data,
                        int input_len, int data_len);
};


#endif //SGPROJECT_LSBENCODER_H
