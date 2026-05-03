//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#define N 10
#include <stdio.h>
#include <string.h>

void swap_student_score(char id[][8], char name[][9], int score[], int i, int j)
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

void sort_by_score_desc_stable(char id[][8], char name[][9], int score[], int n)
{
    for (int pass = 0; pass < n - 1; ++pass)
    {
        for (int i = 0; i < n - 1 - pass; ++i)
        {
            if (score[i] < score[i + 1])
            {
                swap_student_score(id, name, score, i, i + 1);
            }
        }
    }
}

void input_student_info(char id[][8], char name[][9], int score[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("请输入第%d个人的学号、姓名、成绩\n", i + 1);
        scanf("%7s %8s %d", id[i], name[i], &score[i]);
    }
}

void output_student_info(char id[][8], char name[][9], int score[], int n)
{
    printf("\n");
    printf("全部学生(成绩降序):\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%s %s %d\n", name[i], id[i], score[i]);
    }
}

int main()
{
    char id[N][8];
    char name[N][9];
    int score[N];

	input_student_info(id, name, score, N);
    sort_by_score_desc_stable(id, name, score, N);
	output_student_info(id, name, score, N);

    return 0;
}

