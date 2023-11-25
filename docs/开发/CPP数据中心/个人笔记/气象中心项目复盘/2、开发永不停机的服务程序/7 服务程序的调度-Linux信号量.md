 1)Linux信号
===

## 信号的作用

服务程序运行在后台，如果想让中止它，杀掉不是个好办法，因为程序被杀的时候，程序突然死亡，没有安排善后工作。

如果向服务程序发送一个信号，服务程序收到这个信号后，调用一个函数，在函数中编写善后的代码，程序就可以有计划的退出。

向服务程序发送0的信号，可以检测程序是否存活。

在程序中增加捕获信号的代码，当有信号到达的时候，不要执行系统缺损的动作，在book程序中增加捕获信号的代码，linux信号有64种

9这个信号不能被忽略也不能被捕获

## kill和killall的区别

ps -ef |grep book

与kill命令不同的是，killall 命令可以根据进程名称来杀死进程。kill 命令则先需要找到进程的id.  2、9、14、15、10、12、17这几个重要一些

<img src="images/image-20230418154216636.png" alt="image-20230418154216636" style="zoom: 33%;" />



发送信号
===

Linux操作系统提供了kill和killall命令向程序发送信号，C语言也提供了kill库函数，用于在程序中向其它进程或者线程发送信号。

函数声明：

int kill(pid_t pid, int sig);

kill函数将参数sig指定的信号给参数pid 指定的进程。

参数pid 有几种情况：

1）pid>0 将信号传给进程号为pid 的进程。

2）pid=0 将信号传给和目前进程相同进程组的所有进程，常用于父进程给子进程发送信号，注意，发送信号者进程也会收到自己发出的信号。

3）pid=-1 将信号广播传送给系统内所有的进程，例如系统关机时，会向所有的登录窗口广播关机信息。

sig：准备发送的信号代码，假如其值为零则没有任何信号送出，但是系统会执行错误检查，通常会利用sig值为零来检验某个进程是否仍在运行。

返回值说明： 成功执行时，返回0；失败返回-1，errno被设为以下的某个值。

EINVAL：指定的信号码无效（参数 sig 不合法）。

EPERM：权限不够无法传送信号给指定进程。

ESRCH：参数 pid 所指定的进程或进程组不存在。

实现代码
===

用信号通知服务程序退出的代码

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void EXIT(int sig)
{
 printf("接收到了%d信号,程序将退出。\n",sig);
 //在这里编写善后的代码
 exit(0);
}

int main()
{
//忽略全部的信号，不希望程序被打扰
 for(int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);
//设置2 ctrl+c 和 kill或killall的处理函数
signal(SIGINT,EXIT); signal(SIGTERM,EXIT);

 while(1)
 {
   printf("执行了一次任务 \n");

   sleep(1);
 }
}

```

