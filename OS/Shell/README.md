# OS实验1——任务调度管理器

## 目录结构

```
Shell
│  .gitignore                   // github传输忽略文件
│  CMakeLists.txt               // CMake文件
│  main.cpp                     // 主函数
│  README.md                    // 说明文件
├─header                        // 头文件
│      contants.h               // 定义常量
│      LinkList.h               // 前期构思过程中考虑使用的类，后面废弃后使用了Queue
│      PCB.h                    // PCB类定义
│      Queue.h                  // 使用链表完成的Queue类
│      Shell.h                  // Shell主类，程序的主体
│      Utils.h                  // 一些小工具的定义
└─source                        // 一系列类的实现文件
        LinkList.cpp
        PCB.cpp
        Queue.cpp
        Shell.cpp
        Utils.cpp
```

## Shell流程

> 如果看不到图片请直接访问图片或使用Typora等Markdown程序打开该文件

![流程图](.\images\流程图.png)