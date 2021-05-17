# DataRecoverExp

## 目录结构

该仓库为数据取证实验仓库，目录结构如下

```
DataRecoverExp
├── Challenge                                       // 擂台挑战相关代码—人脸融合
│   ├── FaceFusion.py                               // 人脸融合主程序
│   ├── functions.py                                // 相关函数
│   ├── images                                      // 图像目录
│   ├── requirements.txt                            // python所需包文件
│   ├── shape_predictor_68_face_landmarks.dat       // dlib数据集
├── DiskImage
│   └── dfrws-2006-challenge.raw                    // 碎片磁盘镜像
├── PictureDetect                                   // 图像取证代码
│   ├── DetectClass.py                              // 取证相关函数
│   ├── ImgSeq.py                                   // 定义图像矩阵结构
│   ├── TKDetect.py                                 // 图形化界面代码，主程序
│   ├── clickShow.py                                   
│   ├── constants.py                                // 常量定义
│   ├── detect.py
│   ├── images
│   ├── results
│   ├── requirements.txt                             // python所需包文件
├── Project                                          // 文件雕刻目录
│   ├── CMakeLists.txt
│   ├── DEVELOPING.md
│   ├── cmake-build-debug
│   ├── images
│   ├── include
│   │   ├── MCU.h
│   │   ├── Parser.h                                  // JPEG解码器&哈夫曼扫描
│   │   ├── Recover.h
│   │   ├── constants.h                               // 常量
│   │   ├── structs                                   // 相关结构
│   │   ├── typedef.h
│   │   └── utils
│   ├── main.cpp
│   ├── source
│   │   ├── MCU.cpp
│   │   ├── Parser.cpp
│   │   ├── Recover.cpp
│   │   ├── structs
│   │   └── utils
│   └── test
│       ├── CMakeLists.txt
│       └── zigzag_test.cpp
├── RecoverFiles                                         // 单元程序输出目录
│   └── pics
├── RecoverFragmentFiles                                 // 单元程序输出目录
│   └── pics
├── RecoverUnits                                         // 雕刻实验的html和jpeg恢复的单元程序
├── Recovered
└── SGProject                                            // 擂台挑战—隐写
    ├── CMakeLists.txt
    ├── cmake-build-debug
    ├── images
    ├── include
    ├── main.cpp
    └── source
```

## 运行

### 人脸融合&图像取证

人脸融合及图像取证代码均为Python代码编写，版本号3.6

所需要安装的包已经通过pip指令输出到`requirements.txt`，在运行之前需要运行指令`pip install -r requirements.txt`或`pip3 install -r requirements.txt`进行安装依赖后进行运行

人脸融合目录中主程序位于`FacaFusion.py`程序文件

图像取证目录中主程序位于`TKDetect.py`程序文件

### 文件雕刻

文件雕刻单元文件位于`RecoverUnits `目录，该部分程序可以直接在C++11及以上版本进行运行，文件输出目录在`RecoverFiles `及`RecoverFragmentFiles `中，图片需要保证存在子目录`pic`

工程目录为`Project `，当前该工程仅仅完成了通过哈夫曼编码进行扫描，并且由于哈夫曼编码的容错性较高，不能保证扫描到的位置精准，所以后续的恢复没有实现

`Project`和`SGProject`目录代码编译均需要通过CMakelist进行构建，或者直接通过CLion加载后运行