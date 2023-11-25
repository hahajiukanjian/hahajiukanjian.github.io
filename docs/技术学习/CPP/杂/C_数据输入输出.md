# 初识C语言之数据输入输出篇——带你领略编程世界的文字艺术！

>   【摘要】 目录 语句 字符数据输入输出 字符数据输出 字符数据输入 字符串输入输出 字符串输出函数 字符串输入函数  格式输出函数 格式输入函数 顺序程序设计应用 语句 C语言的语句用来向计算机系统发出操作指令。一条语句编写完成经过编译后产生若干条机器指令。实际程序中包含若干条语句，因此语句的作用就是完成一定的操作任务。 字符数据输入输出 字符数据输出...

**目录**

语句

字符数据输入输出

字符数据输出

字符数据输入

字符串输入输出

字符串输出函数

字符串输入函数



格式输出函数

格式输入函数

顺序程序设计应用

------

## 语句

C语言的语句用来向计算机系统发出操作指令。一条语句编写完成经过编译后产生若干条机器指令。实际程序中包含若干条语句，因此语句的作用就是完成一定的操作任务。

## 字符数据输入输出

### 字符数据输出

字符数据输出使用的是putchar函数，作用是向显示设备输出一个字符。该函数的定义为：

int putchar( int ch );

使用时要添加头文件stdio.h，其中的参数ch是要进行输出的字符，可以是字符型变量或整型变量，也可以使用常量。例如输出一个字符A的代码如下：

putchar('A');

使用putchar函数也可以输出转义字符，例如输出字符A：

putchar('\101');

【实例5.1】 使用putchar函数实现字符数据输出。在程序中使用putchar函数，输出字符串“Hello”并且在字符串输出完毕之后进行换行。

```cpp
#include<stdio.h>
int main()
{
    char cChar1,cChar2,cChar3,cChar4;	/*声明变量*/
    cChar1='H'; /*为变量赋值*/
    cChar2='e';
    cChar3='l';
    cChar4='o';
    putchar(cChar1); /*输出字符变量*/
    putchar(cChar2);
    putchar(cChar3);
    putchar(cChar3);
    putchar(cChar4);
    putchar('\n'); /*输出转义字符*/
    return 0;
}
```

