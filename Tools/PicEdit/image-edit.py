import os
import cv2
import random


def file_names_get():
    res = []
    for files in os.walk("./images"):
        for file in files[2]:
            try:
                splitext = os.path.splitext(file)
                if splitext[1] == '.png':
                    res.append(file)
            except IndexError:
                pass
    return res


def draw_margin(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        choose_red = bool(random.getrandbits(1))
        if choose_red:
            float_photo = cv2.imread("./floats/red_float.png")
        else:
            float_photo = cv2.imread("./floats/none_float.png")
        for i in range(0, 60):
            for j in range(0, 120):
                param[0][y + i, x + j] = float_photo[i, j]
        cv2.imshow("src", param[0])
    if event == cv2.EVENT_RBUTTONDOWN:
        cv2.imwrite(param[1], param[0])
        cv2.destroyAllWindows()


def file_edit(file_name):
    img = cv2.imread(file_name)

    cv2.imwrite(file_name, img)
    cv2.imshow("src", img)
    cv2.setMouseCallback("src", draw_margin, (img, file_name))
    cv2.waitKey(0)


files = file_names_get()
for file in files:
    file_edit("./images/" + file)
