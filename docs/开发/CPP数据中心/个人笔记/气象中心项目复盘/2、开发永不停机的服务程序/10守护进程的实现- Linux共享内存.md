# 1）Linux共享内存

Linux每个进程的内存空间是独立的，互相之间不能访问，共享内存允许多个进程访问同一块内存，是进程之间共享和传递数据的最高效的方式，共享内存的操作只有四个动作

- 调用shmget函数获取或创建共享内存
- 调用shmat函数把共享内存连接到当前进程的地址空间
- 调用shmdt函数把共享内存从当前进程中分离
- 调用shmctl函数删除共享内存



在进程通信中，不管是消息队列，共享内存，还是信号量，每个队对象都有一个key，不同的进程通过key来识别不同的对象，key是一个整数，通常用16进制表示

```c++
#include <sys/ipc.h>
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);    
```



```c#
#include <sys/types.h>
#include <sys/shm.h>
//第一个参数是共享内存的id，
void *shmat(int shmid, const void *shmaddr, int shmflg);

int shmdt(const void *shmaddr);
```

```c++
#include <sys/ipc.h>
#include <sys/shm.h>
int shmctl(int shmid, int cmd, struct shmid_ds *buf); 删除的话第二个填IPC_RMID
```



一、调用shmget函数获取或创建共享内存
===

```c#
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct st_pid
{int  pid;       //进程编号
 char name[51];  //进程名称
};
int main(int argc, char *argv[])
{
 //共享内存的标志
 int shmid;
 if((shmid=shmget(0x5005,sizeof(struct st_pid),0640|IPC_CREAT))==-1)
 { printf("shmget(0x5005) failed\n"); return -1;}
 return 0;
}
```

![image-20230418205315253](images/image-20230418205315253.png)

用ipcrm可以删除共享内存参数

![image-20230418205342215](images/image-20230418205342215.png)

最终实现
===

![image-20230418212919143](images/image-20230418212919143.png)

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct st_pid
{
 int  pid;       //进程编号
 char name[51];  //进程名称
};


int main(int argc, char *argv[])
{
 //共享内存的标志
 int shmid;

//获取或者创建共享内存 键值为0x5005
 if((shmid=shmget(0x5005,sizeof(struct st_pid),0640|IPC_CREAT))==-1)
 { printf("shmget(0x5005) failed\n"); return -1;}

//用于指向共享内存的结构体变量
 struct st_pid *stpid=0;

//把共享内存连接到当前进程的地址空间
//(struct st_pid *) 和 (void *)这里是把数据类型强制转换 
 if((stpid=(struct st_pid *)shmat(shmid,0,0))==(void *)-1)
 {printf("shmat failed\n"); return -1;}

//把共享内存里面的东西读出来
printf("pid=%d,name=%s\n",stpid->pid,stpid->name);

//把当前进程的ID赋给PID成员
 stpid->pid=getpid();
//把name函数的第一个参数赋给name成员
strcpy(stpid->name,argv[1]);

printf("pid=%d,name=%s\n",stpid->pid,stpid->name);
 //把共享内存从当前进程中分离
 shmdt(stpid);

//增加删除共享内存的代码
//if(shmctl(shmid,IPC_RMID,0)==-1)
//{printf("shmctl failed\n"); return -1;}

 return 0;
}
```

