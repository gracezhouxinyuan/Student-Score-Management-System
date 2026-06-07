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

    while(stu_num<MAX_STUDENT){
        if(fscanf(fp,"%s %s %d %d %d",
            stu[stu_num].id,
            stu[stu_num].name,
            &stu[stu_num].math,
            &stu[stu_num].physics,
            &stu[stu_num].c_lang)!=5){
            break;
        }

        stu[stu_num].grade=(stu[stu_num].id[0]-'0')*1000+
            stu[stu_num].id[1]-'0')*100+
            stu[stu_num].id[2]-'0')*10+
            stu[stu_num].id[3]-'0');

        stu[stu_num].class=(stu[stu_num].id[4]-'0')*10+
        (stu[stu_num].id[5]-'0');

        stu[stu_num].total=0;
        stu[stu_num].grade_rank=0;
        stu[stu_num].class_rank=0;

        stu_num++;
    }

    fclose(fp);
    printf("读了%d个学生\n",stu_num);
}

void show_menu() {
    printf("\n======成绩系统======\n");
    printf("1.读文件\n");
    printf("2.菜单\n");
    printf("3.算总分平均分\n");
    printf("4.按成绩排\n");
    printf("5.按班级看\n");
    printf("6.查名字\n");
    printf("7.按分数段查\n");
    printf("8.存文件\n");
    printf("9.单科排名\n");
    printf("0.退出\n");
    printf("=====================\n");
    printf("选哪个：");
}

void calc_all() {
    if(count==0){
        printf("还没读数据，先执行1\n");
        return;
    }

    int sum=0,i=0;
    for(i<count;i++){
        stu[i].total=stu[i].score;
        stu[i].avg=stu[i].score;
        sum=sum+stu[i].score;
    }

    float ave=(float)sum/count;
    printf("全班总分：%d\n",sum);
    printf("全班平均：%.2f\n",ave);
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

void show_class() {int i
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

}
void save_file() {

}

void search_single() {

}
