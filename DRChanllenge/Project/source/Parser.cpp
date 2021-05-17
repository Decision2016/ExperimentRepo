//
// Created by Decision on 2021/3/27.
//

#include "Parser.h"

void Parser::Instance() {
    uint8_t *read_ptr = parser_ptr;
    while (true) {
        auto *now = reinterpret_cast<uint16_t *> (read_ptr);
        // JPEG Header
        if (*now == 0xD8FF) {
            std::cout<<"read file as jpeg image file.\n";
            read_ptr += 2;
        }
        // JPEG APP0
        else if (*now == 0xE0FF) {
            std::cout<<"APP0 Marker:\n";
            readAPP0(read_ptr + 9);
            read_ptr = read_ptr + 0x12;
        }
        // JPEG DQT
        else if (*now == 0xDBFF) {
            BitReader bitReader(read_ptr + 2);
            int len = bitReader.fnReadBits(16);
            std::cout<<"Maker: DQT\n";
            buildDCT(read_ptr);
            read_ptr += len + 2;
        }
        // JPEG Huffman
        else if (*now == 0xC4FF) {
            std::cout<<"Maker: Huffman Tree\n";
            BitReader bitReader(read_ptr + 2);
            int len = bitReader.fnReadBits(16);
            uint8_t *huffman = read_ptr + 4;
            read_ptr += len + 2;
            while (huffman != read_ptr) {
                huffman = buildHuffman(huffman);
            }
        }
        // JPEG SOF
        else if (*now == 0xC0FF) {
            BitReader bitReader(read_ptr + 2);
            int len = bitReader.fnReadBits(16);
            std::cout<<"Maker: SOF\n";
            readSOF(read_ptr);
            read_ptr += len + 2;
        }
        // JPEG Scan Line
        else if (*now == 0xDAFF) {
            BitReader bitReader(read_ptr + 2);
            int len = bitReader.fnReadBits(16);
            std::cout<<"Marker: Scan Line Start\n";
            // readSOS(read_ptr);
            read_ptr += len + 2;
            std::cout<<"Start scan data information\n";
            read_ptr = scanSOS(read_ptr);
            if (read_ptr == nullptr) {
                std::cout<<"Trying recover broken picture file...\n";
                // recoverFile();
                checkSector();
                break;
            }
            read_ptr++;
        }
        else if (*now == 0xD9FF) {
            std::cout<<"Scan Finish!\n";
            break;
        }
        else {
            read_ptr++;
        }
    }
}

Parser::Parser(uint8_t *data_ptr) {
    parser_ptr = data_ptr;
}

Parser::~Parser() {
    delete[] parser_ptr;
}

void Parser::readAPP0(uint8_t *app0_ptr) {
    BitReader bitReader(app0_ptr);
    std::cout<<"version:"<<bitReader.fnReadBits(8)<<"."<<bitReader.fnReadBits(8)<<std::endl;
    std::cout<<"units:"<<bitReader.fnReadBits(8)<<std::endl;
    width = bitReader.fnReadBits(16);
    height = bitReader.fnReadBits(16);
    std::cout<<"density:"<<width<<"*"<<height<<std::endl;
    std::cout<<"thumbnail:"<<bitReader.fnReadBits(8)<<"*"<<bitReader.fnReadBits(8)<<std::endl;
}

void Parser::buildDCT(uint8_t *dct_ptr) {
    std::vector<int> vec;
    BitReader bitReader(dct_ptr + 2);
    int len = bitReader.fnReadBits(16);
    int type = bitReader.fnReadBits(8);
    dct_ptr += 5;
    for (int i = 0; i < len; i++) {
        vec.push_back(*dct_ptr);
        dct_ptr++;
    }
    DQT[type] = ZigZag::func(vec);
    DQT[type].show();
    vec.clear();
    return ;
}

void Parser::readSOF(uint8_t *sof_ptr) {
    BitReader bitReader(sof_ptr + 5);
    height = bitReader.fnReadBits(16);
    width = bitReader.fnReadBits(16);
    std::cout<<"Size:"<<height<<"x"<<width<<std::endl;
}

