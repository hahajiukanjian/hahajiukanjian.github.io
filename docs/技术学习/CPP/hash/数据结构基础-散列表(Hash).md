# 数据结构基础-散列表(Hash)

## 实验介绍

我们本次实验主要目标是学会散列表（hash 算法）的原理与实现，学会灵活的运用，能够不依赖于模板根据题目独立写出各类散列表。数据结构 Hash 属于查找算法中的一部分，在比赛中通常也会占据一定的比例，相对较难也比较重要，大家一定要认真学习哦。

#### 知识点

-   Hash 的概念
-   构造方法
-   冲突处理

## 为什么使用哈希表

我们上面所提到的查找算法，简单来说，就是判断现有数据集合中是否有这个元素，或者是否有满足条件的元素。

其中的 Hash 算法则可以帮助我们判断是否有这个元素，虽然功能简单，但是其 O(1) 时间复杂度是具有高性能的。通过在记录的存储地址和它的关键码之间建立一个确定的对应关系。这样，不经过比较，一次读取就能得到所查元素的查找方法。相比普通的查找算法来说，仅仅在比较的环节，就会大大减少查找或映射所需要的时间。

#### 什么是哈希表（散列表）

我们采用散列技术将记录存储在一块连续的存储空间中，这块连续的存储空间即称为散列表。下面用一张图给大家展示一下散列表的实现过程：

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/4bc7e6a7dd8f60dd390a6d89db2f4a28-0)

如果还是不太明白的话，我们可以理解为数学函数，Y=F(X)，X 为自变量也就是这里的 Key, F( ) 对应图中的 H( )，也就是一个映射关系，Y 因变量也就是对应的值的 **存放位置**，此处一定要注意哦。

**此处让我们思考一下：**

-   散列技术仅仅是一种查找技术吗？

    应该说，散列既是一种查找技术，也是一种存储技术。

-   散列是一种完整的存储结构吗？

    散列只是通过记录的关键码定位该记录，没有完整地表达记录之间的逻辑关系，即通过关键码能推出 Key 值，但是通过关键码对应的值（即位置处的值）不能推出关键码，所以散列存储的关键码和值之间并不对称，因此散列主要是面向查找的存储结构。

## 散列表的初体验

通过上面的介绍，大家已经基本了解了散列表的原理。下面我们就来学习一下关于散列表的使用方式，下面我们用一个题目来引入。

#### 弗里的语言

>   小发明家弗里想创造一种新的语言，众所周知，发明一门语言是非常困难的，首先你就要克服一个困难就是，有大量的单词需要处理，现在弗里求助你帮他写一款程序，判断是否出现重复的两个单词。
>
>   要求：有重复的单词，就输出重复单词，没有重复单词，就输出 NO，多个重复单词输出最先出现的。

输入输出如下面示例所示：

首先输入：

```
第 1 行，输入 N，代表共计创造了多少个单词 第 2 行至第 N+1 行，输入 N 个单词 格式如下：     fjsdfgdfsg  fdfsgsdfg  bcvxbxfyres  
```

现在有以下样例输入。

**样例 1：**

```
输入： 6 1fagas  dsafa32j lkiuopybncv hfgdjytr cncxfg sdhrest 输出： NO 
```



**样例 2：**

```
输入： 5 sdfggfds fgsdhsdf dsfhsdhr sdfhdfh sdfggfds  输出： sdfggfds 
```



下面我们来分析一下解题思路，请大家跟着下面的思路一步一步实现，然后再对比后面给出的答案。

**第一步，首先我们需要创建一个散列表和一个公共溢出区。**

```
散列表 公共溢出区 
```



即使你现在不知道什么是散列表和溢出区，没关系！我们后边会做详细的讲解。

**第二步，需要定义插入散列表函数。**

-   按照散列表的映射方式设计即可
-   需要传入一个参数来表示放什么数据

```
in(Name) {    1. 无冲突    2. 冲突处理 } 
```



**第三步：定义查询函数。**

