#include <stdio.h>

int main()
{
    int x, y;
    x = 50;
    y = 9;
    printf("%x\n", -(x < y));
    printf("%x\n", (x < y));
}
