//
// Created by Decision on 2021/3/28.
//

#include "BitOutput.h"

void BitOutput::key_value(uint16_t _key, uint16_t _value) {
    std::cout<<"key: ";
    while (_key) {
        std::cout<<(_key & 1);
        _key >>= 1;
    }
    std::cout<<"\n";

    std::cout<<"value ";
    if (_value == 0) std::cout<<0;
    while (_value) {
        std::cout<<(_value & 1);
        _value >>= 1;
    }
    std::cout<<"\n";
}