```
isAt() {    1. 如果散列表查询成功返回 True    2. 不为成功返回 False } 
```



**4. 第四步，定义散列表映射函数。**

此处我们采用除留余数法即可，不了解这个方法的同学别担心，后面在写解题代码的时候，我会具体为大家介绍。

```
int out(string s) {     处理字符串 s 生成对应的 Key 值 } 
```



**第五步，编写主函数代码。**

```
    输入 N     循环 N 次://            输入 word；                 先查询，有相同的单词有就设置 flag 为 1，ans = word        没有的话，就执行插入操作        根据 flag 决定输出什么。 
```



大致的代码逻辑就是这样，相信大家已经都学会了。可能有的小伙伴已经在嘀咕了“这有什么难的”，先别急，咱们继续往下看。

这道题的代码思路其实并不难，但是代码应该如何来写呢，大家是否还摸不着头脑？在比赛中我们为了追求高效率，必须熟知咱们所使用到的每一个函数的优缺点，做到“扬长避短”，所以在写代码前，我们先来聊聊散列表的优缺点。前面咱们已经了解到了，散列表具有高性能，查找效率高等优点，下面就主要了解一下它的缺陷。

## 散列表的缺陷

散列表并不是适用于所有的需求场景，那么哪些情况下不适合使用呢？

1.  散列技术一般不适合在允许多个记录有同样关键码的情况下使用。

    因为这种情况下，通常会有冲突存在，将会降低查找效率，体现不出散列表查找效率高的优点。

    并且如果一定要在这个情况下使用的话，还需要想办法消除冲突，这将花费大量时间，那么就失去了 O(1) 时间复杂度的优势，所以在存在大量的冲突情况下，我们就要弃用散列表。

2.  散列方法也不适用于范围查找，比如以下两个情况。

-   查找最大值或者最小值

    因为散列表的值是类似函数的，映射函数一个变量只能对应一个值，不知道其他值，也不能查找最大值、最小值，RMQ(区间最值问题）可以采用 ST 算法、树状数组和线段树解决。

-   也不可能找到在某一范围内的记录

    比如查找小于 N 的数有多少个，是不能实现的，原因也是映射函数一个变量只能对应一个值，不知道其他值。

### 散列技术的关键问题

在使用散列表的时候，我们有两个关键的技术问题需要解决：

1.  散列函数的设计，如何设计一个简单、均匀、存储利用率高的散列函数？
2.  冲突的处理，如何采取合适的处理冲突方法来解决冲突。

#### 如何设计实现散列函数

在构建散列函数时，我们需要秉持两个原则：

1.  简单
    -   散列函数不应该有很大的计算量，否则会降低查找效率。
2.  均匀：
    -   函数值要尽量均匀散布在地址空间，这样才能保证存储空间的有效利用并减少冲突。

#### 散列函数实现三种方法

**1. 直接定址法。**

散列函数是关键码（Key）的映射的线性函数，形如：

H(key)=a∗key+b*H*(*k**e**y*)=*a*∗*k**e**y*+*b*

来看一个小案例：

>   如果关键码的集合已知且为 [11,22,33,66,88,44,99]
>
>   H(key)=111∗key+0*H*(*k**e**y*)=111∗*k**e**y*+0

如图：

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/33a166c3a59ad19ba92499d7e65feaaa-0)

**缺点：**

-   我们是看到了这个集合，然后想到他们都是 11 的倍数才想到这 Hash 函数。我们在平常的使用中一般不会提前知道 Key 值集合，所以使用较少。

**适用范围：**

-   事先知道关键码，关键码集合不大且较为连续而不离散。

**2. 除留余数法。**

H(key)=key mod p*H*(*k**e**y*)=*k**e**y* *m**o**d* *p*

来个小例子：

>   H(key)=key mod 21*H*(*k**e**y*)=*k**e**y* *m**o**d* 21

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/d748df7ad307d36189f68a74a573d55e-0)

会发现产生了很多相同的 H(K)，这就是发生冲突，因为一个位置只能放一个数，有两个值对应这里一个位置，是不可以的。

