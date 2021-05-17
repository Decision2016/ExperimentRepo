//
// Created by Decision on 2021/3/20.
//

#ifndef PROJECT_HUFFMANTREE_H
#define PROJECT_HUFFMANTREE_H

#include <unordered_map>
#include "typedef.h"

class HuffmanTree {
private:
    std::unordered_map<uint32_t , uint8_t > mp;
public:
    HuffmanTree(uint8_t* data);
    uint8_t fnGetValue(uint32_t _code);
    bool fnCheckKey(uint32_t _code);
};


#endif //PROJECT_HUFFMANTREE_H
