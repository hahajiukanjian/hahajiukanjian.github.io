/*
    没有改变main函数中两个变量的值是因为:
    在swap函数中仅改变了n和m指向的地址,并没有交换变量的值.
*/

#include <stdio.h>
void swap(float *m, float *n)
{
    float *t;
    t = m;
    m = n;
    n = t;
}

int main(void)
{
    float a = 3.0,b = 5.0;
    swap(&a, &b);
    printf("a=%f, b=%f", a, b);

    return 0;
}