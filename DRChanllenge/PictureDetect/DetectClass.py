import numpy as np
from PIL import Image, ImageDraw, ImageTk
import ImgSeq
from math import sqrt
from queue import Queue


class Detect(object):
    img_path: str
    Q: float
    eps: float
    distance: float

    def __init__(self, _path, _eps, _q, _dis):
        self.img_path = _path
        self.Q = _q
        self.eps = _eps
        self.distance = _dis
        self.pb = None
        self.image_result = None
        self.label = None

    @staticmethod
    def add(item1, item2):
        return tuple(np.asarray(item1) + np.asarray(item2))

    def target(self, progress_bar, result_pic, label):
        self.pb = progress_bar
        self.image_result = result_pic
        self.label = label

    def matrix_divide(self):
        self.label.configure(text='开始分割矩阵')
        img = Image.open(self.img_path)
        gray_img = img.convert('L')
        img_mat = np.float32(gray_img)
        mats = []

        height = img_mat.shape[0]
        width = img_mat.shape[1]
        x = 0
        y = 0
        for i in range(8, height):
            self.pb['value'] = i / height * 100
            for j in range(8, width):
                item = ImgSeq.ImgSeq(x, y, img_mat[i - 8: i, j - 8: j], self.Q, self.eps)
                mats.append(item)
                y = y + 1
            x = x + 1
            y = 0
        self.pb['value'] = 0
        self.label.configure(text='矩阵分割完成，排序中...')
        return mats

    def get_vector(self):
        mat_objs = self.matrix_divide()
        list.sort(mat_objs)
        length = len(mat_objs)
        dir1 = {(i, j): [] for i in range(-512, 512) for j in range(-512, 512)}
        dir2 = {(i, j): [] for i in range(-512, 512) for j in range(-512, 512)}
        self.label.configure(text='排序完成，进行相似度检测...')
        for i in range(1, length - 1):
            self.pb['value'] = i / length * 100
            dis = mat_objs[i] - mat_objs[i - 1]
            distance = sqrt(dis[0] ** 2 + dis[1] ** 2)
            if distance > self.distance and mat_objs[i] == mat_objs[i - 1]:
                dir1[dis].append((mat_objs[i].x, mat_objs[i].y))
                dir2[dis].append((mat_objs[i - 1].x, mat_objs[i - 1].y))

        max_num = (-512, -512)
        for i in range(-512, 512):
            for j in range(-512, 512):
                if len(dir1[(i, j)]) > len(dir1[max_num]):
                    max_num = (i, j)
        self.pb['value'] = 0
        self.label.configure(text='正在遍历获取区块...')
        return max_num

    def detect_connect(self):
        img = Image.open(self.img_path)
        gray_img = img.convert('L')

        gray_mat = np.asarray(gray_img)
        mat = np.int32(img)
        img_mat = np.float32(gray_img)

        cover = np.zeros((512, 512, 3))

        start_pos = (-1, -1)
        max_count = -1

        connect = np.zeros((512, 512))
        vec = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        vector = self.get_vector()
        height = img_mat.shape[0]
        width = img_mat.shape[1]

        for i in range(0, height - 8):
            # show progress
            self.pb['value'] = i / height * 100
            for j in range(width - 8):
                if connect[(i, j)] != 0:
                    continue
                q = Queue()
                # put position to queue
                q.put((i, j))
                count = 0
                while not q.empty():
                    front = q.get()
                    x = front[0]
                    y = front[1]
                    if connect[front] != 0:
                        continue


                    # add vector and position
                    move_pos = self.add(front, vector)
                    if move_pos[0] < 0 or move_pos[0] >= 504 or move_pos[1] < 0 or move_pos[1] >= 504:
                        continue
                    if x < 0 or x >= 504 or y < 0 or y >= 504:
                        continue
                    item1 = ImgSeq.ImgSeq(x, y, img_mat[x: x + 8, y: y + 8], self.Q, self.eps)
                    item2 = ImgSeq.ImgSeq(move_pos[0], move_pos[1],
                                          img_mat[move_pos[0]: move_pos[0] + 8,
                                          move_pos[1]: move_pos[1] + 8], self.Q, self.eps)

                    # check item similar and sign position
                    if item1 == item2:
                        count = count + 1
                        connect[front] = 1
                        connect[move_pos] = 1
                    else:
                        connect[front] = 2
                        connect[move_pos] = 2
                        continue
                    for v in vec:
                        next_pos = self.add(front, v)
                        if 0 <= next_pos[0] < 512 and 0 <= next_pos[1] < 512:
                            q.put(next_pos)
                if count > max_count:
                    max_count = count
                    start_pos = (i, j)
        q = Queue()
        q.put(start_pos)
        # draw connecting block on picture
        while not q.empty():
            front = q.get()
            move_pos = self.add(front, vector)
            if connect[front] != 1:
                continue
            cover[front] = mat[front]
            cover[move_pos] = mat[move_pos]
            connect[front] = 2
            connect[move_pos] = 2
            for v in vec:
                next_pos = self.add(front, v)
                q.put(next_pos)
        cover = Image.fromarray(np.uint8(cover))
        cover = cover.resize((256, 256))
        img_obj = ImageTk.PhotoImage(cover)

        self.pb['value'] = 0
        self.image_result.configure(image=img_obj)
        self.image_result.image = img_obj