![img](https://img-blog.csdnimg.cn/20210410145915290.png)

### 字符数据输入

字符数据输入使用的是getchar函数，此函数的作用是从终端（输入设备）输入一个字符。getchar函数与putchar函数的区别在于没有参数。

该函数的定义为：

int getchar();

使用getchar函数时也要添加头文件stdio.h，函数的值就是从输入设备得到的字符。例如从输入设备得到一个字符赋给字符变量cChar：

cChar=getchar();

**【实例5.2】 使用getchar函数实现字符数据输入。在本实例中，使用getchar函数获取在键盘上输入的字符，再利用putchar函数进行输出。本实例演示了将getchar作为putchar函数表达式的一部分，进行输入和输出字符的方式。**

```cpp
      #include<stdio.h>
      int main()
      {
     	char cChar1;	/*声明变量*/
      	cChar1=getchar();	/*在输入设备得到字符*/
     	putchar(cChar1);	/*输出字符*/
     	putchar('\n');	/*输出转义字符换行*/
      	getchar();	/*得到回车字符*/
     	putchar(getchar());	/*得到输入字符，直接输出*/
     	putchar('\n');	/*换行*/
     	return 0;	/*程序结束*/
      }
  
 
```

![img](https://img-blog.csdnimg.cn/20210410150050883.png)

【实例5.3】 使用getchar函数取消获取回车符。

```cpp
      #include<stdio.h>
      int main()
      {
     	char cChar1;		/*声明变量*/
      	cChar1=getchar();		/*在输入设备得到字符*/
     	putchar(cChar1);		/*输出字符*/
     	putchar('\n');		/*输出转义字符换行*/
     		/*将此处getchar函数删掉*/
     	putchar(getchar());		/*得到输入字符，直接输出*/
     	putchar('\n');		/*换行*/
     	return 0;		/*程序结束*/
      }
  
 
```

![img](https://img-blog.csdnimg.cn/20210410150226825.png)

## 字符串输入输出

### 字符串输出函数

字符串输出使用的是puts函数，作用是输出一个字符串到屏幕上。该函数的定义为：

int puts( char *str );

使用该函数时，先要在其程序中添加stdio.h头文件。其中，形式参数str是字符指针类型，可以用来接收要输出的字符串。例如使用puts函数输出一个字符串：

puts("I LOVE CHINA!"); /*输出一个字符串常量*/

这行语句是输出一个字符串，之后会自动进行换行操作。这与printf函数有所不同，在前面的实例中使用printf函数进行换行时，要在其中添加转义字符'\n'。puts函数会在字符串中判断“\0”结束符，遇到结束符时，后面的字符不再输出并且自动换行。例如：

puts("I LOVE\0 CHINA!"); /*输出一个字符串常量*/

在上面的语句中加上“\0”字符后，puts函数输出的字符串就变成：I LOVE。

**【实例5.4】 使用字符串输出函数显示信息提示。在本实例中，使用puts函数对字符串常量和字符串变量都进行操作，在这些操作中观察使用puts函数的方式。**

```cpp
      #include<stdio.h>
      int main()
      {
     	char* Char="ILOVECHINA";	/*定义字符串指针变量*/
     	puts("ILOVECHINA!"); /*输出字符串常量*/
     	puts("I\0LOVE\0CHINA!"); /*输出字符串常量，其中加入结束符'\0'*/
     	puts(Char); /*输出字符串变量的值*/
      	Char="ILOVE\0CHINA!"; /*改变字符串变量的值*/
     	puts(Char); /*输出字符串变量的值*/
     	return 0; /*程序结束*/
      }
  
 
```

![img](https://img-blog.csdnimg.cn/2021041015091160.png)

### 字符串输入函数

字符串输入函数使用的是gets函数，作用是将读取字符串保存在形式参数str变量中，读取过程直到出现新的一行为止。其中新的一行的换行字符将会转化为字符串中的空终止符“\0”。gets函数的定义如下：

char *gets( char *str );

在使用gets字符串输入函数前，要为程序加入头文件stdio.h。其中的str字符指针变量为形式参数。例如定义字符数组变量cString，然后使用gets函数获取输入字符的方式如下：

gets(cString);

在上面的代码中，cString变量获取到了字符串，并将最后的换行符转化成了终止字符。

**【实例5.5】 使用字符串输入函数gets获取输入信息。**

```cpp
      #include<stdio.h>
      int main()
      {
     	char cString[30];	/*定义一个字符数组变量*/
      	gets(cString); /*获取字符串*/
     	puts(cString); /*输出字符串*/
     	return 0; /*程序结束*/
      }
  
 
```

## ![img](https://img-blog.csdnimg.cn/20210410151812234.png)

## 格式输出函数

前面章节的实例中常常使用格式输入输出函数scanf和printf。其中printf函数就是用于格式输出的函数，也称为格式输出函数。

printf函数的作用是向终端（输出设备）输出若干任意类型的数据。printf函数的一般格式为：

printf(格式控制，输出列表)

括号内包括两部分：

格式控制

格式控制是用双引号括起来的字符串，此处也称为转换控制字符串。其中包括两种字符，一种是格式字符，另一种是普通字符。

格式字符用来进行格式说明，作用是将输出的数据转化为指定的格式输出。格式字符是以 “ % ” 字符开头的。

普通字符是需要原样输出的字符，其中包括双引号内的逗号、空格和换行符。

 

 

 

输出列表

输出列表中列出的是要进行输出的一些数据，可以是变量或表达式。

例如，要输出一个整型变量时：

int iInt=10;

printf("this is %d",iInt);

执行上面的语句显示出来的字符是this is 10。在格式控制双引号中的字符是this is %d，其中的this is字符串是普通字符，而%d是格式字符，表示输出的是后面iInt的数据。

由于printf是函数，“格式控制”和“输出列表”这两个位置都是函数的参数，因此printf函数的一般形式也可以表示为：

**printf(参数1，参数2，****……****，参数n)**

**函数中的每一个参数按照给定的格式和顺行依次输出。例如，显示一个字符型变量和整型变量：**

**printf("the Int is %d,the Char is %c",iInt,cChar);**

**下表列出了有关printf函数的格式字符。**

| **格 式 字 符** | **功 能 说 明**                                |
| --------------- | ---------------------------------------------- |
| d,i             | 以带符号的十进制形式输出整数（整数不输出符号） |
| o               | 以八进制无符号形式输出整数                     |
| x,X             | 以十六进制无符号形式输出整数。用               |
| u               | 以无符号十进制形式输出整数                     |
| c               | 以字符形式输出，只输出一个字符                 |
| s               | 输出字符串                                     |
| f               | 以小数形式输出                                 |
| e,E             | 以指数形式输出实数，用                         |
| g,G             | 选用                                           |

 **【实例5.6】 使用格式输出函数printf。在本实例中，使用printf函数对不同类型变量进行输出，对使用printf函数所用到的输出格式进行分析理解。**

```cpp
      #include<stdio.h>
      int main()
      {
     	int iInt=10;	/*定义整型变量*/
     	char cChar='A';	/*定义字符型变量*/
     	float fFloat=12.34f;	/*定义单精度浮点型*/
     	printf("the int is: %d\n",iInt);	/*使用printf函数输出整型*/
     	printf("the char is: %c\n",cChar);/*输出字符型*/
     	printf("the float is: %f\n",fFloat);/*输出浮点型*/
     	printf("the stirng is: %s\n","I LOVE YOU");	/*输出字符串*/
     	return 0;
      }
  
 
```

![img](https://img-blog.csdnimg.cn/20210410153136853.png)

**【实例5.7】 在printf函数中使用附加符号。（在本实例中，使用printf函数的附加格式说明字符，对输出的数据进行更为精准的格式设计。**

```cpp
      #include<stdio.h>
      int main()
      {
     	long iLong=100000;	/*定义长整型变量，为其赋值*/
     	printf("the Long is %ld\n",iLong);/*输出长整型变量*/
     	printf("the string is: %s\n","LOVE");/*输出字符串*/
     	printf("the string is: %10s\n","LOVE");/*使用m控制输出列*/
     	printf("the string is: %-10s\n","LOVE");/*使用-表示向左靠拢*/
     	printf("the string is: %10.3s\n","LOVE");/*使用n表示取字符数*/
     	printf("the string is: %-10.3s\n","LOVE");
     	return 0;
      }
  
 
```

![img](https://img-blog.csdnimg.cn/20210410153218273.png)

## 格式输入函数

与格式输出函数printf相对应的是格式输入函数scanf。该函数的功能是指定固定的格式，并且按照指定的格式接收用户在键盘上输入的数据，最后将数据存储在指定的变量中。

scanf函数的一般格式为：

scanf(格式控制，地址列表)

通过scanf函数的一般格式可以看出，参数位置中的格式控制与printf函数相同。例如%d表示十进制的整型，%c表示单字符。而在地址列表中，此处应该给出用来接收数据变量的地址。例如得到一个整型数据的操作：

scanf("%d",&iInt); /*得到一个整型数据*/

在上面的代码中，&符号表示取iInt变量的地址，因此不用关心变量的地址具体是多少，只要在代码中在变量的标识符前加&符号，就表示取变量的地址。

| **格 式 字 符** | **功 能 说 明**                                    |
| --------------- | -------------------------------------------------- |
| d,i             | 用来输入有符号的十进制整数                         |
| u               | 用来输入无符号的十进制整数                         |
| o               | 用来输入无符号的八进制整数                         |
| x,X             | 用来输入无符号的十六进制整数（大小写作用是相同的） |
| c               | 用来输入单个字符                                   |
| s               | 用来输入字符串                                     |
| f               | 用来输入实型，可以用小数形式或指数形式输入         |
| e,E,g,G         | 与                                                 |

**【实例5.8】 使用scanf格式输入函数得到用户输入的数据。在本实例中，利用scanf函数得到用户输入的两个整型数据，因为scanf函数只能用于输入操作，所以若在屏幕上显示信息则使用显示函数。**

```cpp
      #include<stdio.h>
      int main()
      {
     	int iInt1,iInt2;		/*定义两个整型变量*/
     	puts("Please enter two numbers:");/*通过puts函数输出提示信息的字符串*/
     	scanf("%d%d",&iInt1,&iInt2);	/*通过scanf函数得到输入的数据*/
     	printf("The first is : %d\n",iInt1);/*显示第一个输入的数据*/
     	printf("The second is : %d\n",iInt2);/*显示第二个输入的数据*/
     	return 0;
      }
  
 
```

![img](https://img-blog.csdnimg.cn/20210410153428892.png)

**在printf函数中除了格式字符还有附加格式用于更为具体的说明，相应地，scanf函数中也有附加格式用于更为具体的格式说明，如下表所示。**

| **字  符** | **功 能 说 明**                          |
| ---------- | ---------------------------------------- |
| l          | 用于输入长整型数据（可用于               |
| h          | 用于输入短整型数据（可用于               |
| n          | 指定输入数据所占宽度                     |
| *          | 表示指定的输入项在读入后不赋给相应的变量 |

## 顺序程序设计应用

**【实例5.10】 计算圆的面积。在本实例中，定义单精度浮点型变量，为其赋值为圆周率的值。得到用户输入的数据并进行计算，最后将计算的结果输出。**

```cpp
      #include<stdio.h>
      int main()
      {
     	float Pie=3.14f;	/*定义圆周率*/
     	float fArea;	/*定义变量，表示圆的面积*/
     	float fRadius;	/*定义变量，表示圆的半径*/
     	puts("Enter the radius:");	/*输出提示信息*/
     	scanf("%f",&fRadius);		/*输入圆的半径*/
      	fArea=fRadius*fRadius*Pie;	/*计算圆的面积*/
     	printf("The Area is: %.2f\n",fArea);	/*输出计算的结果*/
     	return 0;		/*程序结束*/
      }
  
 
```

![img](https://img-blog.csdnimg.cn/20210410153640781.png)

**【实例5.11】 将大写字符转化成小写字符。本实例要将一个输入的大写字符转化成小写字符，需要对其中的ASCII码的关系有所了解。将大写字符转化成小写字符的方法就是将大写字符的ASCII码转化成小写字符的ASCII码。**

```cpp
      #include<stdio.h>
      int main()
      {
     	char cBig;	/*定义字符变量，表示大写字符*/
     	char cSmall;	/*定义字符变量，表示小写字符*/
     	puts("Please enter capital character:");/*输出提示信息*/
      	cBig=getchar();	/*得到用户输入的大写字符*/
     	puts("Minuscule character is:");	/*输出提示信息*/
      	cSmall=cBig+32;	/*将大写字符转化成小写字符*/
     	printf("%c\n",cSmall);	/*输出小写字符*/
     	return 0;		/*程序结束*/
      }
  
 
```

![img](https://img-blog.csdnimg.cn/20210410153729126.png)

**其中，用于单个字符的输入、输出时，使用的是getchar和putchar函数，而gets和puts函数用于输入、输出字符串，并且puts函数在遇到终止符时会进行自动换行。为了能输出其他类型的数据，可以使用格式输出函数printf和格式输入函数scanf。在这两个格式函数中，利用格式字符和附加格式字符可以更为具体地进行格式说明。**

### 每文一语

>   遇事最有水平的处理方式就是——冷静！

文章来源: wxw-123.blog.csdn.net，作者：王小王-123，版权归原作者所有，如需转载，请联系作者。

------

原文链接：wxw-123.blog.csdn.net/article/details/115576138