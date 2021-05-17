//
// Created by Decision on 2021/3/28.
//

#include "IDCT.h"

Matrix IDCT::func(Matrix &matrix) {
    const double pi = 3.141592654;
    double tmp = 0, alpha, beta;
    Matrix res(MATRIX_SIZE, MATRIX_SIZE);
    auto around = [](double a) {return a >= 0 ? int (a + 0.5) : int (a - 0.5);};
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            tmp = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                for (int l = 0; l < MATRIX_SIZE; l++) {
                    alpha = (k == 0 ? sqrt(1.0 / MATRIX_SIZE) : sqrt(2.0 / MATRIX_SIZE));
                    beta = (l == 0 ? sqrt(1.0 / MATRIX_SIZE) : sqrt(2.0 / MATRIX_SIZE));
                    tmp += alpha * beta * matrix[l][k] *
                            cos((2 * i + 1) * k * pi / ( 2 * MATRIX_SIZE)) *
                            cos((2 * j + 1) * l * pi / (2 * MATRIX_SIZE));
                }
            }
            res[i][j] = around(tmp);
        }
    }
    return res;
}

Matrix IDCT::DCT(Matrix &matrix) {
    const double pi = 3.141592654;
    double tmp = 0, alpha, beta;
    Matrix res(MATRIX_SIZE, MATRIX_SIZE);
    auto around = [](double a) {return a >= 0 ? int (a + 0.5) : int (a - 0.5);};
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            tmp = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                for (int l = 0; l < MATRIX_SIZE; l++) {
                    alpha = (k == 0 ? sqrt(1.0 / MATRIX_SIZE) : sqrt(2.0 / MATRIX_SIZE));
                    beta = (l == 0 ? sqrt(1.0 / MATRIX_SIZE) : sqrt(2.0 / MATRIX_SIZE));
                    tmp += alpha * beta * matrix[k][l] *
                           cos((2 * k + 1) * i * pi / ( 2 * MATRIX_SIZE)) *
                           cos((2 * l + 1) * j * pi / (2 * MATRIX_SIZE));
                }
            }
            res[i][j] = around(tmp);
        }
    }
    return res;
}