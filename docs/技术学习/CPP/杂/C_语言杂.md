# C语言杂

## C语言中输入输出十六进制

scanf 输入十六进制

在这里，我们必须声明一个无符号的int变量，并以十六进制格式输入一个值。

要以十六进制格式输入值-我们使用“％x”或“％X”格式说明符并以十六进制格式打印值-我们使用相同格式的说明符“％x”或“％X” 。

-   “％x” –用小写字母(a至f)打印值

-   “％X” –用大写字母(A到F)打印值

-   >    **注意：**在scanf()中 ，可以同时使用格式说明符“％x”或“％X” –它不会影响用户输入，但是在printf()中 – “％x”或“％X”很重要用于以十六进制值(a到f或A到F)打印字母。

## 实现幂运算

用函数pow(x,2)表x的2次方
加上头文件math.h

double pow(double, double);

## 二维数组中array[0]的含义

-   array[0]表示: 

## c++ 警告 warning: conversion from string literal to 'char *' is deprecated
c++ 里面 如果你写

```cpp  view plain  copy
char *af ="bbbb";  
会看到 Conversion from string literal to 'char *' is deprecated  翻译后是：从字符串‘char *’转换是废弃的。

这是什么原因呢，书上是这么写的：

c++从c语言继承下来的一种通用结构是c风格字符串，char 字符串字面值就是这中类型的实例，而字符串字面值的类型是const char 类型的数组，是以空字符null结束的字符数组。

[cpp]  view plain  copy
char ca1[] = "hello";//正确 包换null  
char ca2[] = {'h','e','l','l','o'};//不含null  
char ca3[] = {'h','e','l','l','o','\0'};//包含null  

代码可以看出，ca1和ca3是属于c风格字符串。
现在回到问题中，那么正确的写法是什么呢？

[cpp]  view plain  copy
char af[] = "hello";  
[cpp]  view plain  copy
char const *af = "hello";  
以上两种方式都是正确的，而为什么要加上const， 因为char字符串字面值是不允许修改的，原因如下：
[cpp]  view plain  copy
char const *ak ="ffff";  
ak = "hello";  
ok，编译正确，这里并木有修改*ak的值，而是把ak重新指向了“hello”
[cpp]  view plain  copy
char const *ak ="ffff";  
 *ak = "h";  
编译有错误 “Read-only variable is  not assignable” 
————————————————
版权声明：本文为CSDN博主「hongge372」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/u010029439/article/details/79483329
