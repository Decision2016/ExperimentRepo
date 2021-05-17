#include <cstdio>
#include <iostream>
#include "Appender.h"
#include "LSBEncoder.h"
#include "constants.h"
#include "HiddenReader.h"

int pos = 0;

int main() {
    /*
    FILE *fp = fopen(FILE_PATH1.c_str(), "rb");
    int size = Appender::getFileSize(fp);
    int head_size = size;
    uint8_t *head = new uint8_t[size];
    fread(head, 1, size, fp);
    fclose(fp);

    fp = fopen(FILE_PATH2.c_str(), "rb");
    int bmp_size = Appender::getFileSize(fp);
    uint8_t *bmp = new uint8_t[bmp_size];
    fread(bmp, 1, bmp_size, fp);
    uint32_t *start = reinterpret_cast<uint32_t *>(bmp + 10);
    int offset = *start;
    fclose(fp);

    fp = fopen(FILE_PATH3.c_str(), "rb");
    int file_size = Appender::getFileSize(fp);
    uint8_t *file = new uint8_t[file_size];
    fread(file, 1, file_size, fp);
    fclose(fp);

    LSBEncoder::encode(bmp + offset, file, bmp_size - offset, file_size);
    Appender::append(head, head_size, bmp, bmp_size);
    delete[] file;
    delete[] bmp;
    delete[] head;
    */

    FILE *fp = fopen(FILE_OUTPUT.c_str(), "rb");
    int bmp_size = Appender::getFileSize(fp);
    uint8_t *bmp = new uint8_t[bmp_size];
    fread(bmp, 1, bmp_size, fp);
    uint32_t *start = reinterpret_cast<uint32_t *>(bmp + 10);
    int offset = *start;
    fclose(fp);
    HiddenReader::get(bmp + offset, bmp_size - offset);


    delete[] bmp;
    return 0;
}