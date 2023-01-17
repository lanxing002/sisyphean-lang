#include <stdio.h>

/*
*  `#`会直接将传入的表达式作为一个字符串，嵌入到代码中。
*
*/

#define WARN_IF(EXP) \
do { if (EXP) \
        fprintf (stderr, "Warning: " #EXP "\n"); } \
while (0)

#define TOSTR(EXP) #EXP
#define PRINTTOSTR(EXP) fprintf(stderr, "ToStr: " TOSTR(EXP) "\n")

int main()
{
    int x = 0;
    WARN_IF (x == 0);
    do 
    { 
        if (x == 0)
            fprintf (stderr, "Warning: " "x == 0" "\n"); 
    } while (0);


    //预处理器，不仅仅是表达式前后加引号
    //1、对于表达式中字符串常量周围的引号，转义    p = "hello -> world"
    //2、对于字符串中或者字符常量中的反斜杠，转义  "world\nhello" -> '\n'
    //3、不在字符串内或者字符串常量内的反斜杠不会转义  '\n' -> "\n", 标准是这样写的，但是测试下来，发现g++会将这个转义，输入字符 "\"\\n\""

    const char p[100] = {};
    PRINTTOSTR(p = "foo");              //->  "p = \"foo\\n\"
    PRINTTOSTR("hello\nworld");         //->  "hello\\nworld"
    PRINTTOSTR('\n\n');                   //->  "\'\\n\'"
    PRINTTOSTR("\n");                   //->  "\"\\n\""

    //4、所有前置和后置的空格将被省略
    PRINTTOSTR(p =           "foo");              //->  "p = \"foo\\n\"
    //5、注释也会被替换为空格
    PRINTTOSTR(p = "before" /*comment test*/);              //->  "p = \"foo\\n\"

    //6、There is no way to convert a macro argument into a character constant.

    //7、If you want to stringize the result of expansion of a macro argument, you have to use two levels of macros.
    /*
    #define xstr(s) str(s)
    #define str(s) #s
    #define foo 4

    str (foo)
        → "foo"
    xstr (foo)
        → xstr (4)
        → str (4)
        → "4"
    */

}

/**
*    使用g++编译输出，中间展开结果
*    g++ -E -std=c++2a -O2 demo1.cpp > ./bin/demo1.c
* 
*    g++ compile and run
*    g++ -std=c++2a -O2 -Wall -pedantic -pthread demo1.cpp  -o ./bin/demo1  && ./bin/demo1   
*/
