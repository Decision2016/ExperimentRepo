//
// Created by Decision on 2021/3/27.
//

#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include <iostream>
#include <unordered_map>

#include "IDCT.h"
#include "constants.h"
#include "typedef.h"
#include "Matrix.h"
#include "HuffmanTree.h"
#include "SkipReader.h"
#include "ZigZag.h"
#include "BitOutput.h"
#include "Exporter.h"

class Parser {
private:
    uint8_t *parser_ptr, *record_ptr;
    int record_pos;

    /*
     * Temporary variables start here
     * only used to check information
     */
    int width, height;
    Matrix DQT[2];
    std::unordered_map<uint32_t, uint8_t> tree[4];
    Matrix lum[4];
    Matrix Cr, Cb;
    int DCVal = 0;
    int DC_Y = 0, DC_C = 0;
    int errX = 0, errY = 0;
    int skipNum = 0;

public:
    Parser(uint8_t *data_ptr);
    ~Parser();

    void Instance();

    /*
     * Temporary functions start here
     */
    void buildDCT(uint8_t *dct_ptr);
    uint8_t *buildHuffman(uint8_t *huffman_ptr);
    void readAPP0(uint8_t *app0_ptr);
    void readSOF(uint8_t *sof_ptr);
    void readSOS(uint8_t *sos_ptr);
    uint8_t *scanSOS(uint8_t *sos_ptr);
    bool JIFFDecode(BitReader &bitReader, int huffmanType);
    void YCrCb2RGB();
    void recoverFile();
    int checkSector();
};


#endif //PROJECT_PARSER_H
