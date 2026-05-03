//2550703 卓03 李良玉

/* 允许按需加入系统的宏定义、需要的头文件等 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include "read_stulist.h"
using namespace std;

#define MAX_FILENAME_LEN 512

class stu_merge
{
private:
    int  stu_no;
    char stu_name[MAX_NAME_LEN];

    int in_round_1;
    int in_round_2;

    friend class stu_list;

public:
    /* 不允许定义任何的公有数据成员及成员函数 */
};

class stu_list
{
private:
    student list_round_1[MAX_STU_NUM];
    int list_num_1;

    student list_round_2[MAX_STU_NUM];
    int list_num_2;

    stu_merge list_merge[MAX_STU_NUM];
    int list_merge_num;

private:
    static int is_gb2312_first_byte(unsigned char ch)
    {
        if (ch >= 0xA1 && ch <= 0xFE)
        {
            return 1;
        }
        return 0;
    }

    static int disp_cols_gb2312(const char* s)
    {
        int cols;
        const unsigned char* p;

        cols = 0;
        p = (const unsigned char*)s;

        while (*p != '\0')
        {
            if (is_gb2312_first_byte(*p))
            {
                ++p;
                if (*p != '\0')
                {
                    ++p;
                }
                cols += 2;
            }
            else
            {
                ++p;
                cols += 1;
            }
        }

        return cols;
    }

    static void safe_copy_name(char* dst, const char* src)
    {
        int i;

        i = 0;
        while (i < MAX_NAME_LEN - 1 && src[i] != '\0')
        {
            dst[i] = src[i];
            ++i;
        }
        dst[i] = '\0';
    }

    int find_in_merge(int stu_no) const
    {
        int i;

        i = 0;
        while (i < list_merge_num)
        {
            if (list_merge[i].stu_no == stu_no)
            {
                return i;
            }
            ++i;
        }
        return -1;
    }

    void swap_merge(int i, int j)
    {
        stu_merge tmp;

        tmp = list_merge[i];
        list_merge[i] = list_merge[j];
        list_merge[j] = tmp;
    }

    void sort_merge_by_no()
    {
        int i;
        int j;
        int min_idx;

        i = 0;
        while (i < list_merge_num)
        {
            min_idx = i;
            j = i + 1;
            while (j < list_merge_num)
            {
                if (list_merge[j].stu_no < list_merge[min_idx].stu_no)
                {
                    min_idx = j;
                }
                ++j;
            }

            if (min_idx != i)
            {
                swap_merge(i, min_idx);
            }

            ++i;
        }
    }

    void print_pad_left(const char* s, int width_cols) const
    {
        int cols;
        int pad;

        cols = disp_cols_gb2312(s);
        cout << s;

        pad = width_cols - cols;
        while (pad > 0)
        {
            cout << ' ';
            --pad;
        }
    }

    void print_pad_right(const char* s, int width_cols) const
    {
        int cols;
        int pad;

        cols = disp_cols_gb2312(s);
        pad = width_cols - cols;

        while (pad > 0)
        {
            cout << ' ';
            --pad;
        }

        cout << s;
    }

public:
    stu_list();
    int read(const char* filename, const int round);
    int process();
    int print(const char* prompt = NULL);
};

/***************************************************************************/
stu_list::stu_list()
{
    list_num_1 = 0;
    list_num_2 = 0;
    list_merge_num = 0;
}

/***************************************************************************/
int stu_list::read(const char* filename, const int round)
{
    int ret;

    ret = 0;

    switch (round)
    {
    case 1:
        list_num_1 = read_stulist(filename, list_round_1, MAX_STU_NUM);
        if (list_num_1 > 0)
        {
            print_stulist("第一轮选课名单：", list_round_1, list_num_1);
        }
        else
        {
            ret = -1;
        }
        break;

    case 2:
        list_num_2 = read_stulist(filename, list_round_2, MAX_STU_NUM);
        if (list_num_2 > 0)
        {
            print_stulist("第二轮选课名单：", list_round_2, list_num_2);
        }
        else
        {
            ret = -1;
        }
        break;

    default:
        ret = -1;
        break;
    }

    return ret;
}

