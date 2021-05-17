//
// Created by Decision on 2021/3/30.
//

#include "HiddenReader.h"

void HiddenReader::get(uint8_t *_start, int _len) {
    FILE *fp = fopen(HIDDEN_OUTPUT.c_str(), "wb");
    uint8_t val = 0, _val, count = 0;

    for (int i = 0; i < _len; i++) {
        // 获取最低位 _val
        _val = *_start & 1;
        // 暂存值左移一位， 将当前的最低位放到暂存值的最低位
        val = (val << 1) | _val;
        // 计数器+1
        count++;
        // 如果计数器+1则写出
        if (count == 8) {
            fwrite(&val, 1, 1, fp);
            count = 0;
            val = 0;
        }
        _start++;
    }
    fwrite(&val, 1, 1, fp);
    fclose(fp);
}