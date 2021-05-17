
import cv2
import numpy as np
from math import sqrt
import constants


class ImgSeq(object):
    mat: list
    seq: list
    x: int
    y: int
    eps: float
    Q: float

    table = [
        [16, 11, 10, 16, 24, 40, 51, 61],
        [12, 12, 14, 19, 26, 58, 60, 55],
        [14, 13, 16, 24, 40, 57, 69, 56],
        [14, 17, 22, 29, 51, 87, 80, 62],
        [18, 22, 37, 56, 68, 109, 103, 77],
        [24, 35, 55, 64, 81, 104, 113, 92],
        [49, 64, 78, 87, 103, 121, 120, 101],
        [72, 92, 95, 98, 112, 100, 103, 99],
    ]

    def __init__(self, _x, _y, _mat, _q=constants.Q, _eps=constants.eps):
        self.x = _x
        self.y = _y
        self.Q = _q
        self.eps = _eps
        self.mat = np.int32(np.round(np.int32(cv2.dct(_mat)) / self.Q /ImgSeq.table))
        self.seq = []
        self.zigzag()

    def __lt__(self, other):
        for i in range(0, 64):
            if self.seq[i] == other.seq[i]:
                continue
            return self.seq[i] < other.seq[i]
        return True

    def __gt__(self, other):
        for i in range(0, 64):
            if self.seq[i] == other.seq[i]:
                continue
            return self.seq[i] > other.seq[i]
        return True

    def __eq__(self, other):
        for i in range(0, 64):
            if abs(self.seq[i] - other.seq[i]) <= self.eps:
                continue
            else:
                return False
        return True

    def __sub__(self, other):
        return (self.x - other.x, self.y - other.y)

    def zigzag(self):
        x = 0
        y = 0
        dir = 0
        delta = [
            [0, 1],
            [1, 0],
            [1, -1],
            [-1, 1]
        ]

        for i in range(0, 64):
            self.seq.append(self.mat[x][y])
            x += delta[dir][0]
            y += delta[dir][1]

            if dir == 0:
                dir = 2 if x == 0 else 3
            elif dir == 1:
                dir = 3 if y == 0 else 2
            elif dir == 2:
                if y == 0:
                    dir = 0 if x == 7 else 1
                elif x == 7:
                    dir = 0
            elif dir == 3:
                if x == 0:
                    dir = 0
                elif y == 7:
                    dir = 1