/***************************************************************************
  合并逻辑：两轮名单取并集去重；记录每人是否在第一轮/第二轮
***************************************************************************/
int stu_list::process()
{
    int i;
    int idx;
    int no;

    list_merge_num = 0;

    i = 0;
    while (i < list_num_1)
    {
        no = list_round_1[i].no;
        if (no != 0)
        {
            idx = find_in_merge(no);
            if (idx < 0)
            {
                list_merge[list_merge_num].stu_no = no;
                safe_copy_name(list_merge[list_merge_num].stu_name, list_round_1[i].name);
                list_merge[list_merge_num].in_round_1 = 1;
                list_merge[list_merge_num].in_round_2 = 0;
                ++list_merge_num;
            }
            else
            {
                list_merge[idx].in_round_1 = 1;
            }
        }
        ++i;
    }

    i = 0;
    while (i < list_num_2)
    {
        no = list_round_2[i].no;
        if (no != 0)
        {
            idx = find_in_merge(no);
            if (idx < 0)
            {
                list_merge[list_merge_num].stu_no = no;
                safe_copy_name(list_merge[list_merge_num].stu_name, list_round_2[i].name);
                list_merge[list_merge_num].in_round_1 = 0;
                list_merge[list_merge_num].in_round_2 = 1;
                ++list_merge_num;
            }
            else
            {
                list_merge[idx].in_round_2 = 1;
                /* 名字以第二轮为准 */
                safe_copy_name(list_merge[idx].stu_name, list_round_2[i].name);
            }
        }
        ++i;
    }

    sort_merge_by_no();

    return 0;
}
//输出格式
int stu_list::print(const char* prompt)
{
    int i;
    int name_w;
    int table_w;
    const char* s1;
    const char* s2;

    if (prompt != NULL)
    {
        cout << prompt << endl;
    }

    name_w = 0;
    i = 0;
    while (i < list_merge_num)
    {
        int w;

        w = disp_cols_gb2312(list_merge[i].stu_name);
        if (w > name_w)
        {
            name_w = w;
        }
        ++i;
    }

    if (name_w < 4)
    {
        name_w = 4;
    }

    table_w = 31 + name_w;

    i = 0;
    while (i < table_w+2)
    {
        cout << '=';
        ++i;
    }
    cout << endl;

    /* 表头 */
    cout << " ";
    print_pad_left("序号", 4);
    cout << "  ";
    print_pad_left("学号", 7);
    cout << "  ";
    print_pad_left("姓名", name_w);
    cout << "  ";
    print_pad_left("第一轮", 6);
    cout << "  ";
    print_pad_left("第二轮", 6);
    cout << endl;

    i = 0;
    while (i < table_w+2)
    {
        cout << '=';
        ++i;
    }
    cout << endl;

    /* 数据行 */
    i = 0;
    while (i < list_merge_num)
    {
        if (list_merge[i].in_round_1)
        {
            s1 = "Y";
        }
        else
        {
            s1 = "/";
        }

        if (list_merge[i].in_round_2)
        {
            if (list_merge[i].in_round_1)
            {
                s2 = "Y";
            }
            else
            {
                s2 = "补选";
            }
        }
        else
        {
            if (list_merge[i].in_round_1)
            {
                s2 = "退课";
            }
            else
            {
                s2 = "/";
            }
        }

		cout << " ";
        cout << left << setw(4) << (i + 1);
        cout << "  ";
        cout << left << setw(7) << list_merge[i].stu_no;
        cout << "  ";
        print_pad_left(list_merge[i].stu_name, name_w);
        cout << "  ";
        print_pad_left(s1, 6);
        cout << "  ";
        print_pad_left(s2, 6);
        cout << endl;

        ++i;
    }
    i = 0;
    while (i < table_w + 2)
    {
        cout << '=';
        ++i;
    }
    cout << endl;
    return 0;
}

/***************************************************************************/
int main(int argc, char** argv)
{
    char file1[MAX_FILENAME_LEN];
    char file2[MAX_FILENAME_LEN];
    stu_list list;

    cout << "请输入前一轮选课的数据文件 : ";
    gets_s(file1);

    cout << "请输入后一轮选课的数据文件 : ";
    gets_s(file2);

    if (list.read(file1, 1) < 0)
    {
        return -1;
    }
    if (list.read(file2, 2) < 0)
    {
        return -1;
    }

    list.process();
    list.print("最终选课名单");

    return 0;
}
