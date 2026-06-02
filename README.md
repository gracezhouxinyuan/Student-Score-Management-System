# Student-Score-Management-System

## 01 项目介绍

本项目是一个基于 C 语言实现的"学生成绩管理系统"。

程序从 `score.txt` 读取学生成绩数据（学号、姓名、数学、物理、C语言成绩），自动计算总分和排名，支持按年级排序、班级排序、姓名查询、成绩段查询，并将排名结果保存到 `score_rank.txt` 文件中。

## 02 核心函数说明

1. `void read_file();`
   功能：从 `score.txt` 读取学生信息到结构体数组 `stu`，更新 `studentCount`。

2. `void calc_all();`
   功能：计算所有学生的总分、年级排名、班级排名。

3. `int str_to_int(char *str, int i, int n);`
   功能：将字符串从第 `i` 位到第 `n` 位转换为整数，用于解析学号。

4. `void show_grade();`
   功能：显示全年级成绩信息，按总分从大到小排序，显示年级排名和班级排名，计算平均分。

5. `void show_class();`
   功能：按班级查询显示成绩，按总分从大到小排序，计算班级平均分。

6. `void search_name();`
   功能：按姓名查询并显示学生的成绩信息。

7. `void search_range();`
   功能：查询指定总分段内的学生成绩信息。

8. `void search_single();`
   功能：额外功能：单科最高分排名或其他增强功能。

9. `void save_file();`
   功能：将学生的总分、年级排名、班级排名等信息保存到 `score_rank.txt`。

10. `void show_menu();`
    功能：显示菜单并返回用户输入的功能编号。

11. `int main();`
    功能：主控流程，初始化数据并处理用户交互。

## 03 项目目录结构

下载后推荐保持如下结构：

```text
project-root/
├── score.c
└── score.txt
```
