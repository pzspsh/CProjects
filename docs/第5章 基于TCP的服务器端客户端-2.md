## 第5章 基于TCP的服务器端/客户端-2

### 5.1 回声客户端的完美实现

回声客户端的问题
回声客户端问题的解决方法
定义应用层协议
计算器服务器端/客户端示例

### 5.2 TCP原理

TCP套接字中的I/O缓冲

### 5.3 基于Windows的实现

本章的程序实例
echo_client2.c
op_client.c
op_server.c



### 第5章 基于TCP的服务器端/客户端-2　　

#### 5.1 回声客户端的完美实现

回声客户端的问题
下面是服务器端的代码，服务器端是没问题的。

```
while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
    write(clnt_sock, message, str_len);
```



下面是客户端的代码，客户端的代码存在问题。下面的代码假设每次 write 后数据都会立即发送到服务端，服务端也会立即把收到的数据返回给客户端。

```
write(sock, message, strlen(message));
str_men = read(sock, message, BUF_SIZE - 1);
```

理解：回声客户端的问题实际上就是没有考虑拆包和粘包的情况。



##### 回声客户端问题的解决方法

解决方法的核心：提前确定接收数据的大小。
客户端上一次使用 write 从套接字发送了多少字节，紧接着就使用 read 从套接字读取多少字节。
程序示例见 echo_client2.c



##### 定义应用层协议

上面的回声客户端中，提前就知道要接收的数据长度，但是一般是不知道的。这种情况下，要解决拆包和粘包的问题，就要定义应用层协议。
应用层协议实际就是在服务器端/客户端的实现过程中逐步定义的规则的集合。
在应用层协议中可以定好数据边界的表示方法、数据的长度范围等。



##### 计算器服务器端/客户端示例

程序内容见 op_client.c 和 op_server.c。



##### 程序功能

服务器从客户端获得操作数和运算符信息，完成计算后把结果传回客户端。
客户端运行方式及运行结果如图所示：

![https://note.youdao.com/yws/public/resource/8f6540b91e54373c8d0e0807432ce30c/xmlnote/0AA0D39B42594D1FA9A0787D8A3F20AE/66246](https://note.youdao.com/yws/public/resource/8f6540b91e54373c8d0e0807432ce30c/xmlnote/0AA0D39B42594D1FA9A0787D8A3F20AE/66246)



服务器端运行方式及运行结果如图所示：

![https://note.youdao.com/yws/public/resource/8f6540b91e54373c8d0e0807432ce30c/xmlnote/9CA60EC52FDE4896A96A5750FE637F96/66248](https://note.youdao.com/yws/public/resource/8f6540b91e54373c8d0e0807432ce30c/xmlnote/9CA60EC52FDE4896A96A5750FE637F96/66248)



##### 程序实现方法

为了实现以上功能，定义了一个简单的应用层协议，用来约定在服务器端和客户端之间传输数据的规则。
协议内容包括：
	1、客户端用 1 个字节整数形式传递操作数的个数。
	2、客户端向服务器端传送的每个操作数占用 4 字节。
	3、传递完操作数后紧跟着传递一个占用 1 字节的运算符。
	4、服务器端以 4 字节整数向客户端传回运算结果。
	5、客户端得到运算结果后终止与服务器端的连接。



#### 5.2 TCP原理

##### TCP套接字中的I/O缓冲

在使用 read/write 函数对套接字进行读写数据时，实际上读写的是套接字输入/输出缓冲中的内容。

![https://note.youdao.com/yws/public/resource/8f6540b91e54373c8d0e0807432ce30c/xmlnote/39EB49E25B6247108266AC4368E4230D/66270](https://note.youdao.com/yws/public/resource/8f6540b91e54373c8d0e0807432ce30c/xmlnote/39EB49E25B6247108266AC4368E4230D/66270)



##### 套接字 I/O 缓冲的特性：

​	1、I/O 缓冲在每个套接字中单独存在。
​	2、I/O 缓冲在创建套接字时自动生成。
​	3、即使关闭套接字也会继续传递输出缓冲中遗留的数据。
​	4、关闭套接字将丢失输入缓冲中的数据。



### 5.3 基于Windows的实现

略。



#### 本章的程序实例

#### echo_client2.c

此程序是回声客户端的完美实现，它记录了发送给服务器端的数据的长度，然后从套接字读取相同长度的数据。
理解：感觉这个程序并不完美，只解决了拆包的问题，粘包的问题并未完美地解决。

```c
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
    int str_len, recv_len, recv_cnt;
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

        str_len = write(sock, message, strlen(message));  // 发送了 str_len 个字节
        recv_len = 0;

        while (recv_len < str_len)
        {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
            if (recv_cnt == -1)
                error_handling("read() error!");
            recv_len += recv_cnt;
        }
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



#### op_client.c

这是计算器客户端的实现。
注意两个地方：
		1、应用层协议的定义和实现。
		2、在同一个数组中保存并传输多种数据类型的方式：将数组声明为 char 类型，在向数组读写内容时转换指针的类型。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 50
#define OPSZ 4 // 定义每个操作数在 TCP 报文中占用的字节数

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char opmsg[BUF_SIZE]; // opmsg 用来存储要发送的数据，注意是 char 类型数组
    struct sockaddr_in serv_addr;
    int operand_count, result;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
        error_handling("connect() error");
    else
        puts("Connecting..........\n");

    fputs("Operand count: ", stdout);
    scanf("%d", &operand_count);
    opmsg[0] = (char)operand_count; // 数据的第一个字节存储操作数的数量，注意要将变量类型转换为 char。

    for (int i = 0; i < operand_count; i++)
    {
        printf("Operand %d: ", i + 1);
        scanf("%d", (int *)&opmsg[i * OPSZ + 1]); // 从第二个字节开始每四个字节存储一个操作数，向数组存数据时先取地址再转换类型。
    }

    fgetc(stdin);
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[operand_count * OPSZ + 1]); // 再用一个字节存储运算符

    write(sock, opmsg, operand_count * OPSZ + 2); // 发送数据
    read(sock, &result, OPSZ);                    // 接收运算结果：运算结果是一个 4 字节的操作数

    printf("Operation result: %d\n", result);

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



#### op_server.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 50
#define OPSZ 4
void error_handling(char *message);
int calculate(int operand_count, int operands[], char operator);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    int clnt_addr_sz;
    char message[BUF_SIZE];

    if (argc != 2)
    {
        printf("Usage : %s <port>", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_sz = sizeof(clnt_addr);
    for (int i = 0; i < 5; i++)
    {
        if ((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_sz)) == -1)
            error_handling("accept() error");

        int operand_count;
        read(clnt_sock, &operand_count, 1); // 首先读取第 1 个字节，获取操作数的数量

        char operands[BUF_SIZE];
        for (int i = 0; i < operand_count; i++)
        {
            read(clnt_sock, &operands[i * OPSZ], OPSZ); // 根据操作数数量，依次读取操作数
        }

        char operator;
        read(clnt_sock, &operator, 1); // 读取运算符

        int result = calculate(operand_count, (int *)operands, operator);
        write(clnt_sock, (char *)&result, sizeof(result)); // 发送计算结果
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

int calculate(int operand_count, int operands[], char operator)
{
    int result = operands[0];
    switch (operator)
    {
    case '+':
        for (int i = 1; i < operand_count; i++)
            result += operands[i];
        break;
    case '-':
        for (int i = 1; i < operand_count; i++)
            result -= operands[i];
        break;
    case '*':
        for (int i = 1; i < operand_count; i++)
            result *= operands[i];
        break;
    }
    return result;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

