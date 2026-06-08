#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 100

struct Student {
    char id[15];
    char name[15];
    int math;
    int physics;
    int c;
    int total;
    int year;
    int class;
    int rankGrade;
    int rankClass;
};

/* 函数声明 */
int  read_file(struct Student stu[]);
void show_menu();
void calc_all(struct Student stu[], int studentCount);
void show_grade(struct Student stu[], int studentCount);
void show_class(struct Student stu[], int studentCount);
void search_name(struct Student stu[], int studentCount);
void search_range(struct Student stu[], int studentCount);
void save_file(struct Student stu[], int studentCount);
void search_single(struct Student stu[], int studentCount);

int main() {
    struct Student stu[MAX_STUDENT];
    int studentCount = 0;
    int choice;

    studentCount = read_file(stu);
    calc_all(stu, studentCount);

    while (1) {
        show_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: show_grade(stu, studentCount);   break;
            case 2: show_class(stu, studentCount);   break;
            case 3: search_name(stu, studentCount);  break;
            case 4: search_range(stu, studentCount); break;
            case 5: search_single(stu, studentCount); break;  
            case 0:
                save_file(stu, studentCount);
                printf("已保存排名到 score_rank.txt\n程序退出\n");
                return 0;
            default:
                printf("输入无效，请重新输入！\n");
        }
    }
}

int read_file(struct Student stu[]) {
    FILE *fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("打不开文件\n");
        return 0;
    }

    int stu_num = 0;
    while (stu_num < MAX_STUDENT) {
        if (fscanf(fp,"%s %s %d %d %d",stu[stu_num].id,stu[stu_num].name,&stu[stu_num].math,&stu[stu_num].physics,&stu[stu_num].c) != 5) 
        {
            break;
        }

        stu[stu_num].year  = (stu[stu_num].id[0] - '0') * 1000
                           + (stu[stu_num].id[1] - '0') * 100
                           + (stu[stu_num].id[2] - '0') * 10
                           + (stu[stu_num].id[3] - '0');
        stu[stu_num].class = (stu[stu_num].id[4] - '0');

        stu[stu_num].total     = 0;
        stu[stu_num].rankGrade = 0;
        stu[stu_num].rankClass = 0;

        stu_num++;
    }

    fclose(fp);
    printf("已查询到 %d 个学生\n", stu_num);
    return stu_num;
}

void show_menu() {
    printf("\n-----------------------\n");
    printf("1. 年级成绩\n");
    printf("2. 班级成绩查询\n");
    printf("3. 按姓名查询成绩\n");
    printf("4. 按总分分数段查询成绩\n");
    printf("5. 按单科分数降序查询成绩\n");
    printf("0. 退出\n");
    printf("-----------------------\n");
    printf("请输入你的选择（0-5）：");
}

void calc_all(struct Student stu[], int studentCount) {
    int i, j;

    for (i=0;i<studentCount; i++) 
    {
        stu[i].total=stu[i].math+stu[i].physics+stu[i].c;
    }
    for (i=0;i<studentCount;i++) 
    {
        int rank=1;
        for (j=0;j<studentCount; j++) 
        {
            if (stu[j].total>stu[i].total) rank++;
        }
        stu[i].rankGrade=rank;
    }

    for (i = 0; i < studentCount; i++) {
        int rank = 1;
        for (j = 0; j < studentCount; j++) {
            if (stu[j].class == stu[i].class && stu[j].total > stu[i].total)
                rank++;
        }
        stu[i].rankClass = rank;
    }

    long sum = 0;
    for (i = 0; i < studentCount; i++) sum += stu[i].total;
    printf("全年级平均总分：%.2f\n", (float)sum / studentCount);
}