这种方法是**最常用**的方法，这个方法的关键在于如何选取 P，使得利用率较高并且冲突率较低，一般情况下，我们会选取最接近表长且小于等于表长的最大素数。

**缺点：**

-   P 选取不当，会导致冲突率上升。

**适用范围：**

-   除留余数法是一种最简单、也是最常用的构造散列函数的方法，并且不要求事先知道关键码的分布。

这个方法非常常用，我们后面题目的展开就是使用的这个方法。在大部分的算法实现中也都是选取的这一种方式。

代码实现：

```
C++    const int MOD=P;     int Hx(int n)    {        return n%MOD;    } Java            final Integer MOD=P;     Integer Hx(int n)    {        return n%MOD;    }  python      MOD=P #由于Python不含常量，我们这里就不做修饰     Hx(n):        global MOD        return n%MOD 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

**3. 数字分析法。**

比如我将我的集合全部转化为 16 进制数，根据关键码在各个位上的分布情况，选取分布比较均匀的若干位组成散列地址。或者将 N 位 10 进制数，观察各各位的数字分布，选取分布均匀的散列地址。

举个小例子：

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/afcd26bf35c056ad925ea20dcc5e24b9-0)

首先我们考虑一位作为散列函数，发现都是很多冲突，选取两位时，百位和十位组合最适宜，分布均匀且没有冲突。

当然，我们说的是这一方法的一个具体实列，既然叫做数字分析法，那么只有对于不同数据的不同分析，才能写出更是适配的 H(x)。

**另外还有两种平时使用极少的方法，分别是平方取中法和折叠法，我们就不再做过多的讲解，感兴趣的小伙伴可以在网上自行查找相关的资料了解哦。**

### 冲突的处理方法

1.  **开散列方法：**

    open hashing 也称为拉链法，separate chaining 称为链地址法，简单来说，就是由关键码得到的散列地址一旦产生了冲突，就去寻找下一个空的散列地址，并将记录存入。

    寻找下一个空的散列地址的方法：

-   线性探测法

当发生冲突时，从冲突位置的下一个位置起，依次寻找空的散列地址。

对于键值 key，设 H(key)=d，闭散列表的长度为 m，则发生冲突时，寻找下一个散列地址的公式为：

Hi=(H(key)＋di) MOD m（di=1，2，...，m−1）*H**i*=(*H*(*k**e**y*)＋*d**i*) *M**O**D* *m*（*d**i*=1，2，...，*m*−1）

堆积现象：

在处理冲突的过程中出现的非同义词之间对同一个散列地址争夺的现象。

例子：

>   Key 集合为 47, 7, 29, 11, 27, 92, 22, 8, 3。
>
>   P 值为 11，进行 Hash 映射，采用线性探测法处理冲突。

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/7c7aef8ed70fa2f09e73e23d4b83622b-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/5efb28c7a2d9bb3724fb30485fe95b88-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/4ad349aa6b40bf386825623d39e274fd-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/127de154e541991fa6049edab1505489-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/e92cabfd97045bffeb7220b7e2e5f419-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/a413d33f7fddeacd561f0d123c00efd8-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/dc61de7009418d78f21e3c58fd271111-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/aea957d81451bc08711e9567c084482e-0)

![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/bd007e59136a0a8d446d8944b5972120-0)

-   二次探测法

即当发生冲突时，寻找下一个散列地址的公式为：

Hi=(H(key)＋di)*H**i*=(*H*(*k**e**y*)＋*d**i*)

其中（di=12，－12，22，－22，...，q2，－q2且q≤m/2）其中（*d**i*=12，－12，22，－22，...，*q*2，－*q*2且*q*≤*m*/2）

-   随机探测法

    当发生冲突时，下一个散列地址的位移量是一个随机数列，即寻找下一个散列地址的公式为：

Hi=(H(key)+round)*H**i*=(*H*(*k**e**y*)+*r**o**u**n**d*)

其中round为随机数其中*r**o**u**n**d*为随机数

-   再 hash 法

注意：用开放定址法处理冲突得到的散列表叫闭散列表。

1.  **闭散列方法**

    closed hashing 也称为开地址方法，open addressing 开放地址法，开放地址法中涵盖了以下两种实现方式；

    -   拉链法（链地址法）

        将所有散列地址相同的记录即 Key 值相同的项目，坠成一个链表，每个链表的头指针存放位置为 Key 值对应的位置。

        举一个小例子：

        ![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/ea6302f7506a464067ed34f20a03c3f8-0)

    -   建立公共溢出区

        散列表包含基本表和溢出表两部分（通常溢出表和基本表的大小相同），将发生冲突的记录存储在溢出表中。

        查找时，如果在基本表里找的到就返回成功，没找到就在溢出区顺序查找，注意这里不再是映射而是顺序查找，放置时也是按照顺序的方式。

        ![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/7b880bd492faa44d617183f8f42f1a64-0)

#### 算法流程

1.  假设给定的值为 K，根据所设定的散列函数 h，计算出散列地址 h(K)；
2.  如果将该地址中的值与 K 比较，若相等则检索成功，跳转到第 5 步；
3.  否则，按建表时设定的处理冲突方法查找探查序列的下一个地址,反复执行并检查
    -   如果某个地址空间未被占用（查找不成功，可以插入），跳转到第 5 步；
    -   如果关键码比较相等（有重复记录，不需要插入）为止 ，跳转到第 5 步；
4.  如果探测完整个 hash 表，都没有进行插入或查找失败，跳转到第 5 步；
5.  end 算法结束。

虽然在解题过程中，如果依据表长质数 h 设置得当，则很少会出现冲突情况，但是基本的解决方法我们也须得掌握，根据笔者的实战经验来看，**公共溢出区**的方式更加简洁高效率（**在冲突次数远小于元素数量时**），所以本节实验中，我们主要掌握如何设置公共溢出区的方法。

至此我们已经学完了散列表的相关知识，下面我们结合**建立公共溢出区**的方式，亲自动手解决一下“弗里的语言”这个问题。

## 题目解析

**第一步，我们需要创建一个散列表和一个公共溢出区：**

```
const long long h=1e8+7; string Value[h+5]; string UpValue[h+5]; 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

