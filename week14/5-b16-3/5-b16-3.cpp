//2550703 卓03 李良玉
#include <iostream>
#include <string>
using namespace std;

void swap_student_id(string id[], string name[], int score[], int i, int j)
{
    string tid = id[i];
    id[i] = id[j];
    id[j] = tid;
    string tnm = name[i];
    name[i] = name[j];
    name[j] = tnm;
    int ts = score[i];
    score[i] = score[j];
    score[j] = ts;
}

void sort_by_id_asc(string id[], string name[], int score[], int n)
{
    for (int pass = 0; pass < n - 1; ++pass)
    {
        for (int i = 0; i < n - 1 - pass; ++i)
        {
            if (id[i] > id[i + 1])
            {
                swap_student_id(id, name, score, i, i + 1);
            }
        }
    }
}

void input_students(string id[], string name[], int score[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << "请输入第" << (i + 1) << "个人的学号、姓名、成绩" << endl;
        cin >> id[i] >> name[i] >> score[i];
    }
}

void output_students(string id[], string name[], int score[], int n)
{
    cout << endl;
    cout << "全部学生(学号升序):" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << name[i] << " " << id[i] << " " << score[i] << endl;
    }
}

int main()
{
    const int N = 10;
    string id[N], name[N];
    int score[N];

	input_students(id, name, score, N);
    sort_by_id_asc(id, name, score, N);
	output_students(id, name, score, N);

    return 0;
}

