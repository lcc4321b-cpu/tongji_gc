#include <iostream>

extern int g_shared;
static int g_static_global = 20;

int OtherAdd(int x, int y)
{
    int sum = x + y;
    return sum;
}

void OtherTouchGlobals(void)
{

    std::cout << "other.cpp g_shared=" << g_shared << std::endl;
    std::cout << "other.cpp g_static_global=" << g_static_global << std::endl;
}
