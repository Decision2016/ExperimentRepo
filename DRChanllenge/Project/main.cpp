#include <iostream>

#include "Matrix.h"
#include "Parser.h"
#include "constants.h"
#include "typedef.h"
#include "IDCT.h"

int main() {
    int fileSize;
    FILE *fp = fopen(path.c_str(), "rb");

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);

    fseek(fp, 0, 0);
    auto *data = new uint8_t[fileSize];
    fread(data, 1, fileSize, fp);
    Parser parser(data);
    parser.Instance();
    /*
    int val = 0;
    Matrix mat(8, 8);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cin >> val;
            mat[i][j] = val;
        }
    }
    mat = IDCT::DCT(mat);
    mat.show();
    */
    return 0;
}