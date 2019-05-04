#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>
#include <cmath>
#include "sudokuMap.h"

using namespace std;

Map initMap;

int fileIO(string inputFile){
    fileName.open(inputFile);
    if (!fileName.is_open()){
        return -1;
    }
    fileName >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fileName >> initMap.Sudoku[i][j];
    initMap.upgrade();
    initMap.writeMap();
    fileName.close();
    return 0;
}
//模拟退火
int simulated_annealing(string outputFile){
    fileName.open(outputFile);
    if (!fileName.is_open()){
        return -1;
    }
    //设置初始温度，最低温度，温度跨度
    double T = 10000;
    double T_min = 0.01;
    double r = 0.9999;
    Map X0 = initMap;
    Map X1 = X0;
    int cnt = 0;
    while(T > T_min){
        cnt++;
        if (X0.H() == 0)break;
        X1 = X0.operatorMap();
        if (X0.H() >= X1.H()){
            X0 = X1;
        }
        else if (exp((X0.H() - X1.H()) / T) > 0.9){
            X0 = X1;
        }
        T = T * r;
    }
    X0.Print();
    X0.PrintFile();

    fileName.close();
    return 0;
}

int main(int argc, char * argv[]){
    if (argc <= 2){
        printf("Paraments Error\n");
        return 0;
    }
    //读文件
    if (fileIO(argv[1]) == -1){
        printf("Open File Fall\n");
        return 0;
    }
    //模拟退火
    if (simulated_annealing(argv[2]) == -1){
        printf("Open File Faill\n");
        return 0;
    }
}