static void sort_by_total_desc(struct Student arr[], int n) {
    int i, j;
    struct Student tmp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j].total < arr[j + 1].total) {
                tmp      = arr[j];
                arr[j]   = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void show_grade(struct Student stu[], int studentCount) {
    struct Student tmp[MAX_STUDENT];
    int i;
    for (i = 0; i < studentCount; i++) tmp[i] = stu[i];
    sort_by_total_desc(tmp, studentCount);
    printf("-------------------------------------------------------------------------------------\n");
    printf("%-8s %-6s %-12s %-12s %-6s %-6s %-6s %-6s %-8s %-8s\n","年级", "班级", "学号", "姓名", "数学", "物理", "C语言", "总分", "年级排名", "班级排名");
    printf("-------------------------------------------------------------------------------------\n");

    long sum = 0;
    for (i = 0; i < studentCount; i++) {
        printf("%-6d %-4d %-10s %-10s %-4d %-4d %-5d %-5d %-7d %-6d\n",tmp[i].year, tmp[i].class, tmp[i].id, tmp[i].name,tmp[i].math, tmp[i].physics, tmp[i].c, tmp[i].total,tmp[i].rankGrade, tmp[i].rankClass);
        sum += tmp[i].total;
    }
    printf("-------------------------------------------------------------------------------------\n");
    printf("年级平均总分：%.2f\n", (float)sum / studentCount);
}

void show_class(struct Student stu[], int studentCount) {
    int cls, i, cnt = 0;
    printf("请输入要查询的班级号：");
    scanf("%d", &cls);

    struct Student tmp[MAX_STUDENT];
    for (i = 0; i < studentCount; i++) {
        if (stu[i].class == cls) tmp[cnt++] = stu[i];
    }

    if (cnt == 0) {
        printf("无该班级学生数据\n");
        return;
    }

    sort_by_total_desc(tmp, cnt);

    printf("-------------------------------------------------------------------------------------\n");
    printf("%-8s %-6s %-12s %-12s %-6s %-6s %-6s %-6s %-8s %-8s\n","年级", "班级", "学号", "姓名", "数学", "物理", "C语言", "总分", "年级排名", "班级排名");
    printf("-------------------------------------------------------------------------------------\n");

    long sum = 0;
    for (i = 0; i < cnt; i++) {
        printf("%-6d %-4d %-10s %-10s %-4d %-4d %-4d %-5d %-8d %-6d\n",tmp[i].year, tmp[i].class, tmp[i].id, tmp[i].name,tmp[i].math, tmp[i].physics, tmp[i].c, tmp[i].total,tmp[i].rankGrade, tmp[i].rankClass);
        sum += tmp[i].total;
    }
    printf("-------------------------------------------------------------------------------------\n");
    printf("%d 班共 %d 人，班级平均总分：%.2f\n", cls, cnt, (float)sum / cnt);
}

void search_name(struct Student stu[], int studentCount) {
    char na[20];
    int i, find = 0;
    printf("输入需要查找的学生姓名：");
    scanf("%s", na);

    printf("-------------------------------------------------------------------------------------\n");
    printf("%-8s %-6s %-12s %-12s %-6s %-6s %-6s %-6s %-8s %-8s\n","年级", "班级", "学号", "姓名", "数学", "物理", "C语言", "总分", "年级排名", "班级排名");
    printf("-------------------------------------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++) {
        if (strcmp(stu[i].name, na) == 0) {
            find = 1;
            printf("%-6d %-4d %-10s %-10s %-4d %-4d %-4d %-5d %-8d %-6d\n",stu[i].year, stu[i].class, stu[i].id, stu[i].name,stu[i].math, stu[i].physics, stu[i].c, stu[i].total,stu[i].rankGrade, stu[i].rankClass);
        }
    }
    printf("-------------------------------------------------------------------------------------\n");
    if (find == 0) printf("未查询到姓名为 %s 的学生\n", na);
}

void search_range(struct Student stu[], int studentCount) {
    int min_score, max_score, found = 0, i;

    if (studentCount == 0) {
        printf("暂无学生数据，请先读取文件！\n");
        return;
    }

    printf("请输入最低总分：");
    scanf("%d", &min_score);
    printf("请输入最高总分：");
    scanf("%d", &max_score);

    printf("-------------------------------------------------------------------------------------\n");
    printf("%-8s %-6s %-12s %-12s %-6s %-6s %-6s %-6s %-8s %-8s\n","年级", "班级", "学号", "姓名", "数学", "物理", "C语言", "总分", "年级排名", "班级排名");
    printf("-------------------------------------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++) {
        if (stu[i].total >= min_score && stu[i].total <= max_score) {
            printf("%-6d %-4d %-10s %-10s %-4d %-4d %-4d %-5d %-8d %-6d\n",stu[i].year, stu[i].class, stu[i].id, stu[i].name,stu[i].math, stu[i].physics, stu[i].c, stu[i].total,stu[i].rankGrade, stu[i].rankClass);
            found++;
        }
    }
    printf("-------------------------------------------------------------------------------------\n");

    if (found == 0)
        printf("没有找到总分在 %d 到 %d 之间的学生。\n", min_score, max_score);
    else
        printf("共查询到 %d 名学生。\n", found);
}

void save_file(struct Student stu[], int studentCount) {
    struct Student tmp[MAX_STUDENT];
    int i;
    for (i = 0; i < studentCount; i++) tmp[i] = stu[i];
    sort_by_total_desc(tmp, studentCount);

    FILE *fp = fopen("score_rank.txt", "w");
    if (fp == NULL) {
        printf("错误：无法创建或打开 score_rank.txt 文件！\n");
        return;
    }

    printf("-------------------------------------------------------------------------------------\n");
    printf("%-8s %-6s %-12s %-12s %-6s %-6s %-6s %-6s %-8s %-8s\n","年级", "班级", "学号", "姓名", "数学", "物理", "C语言", "总分", "年级排名", "班级排名");
    printf("-------------------------------------------------------------------------------------\n");

    long sum = 0;
    for (i = 0; i < studentCount; i++) {
        fprintf(fp, "%-6d %-4d %-10s %-10s %-4d %-4d %-4d %-5d %-8d %-6d\n",tmp[i].year, tmp[i].class, tmp[i].id, tmp[i].name,tmp[i].math, tmp[i].physics, tmp[i].c, tmp[i].total,tmp[i].rankGrade, tmp[i].rankClass);
        sum += tmp[i].total;
    }
    fprintf(fp, "-------------------------------------------------------------------------------------\n");
    fprintf(fp, "全年级共 %d 人，平均总分：%.2f\n", studentCount, (float)sum / studentCount);

    fclose(fp);
    printf("成绩排名已成功保存到 score_rank.txt\n");
}

void search_single(struct Student stu[], int studentCount) {
    char target_id[15];
    int found = 0, i;

    if (studentCount == 0) {
        printf("暂无学生数据，请先读取文件！\n");
        return;
    }

    printf("请输入要查询的学生学号：");
    scanf("%s", target_id);

    printf("-------------------------------------------------------------------------------------\n");
    printf("%-8s %-6s %-12s %-12s %-6s %-6s %-6s %-6s %-8s %-8s\n","年级", "班级", "学号", "姓名", "数学", "物理", "C语言", "总分", "年级排名", "班级排名");
    printf("-------------------------------------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++) {
        if (strcmp(stu[i].id, target_id) == 0) {
            printf("%-6d %-4d %-10s %-10s %-4d %-4d %-4d %-5d %-8d %-6d\n",stu[i].year, stu[i].class, stu[i].id, stu[i].name,stu[i].math, stu[i].physics, stu[i].c, stu[i].total,stu[i].rankGrade, stu[i].rankClass);
            found = 1;
            break;
        }
    }
    printf("-------------------------------------------------------------------------------------\n");

    if (found == 0) printf("没有找到学号为 %s 的学生。\n", target_id);
}
