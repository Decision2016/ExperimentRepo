//
// Created by Decision on 2021/3/27.
//

#ifndef PROJECT_IDCT_H
#define PROJECT_IDCT_H
#include "Matrix.h"
#include "constants.h"
#include <cmath>

struct IDCT {
private:
    IDCT();

public:
    static Matrix func(Matrix &matrix);
    static Matrix DCT(Matrix &matrix);
};

#endif //PROJECT_IDCT_H
