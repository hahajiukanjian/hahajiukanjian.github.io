// 求z = ((8+6i)(4+3i))/((8+6i)+(4+3i))
#include <stdio.h>
#include <stdbool.h>

//构造复数的抽象数据类型
typedef struct Complex
{
    float RealPart;
    float ImagPart;
}CPX, * PCPX;

//基本操作
void assign(PCPX z, float real, float imag); //构造复数
void add(PCPX z, CPX z1, CPX z2);  //实现复数相加
void multiply(PCPX z, CPX z1, CPX z2);  //实现复数相乘
bool divide(PCPX z, CPX z1, CPX z2);  //实现复数相除

int main(void)
{
    //利用函数求得结果
    CPX z1, z2, z3, z4, z;
    assign(&z1,8.0,6.0);
    assign(&z2,4.0,3.0);
    add(&z3,z1,z2);
    multiply(&z4,z1,z2);
    if(divide(&z,z4,z3))
        printf("z = (%f + %fi)", z.RealPart,z.ImagPart);
    else
        printf("分母为零,无结果");

    return 0;
}

//基本操作的具体实现
void assign(PCPX z, float real, float imag)
{
    z->RealPart = real;
    z->ImagPart = imag;
}
void add(PCPX z, CPX z1, CPX z2)
{
    //初始条件:复数已存在
    //操作结果:两个复数相加
    z->RealPart = z1.RealPart + z2.RealPart;
    z->ImagPart = z1.ImagPart + z2.ImagPart;
}
void multiply(PCPX z, CPX z1, CPX z2)
{
    z->RealPart = (z1.RealPart*z2.RealPart) - (z1.ImagPart*z2.ImagPart);
    z->ImagPart = (z1.RealPart*z2.ImagPart) + (z1.ImagPart*z2.RealPart);
}
bool divide(PCPX z, CPX z1, CPX z2)
{
    CPX z3;
    z3.ImagPart = -z2.ImagPart;
    z3.RealPart = z2.RealPart;
    CPX z5, z6;
    multiply(&z5,z2,z3);
    multiply(&z6,z1,z3);
    if(0 != z5.RealPart+z5.ImagPart)
    {
        z->RealPart = z6.RealPart / (z5.RealPart+z5.ImagPart);
        z->ImagPart = z6.ImagPart / (z5.RealPart+z5.ImagPart);
        return true;
    }
    else
        return false;
}
