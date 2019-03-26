#include <iostream>
#include "Grad_annealing.h"

using namespace std;

int main()
{
    Grad_annealing grad;
    grad.Init(100, 5, 0.5);         // 随机生成数据,最多支持1000组数据，100维,可自主设定初始值
    grad.Decline(1000, 100); //迭代次数和温度
    grad.Print();                   //打印
}