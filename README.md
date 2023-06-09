# CProject

### 一、运行环境安装
#### 1、[GCC官网安装说明](http://gcc.gnu.org/install/)
- Window GCC [zip包下载连接](https://winlibs.com/)
- 各种系统下载 [Downloads](https://www.mingw-w64.org/downloads/#cygwin)
#### 2、解压GCC的zip包点击到bin目录下
#### 3、复制GCC文件夹到bin目录下
#### 4、配置系统环境变量
```
把复制好的GCC bin路径配置好系统的环境变量中
```
#### 5、打开终端输入命令如下：
```c
gcc -v // 查看是否安装好
```
#### 6、接下来就可以代码编写

##### C语言教程、实例
```c
#include <stdio.h>
 
int main()
{
   /* 我的第一个 C 程序 */
   printf("Hello, World! \n");
   
   return 0;
}
```