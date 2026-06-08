#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 100

struct Student{
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

struct Student stu[MAX_STUDENT];
int studentCount = 0;


int str_to_int(char *str, int i, int n);


void read_file();
void show_menu();
void calc_all();
void show_grade();
void show_class();
void search_name();
void search_range();
void save_file();
void search_single();   

int main() {
    int choice;
    read_file();
    calc_all();
    while (1) {
        show_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: show_grade();    break;
            case 2: show_class();    break;
            case 3: search_name();   break;
            case 4: search_range();  break;
            case 5: search_single(); break;   /* 加分功能 */
            case 0:
                save_file();
                printf("已保存排名到 score_rank.txt\n程序退出\n");
                return 0;
            default:
                printf("输入无效，请重新输入！\n");
        }
    }
}

int str_to_int(char *str, int i, int n) {
    int dig = 0;
    for (; i <= n; i++)
        dig = dig * 10 + (str[i] - '0');
    return dig;
}

void read_file() {
FILE*fp=fopen("score.txt","r");
    if(fp==NULL){
        printf("打不开文件\n");
        return;
    }

    int stu_num=0;
    while(stu_num<MAX_STUDENT){
        if(fscanf(fp,"%s %s %d %d %d",
            stu[stu_num].id,
            stu[stu_num].name,
            &stu[stu_num].math,
            &stu[stu_num].physics,
            &stu[stu_num].class)!=5){
            break;
        }

        stu[stu_num].year=(stu[stu_num].id[0]-'0')*1000+
            (stu[stu_num].id[1]-'0')*100+
            (stu[stu_num].id[2]-'0')*10+
            (stu[stu_num].id[3]-'0');

        stu[stu_num].class=(stu[stu_num].id[4]-'0')*10+
        (stu[stu_num].id[5]-'0');

        stu[stu_num].total=0;
        stu[stu_num].rankGrade=0;
        stu[stu_num].rankClass=0;

        stu_num++;
    }

    studentCount = stu_num;
    fclose(fp);
    printf("读了%d个学生\n",stu_num);
}

void show_menu() {
    printf("\n=====================\n");
    printf("1.年级成绩\n");
    printf("2.班级成绩查询\n");
    printf("3.按姓名查询成绩\n");
    printf("4.按总分分数段查询成绩\n");
    printf("5.按单科分数降序查询成绩\n");
    printf("0.退出\n");
    printf("=====================\n");
    printf("选哪个：");
}

void calc_all() 
{
    if (studentCount == 0) {
        printf("还没读数据，先执行1\n");
        return;
    }

    int sum = 0, i = 0;
    for (i = 0; i < studentCount; i++) {
        stu[i].total = stu[i].math + stu[i].physics + stu[i].c;
        sum += stu[i].total;
    }

    float ave = (float)sum / studentCount;
    printf("全年级总分：%d\n", sum);
    printf("全年级平均：%.2f\n", ave);
}

void show_grade() {
    int i;
    printf("========全年级成绩排名========\n");
    printf("年级 班级 学号 姓名 数学 物理 C语言 总分 年级排名 班排名\n");
    for(i=0;i<studentCount;i++)
    {
        printf("%d  %d  %s %s %d %d %d %d %d %d\n",
        stu[i].year,stu[i].class,stu[i].id,stu[i].name,
        stu[i].math,stu[i].physics,stu[i].c,stu[i].total,
        stu[i].rankGrade,stu[i].rankClass);
}


}

void show_class() 
{   
    int cls,i,flag=0;
    printf("请输入要查询的班级号：");
    scanf("%d",&cls);
    printf("=====%d班成绩=====\n",cls);
    printf("年级 班级 学号 姓名 数学 物理 C语言 总分 年级排名 班排名\n");
    for(i=0;i<studentCount;i++)
    {
        if(stu[i].class==cls)
        {
            flag=1;
            printf("%d  %d  %s %s %d %d %d %d %d %d\n",
            stu[i].year,stu[i].class,stu[i].id,stu[i].name,
            stu[i].math,stu[i].physics,stu[i].c,stu[i].total,
            stu[i].rankGrade,stu[i].rankClass);
        }
    }
    if(flag==0)
        printf("无该班级学生数据\n");


}

