//
// Created by Decision on 2021/3/27.
//

#include "ZigZag.h"

Matrix ZigZag::func(const std::vector<int> &vec) {
    Matrix res(MATRIX_SIZE, MATRIX_SIZE);
    int _x = 0, _y = 0, dir = 0;
    int delta[][2] = {{0, 1}, {1, 0}, {1, -1}, {-1, 1}};

    for (int i : vec) {
        res[_x][_y] = i;
        _x += delta[dir][0];
        _y += delta[dir][1];
        if (dir == 0) {
            if (_x == 0) dir = 2;
            else dir = 3;
        }
        else if (dir == 1) {
            if (_y == 0) dir = 3;
            else dir = 2;
        }
        else if (dir == 2) {
            if (_y == 0) dir = (_x == MATRIX_SIZE - 1 ? 0 : 1);
            else if (_x == MATRIX_SIZE - 1) dir = 0;
        }
        else if (dir == 3) {
            if (_x == 0) dir = 0;
            else if (_y == MATRIX_SIZE - 1) dir = 1;
        }
    }
    return res;
}