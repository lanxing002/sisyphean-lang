#include <iostream>
using namespace std;

#define exprtype(E) decltype((E))

int foo(int a) { return  a * a;}

int main()
{
    //decltype的用法
    
    //-----------------------------------------------------------------
    //1、 如果decltyp的参数是一个unparenthesized id-expression (e.g., x, s.field, S::field)，decltype的作用就是获取它的准确类型

    //decltype(foo) bar2 = foo;  错误，因为这时候将bar2作为一个对象初始化；但是在c++中不能create object of function type
    //但是可以创建一个函数reference、函数指针
    decltype(foo)& bar1 = foo;
    decltype(foo)* bar2 = foo;
    int (*bar3) (int) = foo;

    int arr[] = {1, 2};
    decltype(arr) brr = {2, 3};

    std::cout << bar2(4) << std::endl;
    std::cout << bar1(14) << std::endl;
    std::cout << bar3(2) << std::endl;
    std::cout << brr[0] << brr[1] << std::endl;

    //--------------------------------------------------------------
    //2、当不是第一种情况的时候，一般是一个括号包围的表达式，此时decltype的作用是获取表达式类型的reference
    //If E is a prvalue, then decltype(E) is just T; if E is an lvalue, then decltype(E) is T&; and if E is an xvalue, then decltype(E) is T&&.

    decltype((123)) ra;       // ra是一个int
    decltype((ra)) rb = ra;   //rb 是int reference

}

/**
*    g++ compile and run
*    g++ -std=c++2a -O2 -Wall -pedantic -pthread delctype_demo.cpp  -o ./bin/delctype_demo  && ./bin/delctype_demo   
*/