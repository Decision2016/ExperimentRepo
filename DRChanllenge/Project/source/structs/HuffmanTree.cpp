//
// Created by Decision on 2021/3/20.
//

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(uint8_t *data) {
    uint32_t code = 2;

    const uint8_t* numbers = data + 1;
    const uint8_t* symbols = numbers + 16;

    for (int i = 0; i < 16; i++) {
        int num = numbers[i];
        for (int j = 0; j < num; j++) {
            int symbol = *symbols;
            mp[code] = symbol;
            code++;
            symbols++;
        }
        code <<= 1;
    }
}

uint8_t HuffmanTree::fnGetValue(uint32_t _code) {
    return mp.count(_code) == 0 ? -1 : mp[_code];
}

bool HuffmanTree::fnCheckKey(uint32_t _code) {
    return mp.count(_code) == 0;
}