#include <iostream>
#include "Grad.h"

using namespace std;

int main()
{
    Grad grad;
    grad.Init(100, 5, 0.5);        // 随机生成数据,最多支持1000组数据，100维,可自主设定初始值
    grad.Decline(1000, 0.00001, 1); //迭代次数和步长
    grad.Print();                  //打印
}