#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int g_shared = 300;
static int g_static_global = 10;

extern int OtherAdd(int x, int y);
extern void OtherTouchGlobals(void);

void FunStepDemo(int x)
{
    int a = x + 1;
    double b = std::sqrt(static_cast<double>(a));
    cout << "sqrt(" << a << ")=" << b << std::endl;
}

void FunStaticLocal(int delta)
{
    static int s_static_local = 100;
    int auto_local = delta * 2;

    s_static_local += delta;

    std::cout << "s_static_local=" << s_static_local << ", auto_local=" << auto_local << std::endl;
}

void FunArrayAsPointer(int* p, int n)
{
    int i = 0;

    for (i = 0; i < n; i++)
    {
        p[i] = p[i] + 1;
    }
}

void Fun2DArray(int m[][3], int rows)
{
    int r = 0;
    int c = 0;

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < 3; c++)
        {
            m[r][c] = m[r][c] + 10;
        }
    }
}

void OutOfBoundsDemo(void)
{
    int buf[5] = { 0, 1, 2, 3, 4 };
    int i = 0;

    // 故意写错：i <= 5 会写到 buf[5]（越界）
    for (i = 0; i <= 6; i++)
    {
        buf[i] = 100 + i;
    }

    std::cout << "buf[0]=" << buf[0] << std::endl;
}

int main(void)
{
    char ch = 'A';
    int x = 7;
    float f = 3.14f;

    int* px = &x;
    int& rx = x;

    int arr[5] = { 10, 20, 30, 40, 50 };
    int* parr = arr;

    int mat[2][3] =
    {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };

    int (*pRow)[3] = mat;

    const char* lit = "Hello, VS2022";
    char str[] = "Hello, array";


    FunStepDemo(x);

    FunStaticLocal(1);
    FunStaticLocal(2);

    FunArrayAsPointer(arr, 5);
    Fun2DArray(mat, 2);

    std::cout << "g_shared=" << g_shared << std::endl;
    std::cout << "main.cpp g_static_global=" << g_static_global << std::endl;

    x = OtherAdd(x, 5);
    OtherTouchGlobals();

    std::cout << "After other.cpp, g_shared=" << g_shared << std::endl;
    std::cout << "After other.cpp, x=" << x << std::endl;

    OutOfBoundsDemo();

    std::cout << "Done." << std::endl;
    return 0;
}
