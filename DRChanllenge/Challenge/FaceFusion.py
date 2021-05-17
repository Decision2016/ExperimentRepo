import dlib
import numpy as np
import cv2
import time
import os
from functions import transformation_points, morph_img, tran_src, merge_img


def get_points(image):
    detector = dlib.get_frontal_face_detector()

    predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")
    dets = detector(image, 1)
    shape = predictor(image, dets[0])

    points = []
    for item in shape.parts():
        points.append((item.x, item.y))

    matrix_list = np.matrix(points)
    area = dets[0]
    return matrix_list, points, area


def fusion():
    # 人脸source图片，需要融合另外一张人脸到达的另外一张图片
    src_img = cv2.imread('./images/image.jpg')
    # 人脸origin图片，取材的人脸
    dst_img = cv2.imread('./images/test001.jpg')

    # 获取矩阵以及关键点
    src_matrix, src_points, _ = get_points(src_img)
    dst_matrix, dst_points, _ = get_points(dst_img)

    # 通过凸包提取人脸蒙版
    dst_img = transformation_points(src_img, src_matrix, dst_img, dst_matrix)
    dst_matrix, dst_points, _ = get_points(dst_img)

    # 融合，得到具有两张人脸特征的图像
    dst_img = morph_img(src_img, src_points, dst_img, dst_points)

    morph_file = 'images/' + str(int(time.time() * 1000)) + '.jpg'
    cv2.imwrite(morph_file, dst_img)
    dst_img = cv2.imread(morph_file)

    dst_matrix, dst_points, area = get_points(dst_img)
    face_area = [area.left(), area.top(), area.right()-area.left(), area.bottom()-area.top()]

    # 将融合后的图片“贴回”source图片
    src_img = tran_src(src_img, src_points, dst_points, face_area)
    dst_img = merge_img(src_img, dst_img, dst_matrix, dst_points)

    cv2.imwrite('./images/result.jpg', dst_img)
    os.remove(morph_file)

fusion()