uint8_t* Parser::buildHuffman(uint8_t *huffman_ptr) {
    int huffmanType = ((*huffman_ptr >> 4) << 1) + (*huffman_ptr & 0x01);
    uint32_t code = 2;

    const uint8_t* numbers = huffman_ptr + 1;
    const uint8_t* symbols = numbers + 16;

    for (int i = 0; i < 16; i++) {
        int num = numbers[i];
        for (int j = 0; j < num; j++) {
            int symbol = *symbols;
            tree[huffmanType][code] = symbol;
            // std::cout<<"Huffman Tree #"<<huffmanType<<": "<<(int)code<<" "<<(int)symbol<<std::endl;
            code++;
            symbols++;
        }
        code <<= 1;
    }
    return const_cast<uint8_t *>(symbols);
}

uint8_t* Parser::scanSOS(uint8_t *sos_ptr) {
    BitReader bitReader(sos_ptr);
    record_ptr = sos_ptr;
    bool flag = true;
    uint8_t *tmp_ptr;
    int tmp_pos;
    int _h = height / 16, _w = width / 16;
    // 4:2:1
    if (height % 16 != 0) _h++;
    if (width % 16 != 0) _w++;

    // check scan error and break
    auto check = [&](const int &i, const int &j){
        if (!flag || bitReader.checkErr()) {
            std::cout<<"MCU ("<<j<<", "<<i<<") Error at ";
            bitReader.debug(parser_ptr);
            errX = i, errY = j;
            return true;
        }
        return false;
    };

    // record position if sector is different
    auto record_func = [&]() {
        /*
         * record bitReader`s point if cross block
         * _offset1: offset after scan
         * _offset2: offset before scan
         */
        int _offset1 = int(bitReader.getPtr() - parser_ptr);
        int _offset2 = int(tmp_ptr - parser_ptr);
        if (_offset1 / 512 > _offset2 / 512) {
            record_ptr = tmp_ptr;
            record_pos = tmp_pos;
        }
    };

    // scan all MCU
    for (int i = 0; i < _h; ++i) {
        for (int j = 0; j < _w; ++j) {
            tmp_ptr = bitReader.getPtr();
            tmp_pos = bitReader.getPosition();
            // 4 luminance blocks
            for (auto &item : lum) {
                flag &= JIFFDecode(bitReader, 0);
                if(check(i, j)) {
                    record_func();
                    return nullptr;
                }
            }
            // Cr block
            flag &= JIFFDecode(bitReader, 1);
            if(check(i, j)) {
                record_func();
                return nullptr;
            }
            // Cb block
            flag &= JIFFDecode(bitReader, 1);
            if(check(i, j)) {
                record_func();
                return nullptr;
            }
        }
    }
    return bitReader.getPtr();
}

/*
 * JIFFDecode function
 * read DC Value at first
 * then read 63 or less AC Values
 */
bool Parser::JIFFDecode(BitReader &bitReader, int huffmanType) {
    uint8_t DCHuffman = 0 + huffmanType, ACHuffman = 2 + huffmanType;
    int readCount = 0, elementCount = 0;
    int zeroCount = 0, nextRead;
    int DC_Delta = 0, ACVal;

    // The Huffman code starts with 0x1, to avoid confusion
    uint32_t _key = 1;
    uint8_t _value;

    while(tree[DCHuffman].count(_key) == 0 && readCount < 16) {
        _key = (_key << 1) + bitReader.fnReadBits(1);
        readCount++;
    }

    if (tree[DCHuffman].count(_key) == 0) {
        return  false;
    }

    _value = tree[DCHuffman][_key];
    zeroCount = _value >> 4;
    nextRead = _value & 0x0F;

    DC_Delta = bitReader.fnReadBits(nextRead);
    if (nextRead != 0 && DC_Delta < (1 << (nextRead - 1))) {
        DC_Delta = ~DC_Delta;
    }
    DCVal += DC_Delta;
    elementCount ++;

    while (elementCount < 64) {
        _key = 1;
        readCount = 0;

        while(tree[ACHuffman].count(_key) == 0 && readCount < 16) {
            _key = (_key << 1) + bitReader.fnReadBits(1);
            readCount++;
        }
        if (tree[ACHuffman].count(_key) == 0) {
            return false;
        }

        _value = tree[ACHuffman][_key];
        if (_value == 0) break;
        zeroCount = _value >> 4;
        nextRead = _value & 0x0F;
        ACVal = bitReader.fnReadBits(nextRead);
        elementCount += zeroCount + 1;
    }
    return true;
}

