import numpy as np
import cv2
from scipy.spatial import Delaunay, ConvexHull

FACE_POINTS = list(range(0, 68))
JAW_POINTS = list(range(0, 19))
LEFT_EYE_POINTS = list(range(19, 29))
LEFT_BROW_POINTS = list(range(29, 37))
MOUTH_POINTS = list(range(37, 55))
NOSE_POINTS = list(range(55, 65))
RIGHT_EYE_POINTS = list(range(65, 75))
RIGHT_BROW_POINTS = list(range(75, 83))

LEFT_FACE = list(range(0, 10)) + list(range(29, 34))
RIGHT_FACE = list(range(9, 19)) + list(range(63, 68))

JAW_END = 19
FACE_START = 0
FACE_END = 83

OVERLAY_POINTS = [
    LEFT_FACE,
    RIGHT_FACE,
    JAW_POINTS,
]


def affine_transform(src, src_tri, dst_tri, size):
    warp_mat = cv2.getAffineTransform(np.float32(src_tri), np.float32(dst_tri))

    dst = cv2.warpAffine(src, warp_mat, (size[0], size[1]),
                         None,
                         flags=cv2.INTER_LINEAR,
                         borderMode=cv2.BORDER_REFLECT_101)

    return dst


def affine_triangle(src, dst, t_src, t_dst):
    r1 = cv2.boundingRect(np.float32([t_src]))
    r2 = cv2.boundingRect(np.float32([t_dst]))

    t1_rect = []
    t2_rect = []
    t2_rect_int = []

    for i in range(0, 3):
        t1_rect.append((t_src[i][0] - r1[0], t_src[i][1] - r1[1]))
        t2_rect.append((t_dst[i][0] - r2[0], t_dst[i][1] - r2[1]))
        t2_rect_int.append((t_dst[i][0] - r2[0], t_dst[i][1] - r2[1]))

    mask = np.zeros((r2[3], r2[2], 3), dtype=np.float32)
    cv2.fillConvexPoly(mask, np.int32(t2_rect_int), (1.0, 1.0, 1.0), 16, 0)

    img1_rect = src[r1[1]:r1[1] + r1[3], r1[0]:r1[0] + r1[2]]

    size = (r2[2], r2[3])

    img2_rect = affine_transform(img1_rect, t1_rect, t2_rect, size)
    img2_rect = img2_rect * mask

    dst[r2[1]:r2[1] + r2[3], r2[0]:r2[0] + r2[2]] = dst[r2[1]:r2[1] + r2[3], r2[0]:r2[0] + r2[2]] * (
        (1.0, 1.0, 1.0) - mask)

    dst[r2[1]:r2[1] + r2[3], r2[0]:r2[0] + r2[2]] = dst[r2[1]:r2[1] + r2[3], r2[0]:r2[0] + r2[2]] + img2_rect


def morph_triangle(src, dst, img, t_src, t_dst, t, alpha):
    r1 = cv2.boundingRect(np.float32([t_src]))
    r2 = cv2.boundingRect(np.float32([t_dst]))
    r = cv2.boundingRect(np.float32([t]))

    t1_rect = []
    t2_rect = []
    t_rect = []

    for i in range(0, 3):
        t_rect.append(((t[i][0] - r[0]), (t[i][1] - r[1])))
        t1_rect.append(((t_src[i][0] - r1[0]), (t_src[i][1] - r1[1])))
        t2_rect.append(((t_dst[i][0] - r2[0]), (t_dst[i][1] - r2[1])))

    mask = np.zeros((r[3], r[2], 3), dtype=np.float32)
    cv2.fillConvexPoly(mask, np.int32(t_rect), (1.0, 1.0, 1.0), 16, 0)

    img1_rect = src[r1[1]:r1[1] + r1[3], r1[0]:r1[0] + r1[2]]
    img2_rect = dst[r2[1]:r2[1] + r2[3], r2[0]:r2[0] + r2[2]]

    size = (r[2], r[3])

    warp_img1 = affine_transform(img1_rect, t1_rect, t_rect, size)
    warp_img2 = affine_transform(img2_rect, t2_rect, t_rect, size)

    img_rect = (1.0 - alpha) * warp_img1 + alpha * warp_img2

    img[r[1]:r[1] + r[3], r[0]:r[0] + r[2]] = img[r[1]:r[1] + r[3], r[0]:r[0] + r[2]] * (1 - mask) + img_rect * mask


# 泊松融合
def morph_img(src_img, src_points, dst_img, dst_points, alpha=0.5):
    morph_points = []

    src_img = src_img.astype(np.float32)
    dst_img = dst_img.astype(np.float32)

    res_img = np.zeros(src_img.shape, src_img.dtype)

    for i in range(0, len(src_points)):
        x = (1 - alpha) * src_points[i][0] + alpha * dst_points[i][0]
        y = (1 - alpha) * src_points[i][1] + alpha * dst_points[i][1]
        morph_points.append((x, y))

    triangles = Delaunay(morph_points).simplices

    for item in triangles:
        t1 = []
        t2 = []
        t = []

        for j in range(0, 3):
            t1.append(src_points[item[j]])
            t2.append(dst_points[item[j]])
            t.append(morph_points[item[j]])

        morph_triangle(src_img, dst_img, res_img, t1, t2, t, alpha)

    return res_img


