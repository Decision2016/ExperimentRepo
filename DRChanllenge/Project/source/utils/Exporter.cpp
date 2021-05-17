//
// Created by Decision on 2021/3/30.
//

#include "Exporter.h"

void Exporter::output(uint8_t *_ptr, int _start, int _end) {
    FILE *fp = fopen("../images/test_output.jpg", "a+");

    uint8_t *start_ptr = _ptr + _start * 512;
    int writeSize = (_end - _start) * 512;
    fwrite(start_ptr, 1, writeSize, fp);
    fclose(fp);
}