void search_name() {
    char na[20];
    int i,find=0;
    printf("输入需要查找的学生姓名：");
    scanf("%s",na);
    printf("年级 班级 学号 姓名 数学 物理 C语言 总分 年级排名 班排名\n");
    for(i=0;i<studentCount;i++)
    {
        if(strcmp(stu[i].name,na)==0)
        {
            find=1;
            printf("%d  %d  %s %s %d %d %d %d %d %d\n",
            stu[i].year,stu[i].class,stu[i].id,stu[i].name,
            stu[i].math,stu[i].physics,stu[i].c,stu[i].total,
            stu[i].rankGrade,stu[i].rankClass);
        }
    }
    if(find==0)
        printf("未查询到此姓名学生\n");


}

void search_range() {
int min_score, max_score;
    int found = 0;

    printf("\n--- 按总分区间查询 ---\n");
    if (studentCount == 0) {
        printf("暂无学生数据，请先读取文件！\n");
        return;
    }

    printf("请输入最低总分: ");
    scanf("%d", &min_score);
    printf("请输入最高总分: ");
    scanf("%d", &max_score);

    printf("\n%-15s %-15s %-6s %-6s %-6s %-6s %-6s %-6s %-8s %-8s\n", 
           "学号", "姓名", "数学", "物理", "C语言", "总分", "入学年", "班级", "年级排名", "班级排名");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        if (stu[i].total >= min_score && stu[i].total <= max_score) {
            printf("%-15s %-15s %-6d %-6d %-6d %-6d %-6d %-6d %-8d %-8d\n",
                   stu[i].id, stu[i].name, stu[i].math, stu[i].physics, stu[i].c,
                   stu[i].total, stu[i].year, stu[i].class, stu[i].rankGrade, stu[i].rankClass);
            found++;
        }
    }

    if (found == 0) {
        printf("没有找到总分在 %d 到 %d 之间的学生。\n", min_score, max_score);
    } else {
        printf("共查询到 %d 名学生。\n", found);
    }
}
void save_file() {
FILE *fp = fopen("score_rank.txt", "w");
    if (fp == NULL) {
        printf("错误：无法创建或打开 score_rank.txt 文件！\n");
        return;
    }

    // 表头和对齐完全复刻任务 7
    fprintf(fp, "%-15s %-15s %-6s %-6s %-6s %-6s %-6s %-6s %-8s %-8s\n", 
            "学号", "姓名", "数学", "物理", "C语言", "总分", "入学年", "班级", "年级排名", "班级排名");
    fprintf(fp, "------------------------------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        fprintf(fp, "%-15s %-15s %-6d %-6d %-6d %-6d %-6d %-6d %-8d %-8d\n",
                stu[i].id, stu[i].name, stu[i].math, stu[i].physics, stu[i].c,
                stu[i].total, stu[i].year, stu[i].class, stu[i].rankGrade, stu[i].rankClass);
    }

    fclose(fp);
}

void search_single() {
char target_id[15];
    int found = 0;

    printf("\n--- 精确查询单个学生（加分功能）---\n");
    if (studentCount == 0) {
        printf("暂无学生数据，请先读取文件！\n");
        return;
    }

    printf("请输入要查询的学生学号: ");
    scanf("%s", target_id);

    // 打印单人表头，保持整体视觉效果高度统一
printf("\n%-11s %-11s %-4s %-4s %-4s %-4s %-4s %-4s %-6s %-6s\n", "学号", "姓名", "数学", "物理", "C语言", "总分", "入学年", "班级", "年级排名", "班级排名");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(stu[i].id, target_id) == 0) {
            printf("%-15s %-15s %-6d %-6d %-6d %-6d %-6d %-6d %-8d %-8d\n",
                   stu[i].id, stu[i].name, stu[i].math, stu[i].physics, stu[i].c,
                   stu[i].total, stu[i].year, stu[i].class, stu[i].rankGrade, stu[i].rankClass);
            found = 1;
            break; // 学号是唯一的，找到就退出循环
        }
    }

    if (found == 0) {
        printf("没有找到学号为 %s 的学生。\n", target_id);
    }
}
