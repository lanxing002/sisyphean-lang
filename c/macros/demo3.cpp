// #include <iostream>

#define ADD(x, y) x + y
#define TOSTR(x, y) #x
#define XTOSTR(x, y) TOSTR(x, y)
#define APPLY_XTOSTR(x) XTOSTR(x)  //出现这个宏定义的原因是，因为参数的宏展开就算出现逗号也会视为一个参数，引用到XTOSTR才会看作两个参数


#define IGNORE(x)  // causes error if invoked with 2 arguments
#define APPLY_IGNORE(x) IGNORE(x)
#define PARENTHESIZED_TO_COMMA(x) ,

// 这里这个函数比较费解
// 当宏调用的时候不是一个括号包裹的表达式，那么APPLY_IGNORE中的PARENTHESIZED_TO_COMMA v将被整体视为一个参数
// 当宏调用是被括号包围的，那么展开时候成为PARENTHESIZED_TO_COMMA （expression），再次展开成为APPLY_IGNORE(,), 预处理器遇到逗号的时候，会视为一个分隔符号
#define vdecltype(v) APPLY_IGNORE(PARENTHESIZED_TO_COMMA v) decltype(v)

int main()
{
    int a =100;
    vdecltype(a) b = 12;
    // vdecltype((a==b)) bb = true;  //error

    int aa PARENTHESIZED_TO_COMMA(v)  bb;
    const char* p1 = TOSTR(132, );
    const char* p2 = XTOSTR(PARENTHESIZED_TO_COMMA v,);
    int add_a = ADD(, );
    
    const char* p2 = APPLY_XTOSTR( PARENTHESIZED_TO_COMMA(v) );

    return 0;
}

/**
*    使用g++编译输出，中间展开结果
*    g++ -E -std=c++2a -O2 demo3.cpp > ./bin/demo3.cpp
* 
*    g++ compile and run
*    g++ -std=c++2a -O2 -Wall -pedantic -pthread demo3.cpp  -o ./bin/demo3  && ./bin/demo3   
*/
