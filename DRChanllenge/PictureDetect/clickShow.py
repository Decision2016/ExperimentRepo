import os
import cv2
import random
import numpy as np


def draw_margin(event, y, x, flags, param):
    mat = np.asarray(param[0])
    if event == cv2.EVENT_LBUTTONDOWN:
        print(x, y, mat[x][y])
        print(x + 127, y + 257, mat[x + 127][y + 257])
        param[0][x][y] = 255
        param[0][x + 127][y + 257] = 255
        cv2.imshow("src", param[0])
    if event == cv2.EVENT_RBUTTONDOWN:
        cv2.destroyAllWindows()


def file_edit(file_name):
    img = cv2.imread(file_name, 0)
    cv2.imshow("src", img)
    cv2.setMouseCallback("src", draw_margin, (img, file_name))
    cv2.waitKey(0)

file_edit( "./images/184_F_JC9.jpg")