//
// Created by Decision on 2021/3/27.
//

#ifndef PROJECT_MATRIX_H
#define PROJECT_MATRIX_H

#include "typedef.h"
#include <memory>
#include <cstring>
#include <iostream>

class Matrix {
private:
    std::unique_ptr<int[]> data;
    int row;
public:
    Matrix();
    Matrix(const vec2 &t);
    Matrix(int row, int col);
    Matrix operator * (Matrix &matrix);
    Matrix operator + (Matrix &matrix);
    int *operator[] (const int &k);
    void show();
};

#endif //PROJECT_MATRIX_H