# 添加人脸矩阵的对齐点
def matrix_rectangle(left, top, width, height):
    pointer = [
        (left, top),
        (left + width / 2, top),
        (left + width - 1, top),
        (left + width - 1, top + height / 2),
        (left, top + height / 2),
        (left, top + height - 1),
        (left + width / 2, top + height - 1),
        (left + width - 1, top + height - 1)
    ]

    return pointer


def tran_src(src_img, src_points, dst_points, face_area=None):
    jaw = 19
    matrix_rectangle(face_area[0], face_area[1], face_area[2], face_area[3])
    dst_list = dst_points \
               + matrix_rectangle(face_area[0], face_area[1], face_area[2], face_area[3]) \
               + matrix_rectangle(0, 0, src_img.shape[1], src_img.shape[0])

    src_list = src_points \
               + matrix_rectangle(face_area[0], face_area[1], face_area[2], face_area[3]) \
               + matrix_rectangle(0, 0, src_img.shape[1], src_img.shape[0])

    jaw_points = []

    for i in range(0, jaw):
        jaw_points.append(dst_list[i])
        jaw_points.append(src_list[i])

    warp_jaw = cv2.convexHull(np.array(jaw_points), returnPoints=False)
    warp_jaw = warp_jaw.tolist()

    for i in range(0, len(warp_jaw)):
        warp_jaw[i] = warp_jaw[i][0]

    warp_jaw.sort()

    if len(warp_jaw) <= jaw:
        dst_list = dst_list[jaw - len(warp_jaw):]
        src_list = src_list[jaw - len(warp_jaw):]
        for i in range(0, len(warp_jaw)):
            dst_list[i] = jaw_points[int(warp_jaw[i])]
            src_list[i] = jaw_points[int(warp_jaw[i])]
    else:
        for i in range(0, jaw):
            if len(warp_jaw) > jaw and warp_jaw[i] == 2 * i and warp_jaw[i + 1] == 2 * i + 1:
                warp_jaw.remove(2 * i)

            dst_list[i] = jaw_points[int(warp_jaw[i])]

    triangles = Delaunay(dst_list).simplices

    res_img = np.zeros(src_img.shape, dtype=src_img.dtype)

    for item in triangles:
        t_src = []
        t_dst = []

        for j in range(0, 3):
            t_src.append(src_list[item[j]])
            t_dst.append(dst_list[item[j]])

        affine_triangle(src_img, res_img, t_src, t_dst)

    return res_img


# 将融合完成的人脸拼接到原图片
def merge_img(src_img, dst_img, dst_matrix, dst_points, blur_detail_x=None, blur_detail_y=None, mat_multiple=None):
    face_mask = np.zeros(src_img.shape, dtype=src_img.dtype)

    for group in OVERLAY_POINTS:
        cv2.fillConvexPoly(face_mask, cv2.convexHull(dst_matrix[group]), (255, 255, 255))

    r = cv2.boundingRect(np.float32([dst_points[:FACE_END]]))

    center = (r[0] + int(r[2] / 2), r[1] + int(r[3] / 2))

    if mat_multiple:
        mat = cv2.getRotationMatrix2D(center, 0, mat_multiple)
        face_mask = cv2.warpAffine(face_mask, mat, (face_mask.shape[1], face_mask.shape[0]))

    if blur_detail_x and blur_detail_y:
        face_mask = cv2.blur(face_mask, (blur_detail_x, blur_detail_y), center)

    return cv2.seamlessClone(np.uint8(dst_img), src_img, face_mask, center, cv2.NORMAL_CLONE)


# 仿射变换，将取材图片中的人脸与目标图片中的人脸对齐
def transformation_points(src_img, src_points, dst_img, dst_points):
    src_points = src_points.astype(np.float64)
    dst_points = dst_points.astype(np.float64)

    c1 = np.mean(src_points, axis=0)
    c2 = np.mean(dst_points, axis=0)

    src_points -= c1
    dst_points -= c2

    s1 = np.std(src_points)
    s2 = np.std(dst_points)

    src_points /= s1
    dst_points /= s2

    u, s, vt = np.linalg.svd(src_points.T * dst_points)
    r = (u * vt).T

    m = np.vstack([np.hstack(((s2 / s1) * r, c2.T - (s2 / s1) * r * c1.T)), np.matrix([0., 0., 1.])])

    output = cv2.warpAffine(dst_img, m[:2],
                            (src_img.shape[1], src_img.shape[0]),
                            borderMode=cv2.BORDER_TRANSPARENT,
                            flags=cv2.WARP_INVERSE_MAP)

    return output