import numpy as np
from PIL import Image
import ImgSeq
from tqdm import tqdm
from math import sqrt
from queue import Queue
import constants

img_path = "./images/150_F_JC9.jpg"


def matrix_divide():
    img = Image.open(img_path)
    gray_img = img.convert('L')
    img_mat = np.float32(gray_img)
    mats = []

    height = img_mat.shape[0]
    width = img_mat.shape[1]
    x = 0
    y = 0
    for i in tqdm(range(8, height)):
        for j in range(8, width):
            item = ImgSeq.ImgSeq(x, y, img_mat[i - 8: i, j - 8: j])
            mats.append(item)
            y = y + 1
        x = x + 1
        y = 0
    return mats


def get_vector():
    mat_objs = matrix_divide()
    list.sort(mat_objs)
    length = len(mat_objs)
    dir1 = {(i, j): [] for i in range(-512, 512) for j in range(-512, 512)}
    dir2 = {(i, j): [] for i in range(-512, 512) for j in range(-512, 512)}
    for i in tqdm(range(1, length - 1)):
        dis = mat_objs[i] - mat_objs[i - 1]
        distance = sqrt(dis[0]**2 + dis[1]**2)
        if distance > 30 and mat_objs[i] == mat_objs[i - 1]:
            dir1[dis].append((mat_objs[i].x, mat_objs[i].y))
            dir2[dis].append((mat_objs[i - 1].x, mat_objs[i - 1].y))

    max_num = (-512, -512)
    for i in range(-512, 512):
        for j in range(-512, 512):
            if len(dir1[(i, j)]) > len(dir1[max_num]):
                max_num = (i, j)
    return max_num


def detect():

    img = Image.open(img_path)
    gray_img = img.convert('L')
    mat = np.asarray(img)
    img_mat = np.float32(gray_img)
    cover = np.zeros((512, 512, 3))

    vector = get_vector()

    height = img_mat.shape[0]
    width = img_mat.shape[1]
    x = 0
    y = 0

    for i in tqdm(range(8, height)):
        for j in range(8, width):
            move_pos = (x + vector[0], y + vector[1])
            if move_pos[0] < 0 or move_pos[0] > 504 or move_pos[1] < 0 or move_pos[1] > 504:
                y = y + 1
                continue
            item1 = ImgSeq.ImgSeq(x, y, img_mat[i - 8: i, j - 8: j])
            item2 = ImgSeq.ImgSeq(move_pos[0], move_pos[1],
                                  img_mat[move_pos[0]: move_pos[0] + 8,
                                  move_pos[1]: move_pos[1] + 8])
            if item1 == item2:
                for m in range(8):
                    for n in range(8):
                        cover[x + m][y + n] = mat[x + m][y + n]
                        cover[move_pos[0] + m][move_pos[1] + n] = mat[move_pos[0] + m][move_pos[1] + n]

            y = y + 1
        x = x + 1
        y = 0
    cover = Image.fromarray(np.uint8(cover))
    cover.show()


def add(item1, item2):
    return tuple(np.asarray(item1) + np.asarray(item2))


def detect_connect():
    img = Image.open(img_path)
    gray_img = img.convert('L')

    gray_mat = np.asarray(gray_img)
    mat = np.int32(img)
    img_mat = np.float32(gray_img)

    cover = np.zeros((512, 512, 3))

    start_pos = (-1, -1)
    max_count = -1

    connect = np.zeros((512, 512))
    vec = [[0, 1], [0, -1], [1, 0], [-1, 0]]
    vector = get_vector()
    print(vector)
    height = img_mat.shape[0]
    width = img_mat.shape[1]

    for i in tqdm(range(0, height - 8)):
        for j in range(width - 8):
            if connect[(i, j)] != 0:
                continue
            q = Queue()
            q.put((i, j))
            count = 0
            while not q.empty():
                front = q.get()
                x = front[0]
                y = front[1]
                if connect[front] != 0:
                    continue

                move_pos = add(front, vector)
                if move_pos[0] < 0 or move_pos[0] >= 504 or move_pos[1] < 0 or move_pos[1] >= 504:
                    continue
                if x < 0 or x >= 504 or y < 0 or y >= 504:
                    continue
                item1 = ImgSeq.ImgSeq(x, y, img_mat[x: x + 8, y: y + 8])
                item2 = ImgSeq.ImgSeq(move_pos[0], move_pos[1],
                                      img_mat[move_pos[0]: move_pos[0] + 8,
                                      move_pos[1]: move_pos[1] + 8])
                if item1 == item2:
                # if abs(gray_mat[front] - gray_mat[move_pos]) <= 15:
                    count = count + 1
                    connect[front] = 1
                    connect[move_pos] = 1
                else:
                    connect[front] = 2
                    connect[move_pos] = 2
                    continue
                for v in vec:
                    next_pos = add(front, v)
                    if 0 <= next_pos[0] < 512 and 0 <= next_pos[1] < 512:
                        q.put(next_pos)
            if count > max_count:
                max_count = count
                start_pos = (i, j)
    q = Queue()
    q.put(start_pos)
    print(start_pos)
    while not q.empty():
        front = q.get()
        move_pos = add(front, vector)
        if connect[front] != 1:
            continue
        cover[front] = mat[front]
        cover[move_pos] = mat[move_pos]
        connect[front] = 2
        connect[move_pos] = 2
        for v in vec:
            next_pos = add(front, v)
            q.put(next_pos)
    cover = Image.fromarray(np.uint8(cover))
    cover.show()
    cover.save("./results/{0}_eps{1}_q{2}.jpg".
               format(img_path[9: -4], constants.eps, constants.Q))


detect_connect()

