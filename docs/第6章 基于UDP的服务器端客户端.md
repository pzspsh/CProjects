## 第6章 基于UDP的服务器端/客户端

### 6.1 理解UDP

UDP套接字的特点
UDP的高效使用

### 6.2 实现基于UDP的服务器端/客户端

UDP服务器端和客户端均只需 1 个套接字
基于UDP的数据I/O函数
基于UDP的回声服务器端/客户端
UDP客户端套接字的地址分配

### 6.3 UDP的数据传输特性和调用connect函数

存在数据边界的UDP套接字
已连接UDP套接字和未连接UDP套接字
创建已连接UDP套接字

### 6.4 基于Windows的实现

本章的程序实例
uecho_server.c
uecho_client.c
uecho_con_client.c

```
第6章 基于UDP的服务器端/客户端
6.1 理解UDP
UDP套接字的特点
区分 TCP 与 UDP 的一个典型比喻：UDP 好比寄信，TCP 好比打电话：
UDP：寄信前要在信封上填好寄信人和收信人的地址，然后放进邮筒。不能确认对方是否收到信件，并且邮寄过程中新建可能丢失。
TCP：首先要拨打电话号码，打通后才能开始通话，但打通后的通话是可靠的。
TCP 和 UDP 最重要的区别在于流控制。
理解：这里的流控制应该包含了 TCP 的可靠传输、流量控制、拥塞控制等机制，这些机制都是在流上实现的。
TCP 比 UDP 更可靠，UDP 更简洁，速度更快。

UDP的高效使用
网络实时传输多媒体数据一般使用 UDP。
TCP 比 UDP 慢的两个原因：
TCP 数据传输前后要进行连接的建立与释放。
TCP 数据传输过程中为了保证可靠性而添加的流控制。
当收发的数据量小但需要频繁连接时，UDP 的高效体现地更明显。


6.2 实现基于UDP的服务器端/客户端
因为 UDP 是无连接的，所以在编程时不需要调用 listen 函数和 accept 函数。
UDP 套接字编程中只有创建套接字和数据交换两个过程。

UDP服务器端和客户端均只需 1 个套接字
TCP 中，服务器端和客户端的套接字是一对一的关系，服务器端每向一个客户端提供服务，就需要分配一个新的套接字。
而 UDP 的服务器端和客户端均只需 1 个套接字，服务器端只要有一个 UDP 套接字就可以和多台主机通信。

基于UDP的数据I/O函数
UDP 套接字不会保持连接状态，因此每次传输数据时都要添加目标地址信息（相当于寄信前在信封上写收信地址）。
发送 UDP 数据的函数
#include <sys/socket.h>
ssize_t sendto(int sock, void* buff, size_t nbytes, int flags, struct sockaddr* to, socklen_t addrlen);
                // 功能：向 to 中所指明的目标地址发送数据。
                // 参数：sock：UDP 套接字文件描述符; buff：用户保存接收的数据; nbytes：可接收的最大字节数; 
                     // flags：可选项参数，没有则为 0; to：包含目标地址信息; addrlen：包含目标地址信息的结构体变量的长度
                // 返回值：成功时返回接收的字节数，失败时返回 -1。     
接收 UDP 数据的函数
理解：接收端本来是不知道发送端的地址的，但调用完 recvfrom 函数后，发送端的地址信息就会存储到参数 from 指向的结构体中。
#include <sys/socket.h>
ssize_t recvfrom(int sock, void* buff, size_t nbytes, int flags, struct sockaddr* from, socklen_t *addrlen);
                // 功能：从 from 中所指明的地址接收数据。
                // 参数：sock：UDP 套接字文件描述符; buff：待传输的数据; nbytes：待传输的数据长度（单位是字节）; 
                     // flags：可选项参数，没有则为 0; from：用来存储发送端的地址信息; addrlen：包含发送端地址信息的结构体变量的长度
                // 返回值：成功时返回传输的字节数，失败时返回 -1。 

基于UDP的回声服务器端/客户端
见程序实例中的 uecho_server.c 和 uecho_client.c

UDP客户端套接字的地址分配
在 TCP 的客户端中 conncect 函数会自动完成给套接字分配 IP 地址和端口号的过程，UDP 中则是 sendto 函数来完成此功能。
如果调用 sendto 函数时发现尚未给套接字分配地址信息，就会在首次调用 sendto 函数时给套接字分配 IP 地址和端口。


6.3 UDP的数据传输特性和调用connect函数
存在数据边界的UDP套接字
UDP 套接字编程时，接收端输入函数的调用次数必须和发送端输出函数的调用次数相同，这样才能接收完发送端发送的数据。

已连接UDP套接字和未连接UDP套接字
通过 sendto 函数传输数据的过程包括三个阶段：
向 UDP 套接字注册目标 IP 和端口号；（注意：是将 UDP 套接字与目标的地址信息相关联，不是给 UDP 分配地址信息。前者每次 sendto 都会执行，后者只有首次调用且套接字尚未分配地址时才会执行一次）。
传输数据；
删除 UDP 套接字中注册的目标地址信息。
当多次通过 sendto 向同一个目标发送信息时，每次 sendto 都进行上面的步骤 1 和 3，就会很浪费时间。
因此当要长时间与同一主机通信时，将 UDP 变为已连接套接字会提高效率。

创建已连接UDP套接字
使用 connect 函数创建已连接 UDP 套接字。
connect(sock, (struct sockaddr*)&adr, sizeof(adr)); // 注意：adr 是目标的地址信息
使用已连接的 UDP 套接字进行通信时， sendto 函数就不会再执行步骤 1 和步骤 3，每次只要传输数据即可。
并且已连接的 UDP 套接字也可以通过 write、read 函数进行通信。
使用已连接 UPD 套接字的例子见程序实例中的 uecho_con_client.c。


6.4 基于Windows的实现
Windows 下也有 sendto 和 recvfrom 函数，用法和 linux 下的版本一样。


本章的程序实例
uecho_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;
    struct sockaddr_in serv_adr, clnt_adr;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1)
        error_handling("UDP socket creation error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    while (1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr *)&clnt_adr, clnt_adr_sz); // 接收数据同时获取发送端地址
        sendto(serv_sock, message, str_len, 0, (struct sockaddr *)&clnt_adr, clnt_adr_sz);
    }
    close(serv_sock); // 上面的 while 是无限循环，这里的 colse 函数没什么实际意义。
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


uecho_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_sz;

    struct sockaddr_in serv_adr, from_adr;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    while (1)
    {
        fputs("Insert message(q to quit): ", stdout);
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        sendto(sock, message, strlen(message), 0, (struct sockaddr *)&serv_adr, sizeof(serv_adr));
        adr_sz = sizeof(from_adr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr *)&from_adr, &adr_sz);
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


uecho_con_client.c
这是一个使用已连接 UDP 套接字的例子，在前面的 uecho_client.c 的基础上修改得到。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_sz; // 实际上已不需要这个变量

    struct sockaddr_in serv_adr, from_adr; // from_adr 也不再需要

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)); // 将套接字变为已连接套接字

    while (1)
    {
        fputs("Insert message(q to quit): ", stdout);
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        write(sock, message, strlen(message));  // 使用 write 代替了 sendto 函数
        str_len = read(sock, message, sizeof(message) - 1); // 使用 read 代替了 recvfrom 函数

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

