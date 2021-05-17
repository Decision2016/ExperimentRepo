//
// Created by Decision on 2021/3/27.
//


#include "Matrix.h"

Matrix::Matrix(int row, int col) {
    this->row = row;
    data = std::unique_ptr<int[]>(new int[row * col]());
}

Matrix::Matrix(const vec2 &t) {
    row = t.size();
    data = std::unique_ptr<int[]>(new int[row * row]());

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row; ++j) {
            data[i * row + j] = t[i][j];
        }
    }
}

Matrix Matrix::operator *(Matrix &mat) {
    Matrix res(row, row);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < row; k++) {
                res[i][j] += data[i * row + k] * mat[k][j];
            }
        }
    }
    return res;
}

Matrix::Matrix() {
    data = nullptr;
    row = 0;
}

Matrix Matrix::operator+(Matrix &matrix) {
    Matrix res(row, row);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
                res[i][j] = data[i * row + j] * matrix[i][j];
        }
    }
    return res;
}

int* Matrix::operator[](const int &k) {
    return &data[k * row];
}

void Matrix::show() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            std::cout<<data[i * row + j]<<" ";
        }
        std::cout<<"\n";
    }
}