void Parser::YCrCb2RGB() {
    Matrix *RGB[4];

    Matrix Cr_mat = Cr + DQT[1];
    Matrix Cb_mat = Cb + DQT[1];
    Cr_mat = IDCT::func(Cr_mat);
    Cb_mat = IDCT::func(Cb_mat);

    for (int i = 0; i < 4;i ++) {
        Matrix lum_mat = lum[i] + DQT[0];
        lum_mat = IDCT::func(lum_mat);
        lum_mat.show();
    }
}

void Parser::recoverFile() {
    // int _end = (record_ptr - parser_ptr) / 512;
    // Exporter::output(parser_ptr, 0, _end);
    SkipReader bitReader(record_ptr, parser_ptr, record_pos);
    bitReader.cache();
    bitReader.record();

    uint8_t *tmp_ptr;
    bool flag = true;
    int _h = height / 16, _w = width / 16;
    if (height % 16 != 0) _h++;
    if (width % 16 != 0) _w++;

    // check fragment and skip sector
    auto checkAndSkip = [&]() {
        if (!flag || bitReader.checkErr()) {
            if (bitReader.isSkiped()) skipNum++;
            else skipNum = 1;
            // check fragment and Output information
            std::cout<<"Find broken fragment at position:"<<std::hex<<
                int(bitReader.getPtr() - parser_ptr)<<":"<<std::dec<<bitReader.getPosition()<<", skip "<<
                std::dec<<skipNum<<" blocks.\n";

            bitReader.setSkip(skipNum);
            bitReader.back();
            return true;
        }
        return false;
    };

    auto record = [&]() {
        int _offset1 = int(bitReader.getPtr() - parser_ptr);
        int _offset2 = int(tmp_ptr - parser_ptr);
        if (_offset1 / 512 < _offset2 / 512) {
            bitReader.record();
        }
    };

    // start at error position
    for (int i = errX; i < _h; i++) {
        for (int j = errY; j < _w; j++) {
            bitReader.cache();
            tmp_ptr = bitReader.getPtr();
            bool restart = false;

            for (auto &item : lum) {
                flag &= JIFFDecode(bitReader, 0);
                if (checkAndSkip()) {
                    j--;
                    record();
                    flag = true;
                    restart = true;
                    break;
                };
            }
            if (restart) continue;
            flag &= JIFFDecode(bitReader, 1);
            if (checkAndSkip()) {
                j--;
                record();
                flag = true;
                continue;
            };
            flag &= JIFFDecode(bitReader, 1);
            if (checkAndSkip()) {
                j--;
                record();
                flag = true;
                continue;
            };
        }
    }
}

int Parser::checkSector() {
    int sectorNum = 600;

    for (int i = i ; i < sectorNum; i++) {
        SkipReader bitReader(record_ptr, parser_ptr, record_pos);
        bitReader.cache();
        bitReader.record();
        bitReader.setSkip(i);
        bitReader.back();
        bool flag = true;
        int offset = (record_ptr - parser_ptr) / 512 + 1 + i + 14;
        offset *= 512;
        uint8_t *next_ptr = parser_ptr + offset;
        while (bitReader.getPtr() < next_ptr) {
            for (auto &item : lum) {
                flag &= JIFFDecode(bitReader, 0);
            }
            flag &= JIFFDecode(bitReader, 1);
            flag &= JIFFDecode(bitReader, 1);
        }
        if (flag && !bitReader.checkErr()) std::cout<<std::dec<<i<<std::hex<<" "<<offset - 0x1c00<<std::endl;
    }
    return 0;
}