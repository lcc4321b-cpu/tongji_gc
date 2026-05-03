//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
    //get number
    double charge;
    int integer, small_charge;
    int fifty, twenty, ten, five, one;
    int little_fifty, little_ten, little_five, little_two, little_one;
    int total;

    printf("请输入找零值：\n");
    scanf("%lf", &charge);

    integer = (int)(charge + 0.005);
    small_charge = (int)(((charge - integer) + 0.005) * 100);

    //caculate
    fifty = integer / 50;
    twenty = integer % 50 / 20;
    ten = (integer / 10 - 5 * (integer >= 50)) % 2;
    five = integer % 10 / 5;
    one = integer % 5;
    little_fifty = small_charge / 50;
    little_ten = small_charge % 50 / 10;
    little_five = small_charge % 10 / 5;
    little_two = small_charge % 5 / 2;
    little_one = (small_charge - (little_fifty == 1)) % 2;
    total = fifty + twenty + ten + five + one + little_fifty + little_five + little_one + little_ten + little_two;

    //print
    printf("共%d张找零，具体如下：\n", total);
    if (fifty >= 1)
    {
        printf("50元 : %d张\n", fifty);
    }
    if (twenty >= 1)
    {
        printf("20元 : %d张\n", twenty);
    }
    if (ten >= 1)
    {
        printf("10元 : %d张\n", ten);
    }
    if (five >= 1)
    {
        printf("5元  : %d张\n", five);
    }
    if (one >= 1)
    {
        printf("1元  : %d张\n", one);
    }
    if (little_fifty >= 1)
    {
        printf("5角  : %d张\n", little_fifty);
    }
    if (little_ten >= 1)
    {
        printf("1角  : %d张\n", little_ten);
    }
    if (little_five >= 1)
    {
        printf("5分  : %d张\n", little_five);
    }
    if (little_two >= 1)
    {
        printf("2分  : %d张\n", little_two);
    }
    if (little_one >= 1)
    {
        printf("1分  : %d张\n", little_one);
    }

    return 0;
}