**第二步，我们要定义散列表映射函数：**

我们这里介绍一种在算法竞赛中特别常用的字符串映射成数字的方式。

**实现原理：**

1.  将字符串中的每一个字母都看做是一个数字（例：从 a-z ，视为 1-26 ）；

2.  选取两个合适的互质常数 b 和 h，其中 h 要尽可能的大一点，为了降低冲突的概率。b 常用 131，h 常用 1e9+7，这里我们需要设置公共溢出区所以，我们需要随便找一个 string 数组能开出来的数字，这里选取 999983。

3.  定义哈希函数：

    ![图片描述](https://doc.shiyanlou.com/courses/3993/1677054/6c0177932d56e404c063d5c84a1c25aa-0)

**处理方式：**

1.  C 代表一个字符串，用 C =c1 c2 c3 c4..cm 表示该字符串，其中 ci 表示从前向后数的第 i 个字符；
2.  C 当做 b 进制数 来处理，b 是基数；
3.  关于对 h 取模，若 b、h 有公因子，那么不同的字符串取余之后的结果发生冲突的几率将大大大增加（冲突：不同的字符串但会有相同的 hash 值）。

举一个例子：

>   现在有一字符串 S=s1s2s3s4s5*s*1*s*2*s*3*s*4*s*5
>
>   hash[1]=s1*h**a**s**h*[1]=*s*1
>
>   hash[2]=s1∗p+s2*h**a**s**h*[2]=*s*1∗*p*+*s*2
>
>   hash[3]=s1∗p2+s2∗p+s3*h**a**s**h*[3]=*s*1∗*p*2+*s*2∗*p*+*s*3
>
>   hash[4]=s1∗p3+s2∗p2+s3∗p+s4*h**a**s**h*[4]=*s*1∗*p*3+*s*2∗*p*2+*s*3∗*p*+*s*4
>
>   hash[5]=s1∗p4+s2∗p3+s3∗p2+s4∗p+s5*h**a**s**h*[5]=*s*1∗*p*4+*s*2∗*p*3+*s*3∗*p*2+*s*4∗*p*+*s*5

所以 S 的哈希值为 Hash[5]

#### 实现

```
const long long h = 999983; int Hx(string s) {     int n = s.size();    int sum1 = 0;     for (int i = 0; i < n; i++)    {        sum1 = sum1 * 131 % h + (s[i] - 'a' + 1) % h;    }     return (sum1 + h) % h; } 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

在比赛按此方法设计 Hash 函数一般不需要设置冲突的公共溢出区，这里我们为了方便讲解，才进行设置，在比赛中我们不用设置溢出区，所以可以设置很大的 h，避免出现冲突。

**第三步，我们定义查询函数：**

通过散列表顶指针大小即可判断。

```
bool isAt(string s) {    int n=Hx(s);     if(Value[n]=="")         return false;     else if(Value[n]==s)         return true;     else {        for(int i=0;i<UpValueCount;i++)            if(UpValue[n]==s) return true;                    return false;    } } 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

**第四步，定义插入散列表函数：**

1.  按照散列表的映射方式设计即可；
2.  需要传入一个参数来表示放什么数据。

```
bool in(string s) {    int n=Hx(s);    if(Value[n]=="") {        Value[n]=s;        return true;    }    else if(Value[n]==s) return false;    else {        for(int i=0;i<UpValueCount;i++)            if(UpValue[n]==s) return false;         UpValue[UpValueCount++]=s;        return true;    } } 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

**第五步，编写主函数代码：**

主函数代码我们有三种定义方式

-   法一

中规中矩定义法，设置 flag 变量用于跳过找到答案后的输入处理。

```
int main() {     int n;    bool flag = 0;    string ans = "NO";    cin >> n;    for (int i = 0; i < n; i++)    {        string word;        cin >> word;        if (flag)            continue;         if (isAt(word))        {            flag = 1;            ans = word;        }        else        {            in(word);        }    }    cout << ans << endl; } 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

-   法二

由于我们设置的插入函数也具有查询功能，插入成功即为没有重复值，插入失败即为有重复值，我们这里不存在单独查询的操作，所以我们可以将查询省略。

```
 int main() {     int n;    bool flag = 0;    string ans = "NO";    cin >> n;    for (int i = 0; i < n; i++)    {        string word;        cin >> word;        if (flag)            continue;         if (!in(word))        {            flag = 1;            ans = word;        }    }    cout << ans << endl; } 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

-   法三

在法二的基础上，利用 OJ 的特性，OJ 是判定输出的答案是否与答案相同进行判定，当我们知道答案之后直接输出，结束程序那么就会使得程序运行时间大幅度减少。

```
 int main() {     int n;    string ans = "NO";    cin >> n;    for (int i = 0; i < n; i++)    {        string word;        cin >> word;         if (!in(word))        {            cout << word << endl;            return 0;        }    }    cout << ans << endl; } 
```

![copy](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAYAAACtWK6eAAALCElEQVR4Xu2dXchlZRXH/+uiyDAV7SIm+pg+MBvxow9IpNTArFCbQrS6iKhJ+zCwspu8UKOb6MML+8BREypTCCslI6xw1IiCbMopSTCxEiSKagy8qIsVD52hSXrfs85+zrP3c/b6bTjMxbvW86z1X//fu8857569TRwogAJbKmBogwIosLUCAII7UGAbBQAEe6AAgOABFBimAGeQYbqRlUQBAEkyaNocpgCADNONrCQKAEiSQdPmMAUAZJhuZCVRAECSDJo2hykAIMN0IyuJAgCSZNC0OUwBABmmG1lJFOgGEHc/RdJuScce9joiyRx6bfMOSfea2f29Fti6rkkBcfcTJF0s6WxJu1o3y/qDFfi4mX12cPYGJ04CiLs/Q9LHJF0u6ZgN1i9T6a81sx9narj0Ojog7n6upE9KOjWb2Bve78/M7DUb3sPK5Y8KiLt/SNIXVq6ShF4U2Glmj/ZSzBh1jAaIu39A0pfGaIo9mikAIC2kdffXSbqnxdqsOZoCB8zspNF262Sj5mcQdz9R0p2Snt9Jz5QxTIGrzeyqYambmzUGINctvsrdXJWo/JtmdmFGGZoC4u6vlPTzgcI+IukPA3NJW48CZQY/MrNvrGe5zVulNSCrnj3uk3STpPvM7OHNk5OK56ZAM0DcvVwm8tjispGIbinf40aEIWY6BVoC8jZJtwVb22FmjwdjCUOB0RRoCcj1kvYEOuHMERCJkGkUaAnIAUnlK97tjiclvYSzxzTDZ9flCrQE5J+SnrakhP1m9orlZRKBAtMo0AQQd3+RpN8FWrrFzN4ZiCMEBSZRoBUgZ0q6O9ARnz8CIhEynQIAMp327LwBCgDIBgyJEqdTAECm056dN0ABANmAIVHidAoAyHTas/MGKAAgGzAkSpxOAQCZTnt23gAFUgLi7i+XVP6vyvGSXibpuA2Y1ZxLLJccPXToZWb7emk2DSDu/kZJZ0g6j5vU9WK/Lev48+JK8HvM7NYpq509IO5+uqQPS7poSqHZe7AC5bane81s7+AVKhJnDYi7f17SRyr0IbUfBQool4/99mu2gLj7TySd1s98qWQNCvxL0hvGhGSWgLi7r2EYLNGvArvM7MExypsdIO5+syQuoR/DPdPuMQokswLE3T8l6Ypp58buIynwG0kXtj6TzAYQd399uYfTSMNhmz4UKN9uXdKylDkBUm5v+uaWYrF2lwq8quUTsGYBiLu/V9INK4zvL5I+LekBSb8ysz+tkEvomhVw9yMllRtjl1d54tgqz45pehaZCyB3LR7jFhlduXvjbjP7aySYmPEVcPdV5nlQ0gvMrPy79mPjAXH3561wD9/bzOyCtavIgmtXwN2vkXRZcOF3mdnXgrErhc0BkEslXRvsmjs4BoXqIczd90sqTz9edjT7xTcHQD4n6aPLFJTEHVQCIvUU4u7nS7o9UNMvzKxcnb32Yw6AlLvBvzugzDlmVt7bcmyIAu7+dEnlyt6jlpT8qJntbNHWHAApD7svl7BvdzxhZke3EJA12yrg7t+XdM5U850DIOUGdeVGddsd+8zsrLajZPUWCrh7eezblcvWNrMmXm6yqLuPdmdFdweQZe7Z4J8DSOWDIQFkg90fKB1AACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whAAIged0f6BxAACRgk7whcwXkKEkHA2M9z8y+G4jbMsTd75Z05pI19pnZWTX7kDuNArMEpEjp7rdLOn+JrDvM7PEa6QGkRr3+c+cMSPmtXn67b3XsNbNLakcEILUK9p0/W0AWZ5H3S/qMpCOfMoarrfKzx6H1AKRvg9dWN2tAFpCcLOlUSS+U9EdJvzezH9YKByDrUrDvdWYPSGv5OYO0Vnja9QGkUn8AqRSw83QAqRwQgFQK2Hk6gFQOCEAqBew8HUAqBwQglQJ2ng4glQMCkEoBO08HkMoBAUilgJ2nA0jlgACkUsDO0wGkckAAUilg5+kAUjkgAKkUsPN0AKkcEIBUCth5OoBUDghAKgXsPB1AKgcEIJUCdp4OIJUDApBKATtPB5DKAQFIpYCdpwNI5YAApFLAztMBpHJAAFIpYOfpAFI5IACpFLDzdACpHBCAVArYeTqAVA4IQCoF7DwdQCoH5O53STp7yTKPmNmLK7cifQIF3P0aSZct2fqgmR3TojxrseiYa7r7LZLeHtjzpWb2cCCOkI4UcPf9kk5ZUtIBMzupRdlzAORaSZcGxHmPmd0UiCOkEwXc/XhJvw2Uc6eZnRuIWzlkDoBcJenKQOc/NbPTAnGEdKKAu18n6eJAOWu5S+f/22cOgJTTbzkNR44bzOx9kUBiplXA3d8k6XvBKtZ2p86n7rfxgJSG3P3XknYFxXyHmd0ajCVsAgXc/URJB4JbPynp5FafL+cCSOSbjsP1/qqkvZIeMLN/BAdBWGMF3L3covYCSZ9YYavrzSzyNmyFJf8bOhdAyle490raMUCFhyRVPYJhwJ6k/K8Cz5J0gqRnDhDmDDMrs29yzAKQxdusD0r6YhOVWLRXBb5jZm9tWdxsAFlA8m1Ju1sKxtrdKPB3Saeb2YMtK5obIM9efLh7TkvRWLsLBfaY2Y2tK5kVIIuzSHkeyS9bC8f6kypwo5ntGaOC2QGygKR8aL9f0tFjiMgeoyrwZTMrnzdHOWYJyAKSYyV9RdJbRlGSTVor8DdJF5nZD1pvdPj6swXkUJPufoWk8jpiTGHZa60KfKtc0Wtm5RF+ox6zB2RxNnn1AhLOJqPaq2qz8hfymyV9veXfOZZVmAKQw84mz5VUrvEpr52Syrdexw38A9Uybfl5XIEnFg94fUzSoVcBY/L/npAKkPi8iESB/ygAIDgBBbZRAECwBwoACB5AgWEKcAYZphtZSRQAkCSDps1hCgDIMN3ISqIAgCQZNG0OUwBAhulGVhIFACTJoGlzmAIAMkw3spIoACBJBk2bwxQAkGG6kZVEAQBJMmjaHKbAvwGyE7Iy90AbtwAAAABJRU5ErkJggg==)

## 完整解题代码

**C++实现方法：**

```cpp
#include <iostream>
#include <stack>
using namespace std;

const int h = 999983;

string Value[h];

string UpValue[h];

int UpValueCount = 0;

int Hx(string s)
{

    int n = s.size();

    int sum1 = 0;

    for (int i = 0; i < n; i++)
    {

        sum1 = sum1 * 131 % h + (s[i] - 'a' + 1) % h;
    }

    return (sum1 + h) % h;
}

bool isAt(string s)
{
    int n = Hx(s);
    if (Value[n] == "")
        return false;
    else if (Value[n] == s)
        return true;
    else
    {
        for (int i = 0; i < UpValueCount; i++)
            if (UpValue[n] == s)
                return true;

        return false;
    }
}

bool in(string s)
{
    int n = Hx(s);
    if (Value[n] == "")
    {
        Value[n] = s;
        return true;
    }
    else if (Value[n] == s)
        return false;
    else
    {
        for (int i = 0; i < UpValueCount; i++)
            if (UpValue[n] == s)
                return false;

        UpValue[UpValueCount++] = s;
        return true;
    }
}

int main()
{

    int n;
    string ans = "NO";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;

        if (!in(word))
        {
            cout << word << endl;
            return 0;
        }
    }
    cout << ans << endl;
}

Java 实现方法Python 写法最后总结给大家一个小窍门，在解题过程中可以使用：C++ 中有一个 UnorderedMap，可以方便我们的解题过程；Python 和 Java 中都有提前定义好的 Hash 函数，也可以直接使用。实验总结本次实验，我们学习了散列表的实现方式，了解了散列表的原理与基本的实现方式，学了各种的冲突处理方式和散列函数的构造方式，我们还讲了一种竞赛常用的字符串 hash 的方式，我们都要多加练习并熟练使用。
进入下一章节
```
