//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void swap_student(char id[][8], char name[][9], int score[], int i, int j)
{
    char tid[8];
    char tname[9];
    int ts;

    strcpy(tid, id[i]);
    strcpy(id[i], id[j]);
    strcpy(id[j], tid);

    strcpy(tname, name[i]);
    strcpy(name[i], name[j]);
    strcpy(name[j], tname);

    ts = score[i];
    score[i] = score[j];
    score[j] = ts;
}

void sort_by_id_desc(char id[][8], char name[][9], int score[], int n)
{
    for (int pass = 0; pass < n - 1; ++pass)
    {
        for (int i = 0; i < n - 1 - pass; ++i)
        {
            if (strcmp(id[i], id[i + 1]) < 0)
            {
                swap_student(id, name, score, i, i + 1);
            }
        }
    }
}

void input_students(char id[][8], char name[][9], int score[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("请输入第%d个人的学号、姓名、成绩\n", i + 1);
        scanf("%7s %8s %d", id[i], name[i], &score[i]);
    }
}

void output_students(char id[][8], char name[][9], int score[], int n)
{
    printf("\n");
    printf("及格名单(学号降序):\n");
    for (int i = 0; i < n; ++i)
    {
        if (score[i] >= 60)
        {
            printf("%s %s %d\n", name[i], id[i], score[i]);
        }
    }
}

int main()
{
    char id[10][8];
    char name[10][9];
    int score[10];

	input_students(id, name, score, 10);
    sort_by_id_desc(id, name, score, 10);
	output_students(id, name, score, 10);

    return 0;
}

