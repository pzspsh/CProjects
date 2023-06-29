## 第4章 基于TCP的服务器端/客户端-1

#### 4.1 理解TCP和UDP

#### 4.2 实现基于TCP的服务器端/客户端

服务器端进入等待连接请求状态
服务器端受理客户端连接请求
客户端发起连接请求
基于TCP的服务器端/客户端函数调用关系

#### 4.3 实现迭代服务器端/客户端

实现迭代服务器端
迭代回声服务器端/客户端
回声客户端存在的问题

#### 4.4 基于Windows的实现

本章的程序实例
echo_server.c
echo_client.c



### 第4章 基于TCP的服务器端/客户端-1

#### 4.1 理解TCP和UDP

略，相关知识与《计算机网络》中讲解传输层的那一章重复。

#### 4.2 实现基于TCP的服务器端/客户端

服务器端进入等待连接请求状态

```c
#include <sys/socket.h>
int listen(int sockfd, int backlog);  
                // 功能：将套接字转换为可接收连接的状态。
                // 参数：sock：希望进入等待连接请求状态的套接字文件描述符；backlog：连接请求等待队列的最大长度，最多使 backlog 个连接请求进入队列。
                // 返回值：成功时返回 0，失败时返回 -1
```

等待连接请求状态：当服务器在此状态下时，在调用 accept 函数受理连接请求前，请求会处于等待状态。注意：这里说的是让来自客户端的请求处于等待状态，以等待服务器端受理它们的请求。

连接请求等待队列：还未受理的连接请求在此排队，backlog 的大小决定了队列的最大长度，一般频繁接受请求的 Web 服务器的 backlog 至少为 15。



##### 服务器端受理客户端连接请求

```
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t addrlen);  
                // 功能：受理连接请求等待队列中待处理的连接请求。
                // 参数：sock：服务器套接字的文件描述符；addr：用于保存发起连接请求的客户端地址信息；addrlen：第二个参数的长度。
                // 返回值：成功时返回创建的套接字文件描述符，失败时返回 -1
```

accept 函数会受理连接请求等待队列中待处理的客户端连接请求，它从等待队列中取出 1 个连接请求，创建套接字并完成连接请求。如果等待队列为空，accpet 函数会阻塞，直到队列中出现新的连接请求才会返回。

它会在内部产生一个新的套接字并返回其文件描述符，该套接字用于与客户端建立连接并进行数据 I/O。新的套接字是在 accept 函数内部自动创建的，并自动与发起连接请求的客户端建立连接。

accept 执行完毕后会将它所受理的连接请求对应的客户端地址信息存储到第二个参数 addr 中。



##### 客户端发起连接请求

```
#include <sys/socket.h>
int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);  
                // 功能：请求连接。
                // 参数：sock：客户端套接字的文件描述符；serv_addr：保存目标服务器端地址信息的结构体指针；addrlen：第二个参数的长度（单位是字节）
                // 返回值：成功时返回 0，失败时返回 -1
```



客户端调用 connect 函数后会阻塞，直到发生以下情况之一才会返回：
	1、服务器端接收连接请求。
	2、发生断网等异常情况而中断连接请求。
注意：上面说的”接收连接请求“并不是服务器端调用了 accept 函数，而是服务器端把连接请求信息记录到等待队列。因此 connect 函数返回后并不立即进行数据交换。



#### 基于TCP的服务器端/客户端函数调用关系

![https://note.youdao.com/yws/public/resource/3812118367af6a02a2ff2e89fc824283/xmlnote/245352958B0A472FA87D717EB23D5D3E/63297](https://note.youdao.com/yws/public/resource/3812118367af6a02a2ff2e89fc824283/xmlnote/245352958B0A472FA87D717EB23D5D3E/63297)

客户端只有等到服务器端调用 listen 函数后才能调用 connect 函数，否则会连接失败。
客户端调用 connect 函数和服务器端调用 accept 函数的顺序不确定，先调用的要等待另一方。



```
4.3 实现迭代服务器端/客户端
回声服务器端：它会将客户端传输的字符串数据原封不动地传回客户端，像回声一样。

实现迭代服务器端
调用一次 accept 函数只会受理一个连接请求，如果想要继续受理请求，最简单的方法就是循环反复调用 accept 函数，在前一个连接 close 之后，重新 accept。
在不使用多进程/多线程情况下，同一时间只能服务于一个客户端。

迭代回声服务器端/客户端
迭代回声服务器端与回声客户端的基本运行方式：
服务器端同一时刻只与一个客户端相连接，并提供回声服务。
服务器端依次向 5 个客户端提供服务，然后退出。
客户端接收用户输入的字符串并发送到服务器端。
服务器端将接收到的字符串数据传回客户端，即”回声“。
服务器端与客户端之间的字符串回声一直执行到客户端输入 Q 为止。
具体实现见最后本章的程序实例部分

回声客户端存在的问题
write(sock, message, strlen(message));
str_len = read(sock, message, BUF_SIZE - 1);
在本章的回声客户端的实现中有上面这段代码，它有一个错误假设：每次调用 read、write 函数时都会执行实际的 I/O 操作。
但是注意：TCP 是面向连接的字节流传输，不存在数据边界。所以多次 write 的内容可能一直存放在发送缓存中，某个时刻再一次性全都传递到服务器端，这样的话客户端前几次 read 都不会读取到内容，最后才会一次性收到前面多次 write 的内容。还有一种情况是服务器端收到的数据太大，只能将其分成多个数据包发送给客户端，然后客户端可能在尚未收到全部数据包时旧调用 read 函数。
理解：问题的核心在于 write 函数实际上是把数据写到了发送缓存中，而 read 函数是从接收缓存读取数据。并不是直接对 TCP 连接的另一方进行数据读写。


4.4 基于Windows的实现
将 Linux 平台下的实例转化为 Windows 下的实例，记住以下四点：
通过 WSAStartup、WSACleanup 函数初始化并清除套接字相关库。
把数据类型和变量名切换为 Windows 风格。
数据传输中用 recv、send 函数而非 read、write 函数。
关闭套接字时用 closesocket 函数而非 close 函数。


本章的程序实例
echo_server.c
回声服务器端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock; // 这个 clnt_sock 将用来表示服务器端上真正与客户端相连接的那个套接字
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr, clnt_adr; // 这个 clnt_adr 将用来存储连接的客户端的地址信息，注意和 clnt_sock 表示的对象的不同
    socklen_t clnt_adr_sz;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof(clnt_adr);
    for (int i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
        if (clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i + 1);

        while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
            write(clnt_sock, message, str_len);

        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

echo_client.c
回声客户端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_addr;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");
    else
        puts("Connected...........");

    while (1)
    {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        write(sock, message, strlen(message));
        str_len = read(sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

