#include <stdio.h>
#include <iostream>
#include <array>

/*
*  `##` 会完成两个token的拼接
*
*/

// empty function
#define VOIDFUN(NAME) void NAME ## _command() {std::cout << #NAME << std::endl;}

#define CONCATETEST(NAME1, NAME2) NAME1 ## NAME2

//concatenation 
#define COMMAND(NAME) {#NAME, NAME /*使用的输入参数*/ ## _command /*使用固定值，## 前后都可以使用固定值，但是没有必要*/}

struct Command
{
    const char *name;
    void (*function) (void);
};

VOIDFUN(start)
VOIDFUN(end)


int main()
{
    /*
    *  目标是对于每一个command，不用重复输入它的function name
        struct command commands[] =
        {
            { "quit", quit_command },
            { "help", help_command },
        };
    */
    Command commands[] = 
    {
        COMMAND(start), 
        COMMAND(end), 
    };

    for(auto it = std::begin(commands); it != std::end(commands); it++)
    {
        it->function();
    }

    int a = 0;
    // CONCATETEST(a, 1); 处理器会检查拼接结果，并报告相应错误， a1 error-没有声明
}

/**
*    使用g++编译输出，中间展开结果
*    g++ -E -std=c++2a -O2 demo2.cpp > ./bin/demo2.cpp
* 
*    g++ compile and run
*    g++ -std=c++2a -O2 -Wall -pedantic -pthread demo2.cpp  -o ./bin/demo2  && ./bin/demo2   
*/
