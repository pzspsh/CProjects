## 第17章 优于select的epoll

### 17.1 epoll理解及应用

#### 实现epoll时必要的函数和结构体

​	epoll_create
​	epoll_ctl
​	epoll_wait

#### 基于epoll的回声服务器端

##### 17.2 条件触发和边缘触发

条件触发和边缘触发的区别在于发生事件的时间点
条件触发的事件特性
边缘触发的服务器实现中要注意的两点
实现边缘触发的回声服务器端

##### 程序实例

echo_epollserv.c
echo_EPLTserv.c
echo_EPETserv.c

```
第17章 优于select的epoll
17.1 epoll理解及应用
select函数的缺点：
每次调用 select 函数前都要向操作系统传递监视对象信息；
调用完 select 函数后需要循环获取发生变化的文件描述符；
select 函数可以监视的最大文件描述符数量有限；
前两个原因导致基于 select 函数的 I/O 复用速度较慢。

实现epoll时必要的函数和结构体
epoll 服务器端实现种要用到 3 个函数和一个结构体。
3个函数
epoll_create：创建保存 epoll 文件描述符的空间。
epoll_ctl：向空间注册并注销文件描述符。
epoll_wait：与 select 函数类似，等待文件描述符发生变化。
epoll_event结构体
struct epoll_event
{
    __uint32_t events;
    epoll_data_t data;
}
typedef union epoll_data  // 注意：epoll_data 是一个联合不是结构体
{
    void* ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;    
}
epoll_event 结构体在 epoll_ctl 和 epoll_wait 函数中都要用到，作用分别如下：
在 epoll_ctl 中：指定向 epoll 例程注册文件描述符所关注的事件。用到的是 epoll_event 中的 events 成员。
在 epoll_wait 中：保存发生事件的文件描述符集合。用到的是 epoll_event 中的 data 成员的 fd 成员。

epoll_create
epoll 中由操作系统保存要监视的文件描述符，使用 epoll_create 函数向操作系统申请创建保存文件描述符的空间。这对应使用 select 函数时声明 fd_set 变量来保存要监视的文件描述符。
#include <sys/epoll.h>
int epoll_create(int size);
        // 功能：申请 size 大小的 epoll 例程（调用 epoll_create 函数创建的文件描述符保存空间称为 epoll 例程）
        // 参数：size：申请的 epoll 例程的大小
        // 返回值：成功时返回 epoll 文件描述符，失败时返回 -1。
注意：Linux 2.6.8 之后的内核会完全忽略 size 参数，它会自己根据情况调整 epoll 例程的大小。因此调用时只需将 size 设为 0 即可。


epoll_ctl
生成 epoll 例程后，就要调用 epoll_ctl 函数在其内部注册监视对象文件描述符。
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
        // 功能：在 epoll 例程内部注册要监视的文件描述符
        // 参数：epfd：epoll 例程的文件描述符；op：指定监视对象的添加、删除或更改等操作。fd：需要注册的监视对象文件描述符。event：监视对象的事件类型
        // 返回值：成功时返回 0，失败时返回 -1
参数 op 的可取值：
EPOLL_CTL_ADD：将文件描述符注册到 epoll 例程。
EPOLL_CTL_DEL：从 epoll 例程中删除文件描述符。如果 fd 取此值，则第四个参数 event 应为 NULL。
EPOLL_CTL_MOD：更改注册的文件描述符的关注事件发生情况。
参数 event 的使用：这里用到的是 epoll_event 结构体的 events 成员，events 成员用来指明关注的事件类型。
events 可以指明的事件类型不止 3 种，它的可取值如下：
EPOLLIN：需要读取数据的情况。
EPOLLOUT：输出缓冲为空，可以立即发送数据的情况。
EPOLLPRI：收到 OOB 数据的情况。
EPOLLDHUP：断开连接或半关闭的情况，在边缘触发模式下很有用。
EPOLLERR：发送错误的情况。
EPOLLET：以边缘触发的情况得到事件通知。
EPOLLONESHOT：发送一次事件后，相应的文件描述符不再收到事件通知。因此需要向 epoll_ctl 函数的第二个参数传递 EPOLL_CTL_MOD，再次设置事件。
可以通过位运算同时传递多个上述参数。

epoll_wait
epoll_wait 函数与 select 函数相对应。
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
        // 功能：监视发生事件的文件描述符
        // 参数：epfd：epoll 例程的文件描述符；events：保存发生事件的文件描述符集合的结构体地址；maxevents：最多监听的事件数，必须大于 0；
                // timeout：超时时间，以 ms 为单位。如果 timeout 为 -1，则一直等待到事件发生。（注意类型为 int，和 select 函数中的不同）
        // 返回值：成功时返回发生事件的文件描述符数量，失败时返回 -1。
第二个参数 events 应该是一个 epoll_event 类型数组的地址。数组应该足够大，保证能够容下所有的文件描述符，可以取和第三个参数 maxevents 一样的值。

基于epoll的回声服务器端
见程序实例 echo_epollserv.c。


17.2 条件触发和边缘触发
epoll 中有两种触发方式：条件触发 LT(Level Trigger) 和边缘触发 ET(Edge Trigger)。
条件触发又称电平触发。

条件触发和边缘触发的区别在于发生事件的时间点
条件触发：只要输入缓冲中有数据就一直通知该事件。
边缘触发：只有当输入缓冲收到数据时注册一次该事件，之后即使输入缓冲中还有数据也不会再注册。
epoll 默认以条件触发方式工作。select 函数也是以条件触发方式工作的。

条件触发的事件特性
使用条件触发的例子见 echo_EPLTserv.c

边缘触发的服务器实现中要注意的两点
两点：
通过 errno 变量验证错误原因。
为了完成非阻塞 I/O，更改套接字的属性为非阻塞模式。
errno
Linux 的套接字相关函数返回 -1 以通知发生了错误，同时会设置变量 errno 的值来提示产生错误的原因。
访问 errno 变量需要引入 errno.h，errno 类型为 int，是一个全局变量。
非阻塞模式下，当 read 函数发现输入缓冲中没有数据可读时返回 -1，同时将 errno 的值设为常量 EAGAIN 的值。 
将文件（套接字）改为非阻塞模式
使用 fcntl 函数来完成
#include <fcntl.h>
int fcntl(int filedes, int cmd, ...);
        // 功能：更改或读取文件属性。
        // 参数：filedes：要更改属性的文件描述符；cmd：指明函数调用的目的；...：可变参数，根据 cmd 的不同值会有不同情况。
cmd 的可取值（包括但不限于以下）：
F_GETFL：取此值时，fcntl 函数用于获取文件描述符 filedes 的属性（会返回相应值）。
F_SETFL：更改文件描述符属性。
将文件（套接字）改为非阻塞模式要使用如下的两条语句：
int flag = fcntl(fd, F_GETFL, 0);      // 获取之前的属性
fcntl(fd, F_SETFL, flag|O_NONBLOCK);   // 在此基础上添加非阻塞 O_NONBLOCK 标志。
此后使用 read 对文件 fd 进行读取时都是非阻塞模式。

实现边缘触发的回声服务器端
见程序实例中的 echo_EPETserv.c。


程序实例
echo_epollserv.c
这是基于 epoll 的回声服务器端（工作模式默认情况下是条件出发模式）。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 100
#define EPOLL_SIZE 50
void error_handling(char *buf);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];

    struct epoll_event *ep_events; // 是个 epoll_event 类型的数组，用于存储发生事件的文件描述符的集合。
    struct epoll_event event;      // 是个变量，用于向 epoll 例程注册文集描述符时指明关注的事项。
    int epfd, event_cnt;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    epfd = epoll_create(EPOLL_SIZE); // 创建 epoll 例程
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE); 

    event.events = EPOLLIN; // 关注的是输入事件
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event); // 向 epoll 例程注册套接字

    while (1)
    {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1); // 监视事件的发生
        if (event_cnt == -1)
        {
            puts("epoll_wait() error");
            break;
        }

        for (i = 0; i < event_cnt; i++)
        {
            if (ep_events[i].data.fd == serv_sock) // 服务器套接字用于接受新的连接请求
            {
                adr_sz = sizeof(clnt_adr);
                clnt_sock =
                    accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connected client: %d \n", clnt_sock);
            }
            else // 其他套接字用于提供回声服务
            {
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                if (str_len == 0) // close request!
                {
                    epoll_ctl(
                        epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("closed client: %d \n", ep_events[i].data.fd);
                }
                else
                {
                    write(ep_events[i].data.fd, buf, str_len); // echo!
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}

void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}


echo_EPLTserv.c
以条件触发模式工作的回声服务器端。
此程序和 echo_epollserv.c 差不多，只是将 read 函数的输入缓冲区大小缩小为 4 字节，使得一次 read 不会读完接收缓冲中的数据。由此证明条件触发情况下只要接收缓冲中还有数据，就会一直通知该事件。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 4 // 调用 read 函数时使用 4 字节的缓冲区，保证不会一次读完接收缓存中的内容
#define EPOLL_SIZE 50
void error_handling(char *buf);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];

    struct epoll_event *ep_events;
    struct epoll_event event;
    int epfd, event_cnt;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    epfd = epoll_create(EPOLL_SIZE);
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

    event.events = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

    while (1)
    {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1)
        {
            puts("epoll_wait() error");
            break;
        }

        puts("return epoll_wait"); // 每调用一次 epoll_wait，打印一次。
        for (i = 0; i < event_cnt; i++)
        {
            if (ep_events[i].data.fd == serv_sock)
            {
                adr_sz = sizeof(clnt_adr);
                clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connected client: %d \n", clnt_sock);
            }
            else
            {
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                if (str_len == 0) // close request!
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("closed client: %d \n", ep_events[i].data.fd);
                }
                else
                {
                    write(ep_events[i].data.fd, buf, str_len); // echo!
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}

void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}

echo_EPETserv.c
以边缘触发模式工作的回声服务器端。
注意其中和条件触发模式的区别，主要区别的地方在从套接字读取数据的方式，这里多了个 while 循环。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 50
void setnonblockingmode(int fd); // 此函数用于将文件设为非阻塞模式
void error_handling(char *buf);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];

    struct epoll_event *ep_events;
    struct epoll_event event;
    int epfd, event_cnt;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    epfd = epoll_create(EPOLL_SIZE);
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

    setnonblockingmode(serv_sock); // 将服务器套接字设为非阻塞模式
    event.events = EPOLLIN;        // 监听服务器套接字的输入事件
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

    while (1) {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            puts("epoll_wait() error");
            break;
        }

        puts("return epoll_wait");
        for (i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == serv_sock) {
                adr_sz = sizeof(clnt_adr);
                clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
                setnonblockingmode(clnt_sock);    // 将用于连接客户的套接字设为非阻塞模式
                event.events = EPOLLIN | EPOLLET; // 以边缘触发方式监听用于连接客户的套接字上的输入事件
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connected client: %d \n", clnt_sock);
            }
            else {
                while (1) // 当有输入时，循环读取数据。条件触发中没有此循环。
                {
                    str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                    if (str_len == 0) // close request! {
                        epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                        close(ep_events[i].data.fd);
                        printf("closed client: %d \n", ep_events[i].data.fd);
                        break;
                    }
                    else if (str_len < 0) {
                        if (errno == EAGAIN) // 当没有数据可读时跳出循环，完成读取
                            break;
                    }
                    else {
                        write(ep_events[i].data.fd, buf, str_len); // echo!
                    }
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}

void setnonblockingmode(int fd) {
    int flag = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}
void error_handling(char *buf) {
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

