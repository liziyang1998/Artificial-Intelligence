#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <ctime>
#include "sudokuMap.h"

using namespace std;

Map initMap;

int fileIO(string inputFile){
    startTime = clock();
    fileName.open(inputFile);
    if (!fileName.is_open()){
        return -1;
    }
    fileName >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fileName >> initMap.Sudoku[i][j];
    initMap.upgrade();

    fileName.close();
    return 0;
}
//遗传算法
//两个个体交叉，只换行，保证每行不重复
pair<Map, Map> Cross(Map X0, Map X1){
    int x = uniform_int_distribution<int>(0, n-2)(rng);
    Map tmp = X0;
    for (int i = x; i < n; i++)
        for (int j = 0; j < n; j++)
            X0.Sudoku[i][j] = X1.Sudoku[i][j];
    for (int i = x; i < n; i++)
        for (int j = 0; j < n; j++)
            X1.Sudoku[i][j] = tmp.Sudoku[i][j];
    return {X0, X1};
}

Map Variation(Map X){
    if (n == k)return X.swapMap();
    else return X.variationMap();
}

int genetic_algorithm(string outputFile){
    fileName.open(outputFile);
    if (!fileName.is_open()){
        return -1;
    }
    //设置初始种群
    Map X[gaSum];
    for (int i = 0; i < gaSum; i++){
        X[i] = initMap;
        X[i].writeMap();
        population.push(X[i]);
    }
    int cnt = 0;
    //迭代
    while(true){
        cnt++;
        //取出优先队列中的种群
        for (int i = 0; i < gaSum; i++){
            X[i] = population.top();
            population.pop();
        }
        //结束标志
        if (X[0].H() == 0)break;
        //后crossFactor进行交叉
        for (int i = gaSum * (1 - crossFactor); i < gaSum; i+=2){
            if (i == gaSum - 1)break;
            auto item = Cross(X[i], X[i+1]);
            X[i] = item.first; X[i+1] = item.second;
        }
        // //随机80%进行交叉
        // for (int i = 0; i < gaSum; i++){
        //     if (i == gaSum - 1)break;
        //     double x = (double)uniform_int_distribution<int>(0, 1000)(rng) / 1000;
        //     if (x <= crossFactor){
        //         auto item = Cross(X[i], X[i+1]);
        //         X[i] = item.first; X[i+1] = item.second;
        //     }
        // }
        //以一定概率变异
        for (int i = 0; i < gaSum; i++){
            double x = (double)uniform_int_distribution<int>(0, 1000)(rng) / 1000;
            if (x < variationFactor){
                X[i] = Variation(X[i]);
            }
        }
        //将新一代种群放入优先队列
        for (int i = 0; i < gaSum; i++)
            population.push(X[i]);
    }
    // cout << cnt << endl;
    X[0].Print();
    endTime = clock();
    fileName << (double)(endTime - startTime) / CLOCKS_PER_SEC << 's' << endl;
    X[0].PrintFile();

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
    //遗传算法
    if (genetic_algorithm(argv[2]) == -1){
        printf("Open File Faill\n");
        return 0;
    }
    return 0;
}