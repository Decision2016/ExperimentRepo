import tkinter as tk
from tkinter import ttk
from tkinter.filedialog import askopenfilename
from PIL import Image, ImageTk
import threading
from DetectClass import Detect


class TKDetect(object):
    file_path: str

    def __init__(self):
        self.window = tk.Tk()
        self.window.style = ttk.Style()
        self.window.style.theme_use("vista")

        self.frame_control = tk.Frame(self.window, width=350)
        self.frame_control.grid(row=0, column=0)

        self.frame_pictures = tk.Frame(self.window, width=600)
        self.frame_pictures.grid(row=0, column=1)

        self.button_select = tk.Button(self.frame_control, text="选择文件", command=self.select_file_callback)
        self.button_submit = tk.Button(self.frame_control, text="进行检测", command=self.start_detect)
        self.button_select.grid(row=3, column=0, padx=10, pady=10)
        self.button_submit.grid(row=3, column=2, padx=10, pady=10)

        self.label_eps = tk.Label(self.frame_control, text='eps')
        self.label_eps.grid(row=0, column=0)
        self.label_dis = tk.Label(self.frame_control, text='distance')
        self.label_dis.grid(row=1, column=0)
        self.label_q = tk.Label(self.frame_control, text='Q')
        self.label_q.grid(row=2, column=0)
        self.label_info = tk.Label(self.frame_control)
        self.label_info.grid(row=4, columnspan=3)

        self.scale_eps = tk.Scale(self.frame_control, from_=0.5, to=100.0, digits=4, resolution=0.01, orient='horizontal')
        self.scale_eps.grid(row=0, column=1, columnspan=3)
        self.scale_eps.set(5)
        self.scale_distance = tk.Scale(self.frame_control, from_=1, to=512, orient='horizontal')
        self.scale_distance.grid(row=1, column=1, columnspan=3)
        self.scale_distance.set(30)
        self.scale_Q = tk.Scale(self.frame_control, from_=0.5, to=5.0, digits=3, resolution=0.01, orient='horizontal')
        self.scale_Q.grid(row=2, column=1, columnspan=3)
        self.scale_Q.set(1)

        self.canvas_origin = tk.Label(self.frame_pictures, bg='white', height=256, width=256)
        self.canvas_origin.grid(row=0, column=0)
        img = Image.open('./images/512x512.png')
        img = img.resize((256, 256))
        img_obj = ImageTk.PhotoImage(img)
        self.canvas_origin.configure(image=img_obj)
        self.canvas_origin.image = img_obj

        self.image_result = tk.Label(self.frame_pictures, bg='white', height=256, width=256)
        self.image_result.grid(row=0, column=1)
        self.image_result.configure(image=img_obj)
        self.image_result.image = img_obj

        self.progress_bar = ttk.Progressbar(self.window, orient='horizontal', length=700)
        self.progress_bar.grid(row=1, column=0, columnspan=2)
        self.file_path = None
        self.refresh()

    def instance(self):
        self.window.mainloop()

    def select_file_callback(self):
        self.file_path = askopenfilename()
        img = Image.open(self.file_path)
        img = img.resize((256, 256))
        img_obj = ImageTk.PhotoImage(img)
        self.canvas_origin.configure(image=img_obj)
        self.canvas_origin.image = img_obj

    def start_detect(self):
        detect = Detect(self.file_path, self.scale_eps.get(), self.scale_Q.get(), self.scale_distance.get())
        detect.target(self.progress_bar, self.image_result, self.label_info)
        th = threading.Thread(target=detect.detect_connect)
        th.setDaemon(True)
        th.start()

    def refresh(self):
        self.window.after(100, self.refresh)



window = TKDetect()
window.instance()