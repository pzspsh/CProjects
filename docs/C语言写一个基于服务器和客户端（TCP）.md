# C语言写一个基于服务器和客户端（TCP）



13 人赞同了该文章

如果想要自己写一个服务器和客户端，我们需要掌握一定的网络编程技术，个人认为，网络编程中最关键的就是这个东西——socket(套接字)。

**socket(套接字)：**简单来讲，socket就是用于描述IP地址和端口，是一个通信链的句柄，可以用来实现不同虚拟机或不同计算机之间的通信。

### ✁ TCP 协议

**TCP 协议：**是一种面向连接的、可靠的、基于字节流的传输层通信协议，由IETF的RFC 793定义。在简化的计算机网络OSI模型中，它完成第四层传输层所指定的功能。

**关键词：**三次握手，可靠，基于字节流。

可能有朋友会问，TCP就这么简单一句话吗?当然不是，TCP作为非常重要的传输协议，细节知识是很多的，细讲起来这一篇文章怕是不够。不过在本篇内容中，我们只需了解他的几个关键词特性，就能很好的理解下面的内容。

![img](https://pic4.zhimg.com/80/v2-ad5689fe6a499315b5f649853e880d47_720w.webp)



### ✁ TCP服务器端和客户端的运行流程

如图，这是一个完整的TCP服务器——客户端的运行流程图，其实我个人认为程序啊，不管哪个语言都是一样，核心就在于算法的设计和函数的调用。那么图中的函数都是什么意思呢?

**1.创建socket**

socket是一个结构体，被创建在内核中

```c
sockfd=socket(AF_INET,SOCK_STREAM,0);   //AF_INT:ipv4, SOCK_STREAM:tcp协议
```

**2.调用bind函数**

将socket和地址(包括ip、port)绑定。

需要定义一个结构体地址，以便于将port的主机字节序转化成网络字节序

```text
struct socka ddr_inmyaddr;  //地址结构体 
```

**bind函数**

```text
bind(sockfd,(structsockaddr*)&myaddr,sizeof(serveraddr))
```

**3.listen监听，将接收到的客户端连接放入队列**

```text
listen(sockfd,8)  //第二个参数是队列长度 
```

**4.调用accept函数，从队列获取请求，返回socket描 述符**

如果无请求，将会阻塞，直到获得连接

```cpp
int fd=accept(sockfd,NULL，NULL);  //这边采用默认参数 
```

**5.调用read/write进行双向通信**

**6.关闭accept返回的socket**

> close(scokfd);

## 下面放出完整代码：

如果你也想学编程，可以来我的[C语言/C++编程学习基地【点击进入】！](https://link.zhihu.com/?target=https%3A//jq.qq.com/%3F_wv%3D1027%26k%3DAi3shoaS)

还有免费的（源码，零基础教程，项目实战教学视频）！

**涉及：**游戏开发、课程设计、常用软件开发、编程基础知识、黑客等等...

```c
/*服务器*/ 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
int main() 
{ 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);//创建套接字 
    if (sockfd < 0) 
    { 
        perror("socket"); 
        return -1; 
    } //创建失败的错误处理 
    printf("socket..............\n"); //成功则打印“socket。。。。” 

    struct sockaddr_in myaddr; //创建“我的地址”结构体 
    memset(&myaddr, 0, sizeof(myaddr)); //对内存清零（保险起见） 
    myaddr.sin_family       = AF_INET; //选择IPV4地址类型 
    myaddr.sin_port         = htons(8888); //选择端口号 
    myaddr.sin_addr.s_addr  = inet_addr("192.168.3.169"); //选择IP地址 

 if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))//绑定套接字 
    { 
        perror("bind"); 
        return -1; 
    } 
    printf("bind..........\n"); 

    if (0 > listen(sockfd, 8))//调用listen对指定端口进行监听 
    { 
        perror("listen"); 
        return -1; 
    } 
    printf("listen............\n"); 

    int connfd = accept(sockfd, NULL, NULL);//使用accept从消息队列中获取请求 
    if (connfd < 0) 
    { 
        perror("accept"); 
        return -1; 
    } 
    printf("accept..............\n"); 
    char buf[100];//定义一个数组用来存储接收到的数据 
    int ret; 
    while (1) 
    { 
        memset(buf, 0, sizeof(buf)); 
        ret = read(connfd, buf, sizeof(buf)); 
        if (0 > ret) 
        { 
            perror("read"); 
            break; 
        }//执行while循环读取数据，当 
        else if (0 == ret) 
        { 
            printf("write close!\n"); 
            break; 
        } 
        printf("recv: "); 
        fputs(buf, stdout);//打印接收到的数据 
    } 
    close(sockfd);//关闭套接字 
    close(connfd);//断开连接 
    return 0; 
} 
/*客户端*/（具体功能和服务器一样，所以不再加注释） 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
int main() 
{ 
 int sockfd; 
    if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0))) 
    { 
        perror("socket"); 
        return -1; 
    } 
    printf("socket...........\n"); 

    struct sockaddr_in srv_addr; 
    memset(&srv_addr, 0, sizeof(srv_addr)); 
    srv_addr.sin_family         = AF_INET; 
    srv_addr.sin_port           = htons(8888); 
    srv_addr.sin_addr.s_addr    = inet_addr("192.168.3.169"); 
    if (0 > connect(sockfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr))) 
    { 
        perror("connect"); 
        return -1; //exit //pthread_exit 
    } 
    printf("connect..............\n"); 
    char buf[100]; 
    int ret; 
    while (1) 
    { 
        printf("send: "); 
        fgets(buf, sizeof(buf), stdin); 
        ret = write(sockfd, buf, sizeof(buf)); 
        if (ret < 0) 
        { 
            perror("write"); 
            break; 
        } 
        if (strncmp(buf, "quit", 4) == 0) 
            break; 
    } 
    close(sockfd); 
    return 0; 
} 
```