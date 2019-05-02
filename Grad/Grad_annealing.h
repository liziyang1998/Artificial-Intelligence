#ifndef GRAD_MBGD
#define GRAD_MBGD
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#define ESP 0.0001
#define esp 1e-6
#define Debug
using namespace std;

class Grad_annealing
{
  private:
    //目标模型参数
    double theta[100] = {0};
    //随机数据
    double X[1000][100];
    double Y[1000];
    //错误数值
    double loss = 0;
    //导数
    double gradOfTheta[100];
    //数据组数和维数
    int n, m;

  public:
    void Init(int a, int b, double c);
    //flag代表是否随机
    void Decline(int maxIterator, double T);
    void Print();
};

void Grad_annealing::Init(int a, int b, double c)
{
    n = a;
    m = b;
    srand(time(NULL)); //随机生成
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            X[i][j] = rand() % 100;
        }
        Y[i] = rand() % 2;
    }
    //初始参数均为c = 0.5
    for (int i = 0; i < m; i++)
        theta[i] = c;
    for (int i = 0; i < n; i++){
        double tmp = 0;
        for (int j = 0; j < m; j++){
            tmp += theta[j] * X[i][j];
        }
        //采用平方来计算误差
        loss += (tmp - Y[i]) * (tmp - Y[i]);
    }
    cout << "原误差     loss = " << loss << endl;
}

void Grad_annealing::Decline(int maxIterator, double T)
{
    int iterator = 0; T/=1000000;
    while (1){
        iterator++;
        loss = 0;
        memset(gradOfTheta, 0, sizeof(gradOfTheta));
        for (int i = 0; i < n; i++){
            double tmp = 0;
            for (int j = 0; j < m; j++){
                tmp += theta[j] * X[i][j];
            }
            for (int j = 0; j < m; j++){
                //导数 = sigma(1-m)( H ( theta1, theta2...thetan ) - Y[i]) * X[i][j]
                gradOfTheta[j] += (tmp - Y[i]) * X[i][j];
            }
            loss += (tmp - Y[i]) * (tmp - Y[i]);
        }
        //退火
        if ((iterator!=0) && (iterator%10 == 0)){
            T /= 2;
        }

        //x = x - step * grad(x) / n
        //目标模型向梯度相反的方向递减
        for (int i = 0; i < m; i++)
            theta[i] -= (T * gradOfTheta[i] / n);

        //损失到一定范围内退出
        if (fabs(loss - ESP) < esp)
            break;
        //达到迭代最大数目退出
        if (iterator >= maxIterator)
            break;
    }
}

void Grad_annealing::Print()
{
#ifdef Debug1
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << X[i][j] << " ";
        }
        cout << "  " << Y[i] << endl;
    }
#endif
    cout << "迭代后误差 "
         << "loss = " << loss << endl;
    for (int i = 0; i < 5; i++){
        cout << "theta[" << i << "] = " << theta[i] << endl;
    }
}

#endif