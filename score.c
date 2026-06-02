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

}

void show_menu() {

}

void calc_all() {

}

void show_grade() {

}

void show_class() {

}

void search_name() {

}

void search_range() {

}
void save_file() {

}

void search_single() {

}
