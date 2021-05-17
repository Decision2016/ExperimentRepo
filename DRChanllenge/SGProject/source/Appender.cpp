//
// Created by Decision on 2021/3/30.
//

#include "Appender.h"

void Appender::append(uint8_t *input, int input_len, uint8_t *data, int data_len) {
    FILE *fp = fopen(FILE_OUTPUT.c_str(), "wb");
    fwrite(input, 1, input_len, fp);
    fwrite(data, 1, data_len, fp);
    fclose(fp);
}

int Appender::getFileSize(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int res = ftell(fp);
    fseek(fp, 0, 0);
    return res;
}