//
// Created by Decision on 2021/3/30.
//

#ifndef SGPROJECT_APPENDER_H
#define SGPROJECT_APPENDER_H

#include <cstdio>
#include <cstdint>
#include "constants.h"

class Appender {
public:
    static void append(uint8_t* input, int input_len,
                        uint8_t* data, int data_len);
    static int getFileSize(FILE *fp);
};


#endif //SGPROJECT_APPENDER_H
