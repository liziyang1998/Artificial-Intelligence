#ifndef SUDOKUMAP_H
#define SUDOKUMAP_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <random>
#include <queue>

using namespace std;

fstream fileName;
int n, k;
mt19937 rng;

class Map{
public:
    int Sudoku[20][20];
    //更新哪些位置不能更改
    void upgrade(){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (Sudoku[i][j]) unChanged[i][j] = true;
    }
    //随机写入数据，保证每行不存在重复元素
    void writeMap(){
        bool flag[20];
        int cnt = 1;
        for (int i = 0; i < n; i++){
            memset(flag, 0, sizeof(flag));
            for (int j = 0; j < n; j++)
                if (unChanged[i][j]) flag[Sudoku[i][j]] = true;
            for (int j = 0; j < n; j++){
                if (!unChanged[i][j]){
                    int tmp = uniform_int_distribution<int>(1, k)(rng);
                    while(flag[tmp]){
                        tmp = uniform_int_distribution<int>(1, k)(rng);
                    }
                    Sudoku[i][j] = tmp;
                    flag[tmp] = true;
                }
            }
        }
    }
    void Print(){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                cout << Sudoku[i][j] << " ";
            cout << endl;
        }
    }
    void PrintFile(){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                fileName << Sudoku[i][j] << " ";
            fileName << endl;
        }
    }
    //随机交换某行中的两个可更改的数据
    //保证该行中不会出现重复
    Map swapMap(){
        int col, row1, row2;
        Map ret;
        while(true){
            col = uniform_int_distribution<int>(0, n-1)(rng);
            row1 = uniform_int_distribution<int>(0, n-1)(rng);
            row2 = uniform_int_distribution<int>(0, n-1)(rng);
            if (row1 == row2)continue;
            if ((!unChanged[col][row1]) && (!unChanged[col][row2]))
                break;
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ret.Sudoku[i][j] = Sudoku[i][j], ret.unChanged[i][j] = unChanged[i][j];
        swap(ret.Sudoku[col][row1], ret.Sudoku[col][row2]);
        return ret;
    }
    //随机更换某个位置的值
    Map variationMap(){
        int col, row;
        Map ret;
        while(true){
            col = uniform_int_distribution<int>(0, n-1)(rng);
            row = uniform_int_distribution<int>(0, n-1)(rng);
            if (!unChanged[col][row])break;
        }
        bool flag[20];
        memset(flag, 0, sizeof(flag));
        for (int i = 0; i < n; i++)
            flag[Sudoku[col][i]] = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ret.Sudoku[i][j] = Sudoku[i][j], ret.unChanged[i][j] = unChanged[i][j];
        for (int i = i; i <= k; i++)
            if (!flag[i])
                ret.Sudoku[col][row] = i;
        return ret;
    }
    //评估函数，每列中重复元素个数，不用考虑每行，随机填充时保证每行不存在重复元素
    int H() const{
        int ret = 0;
        bool flag[20];
        for (int i = 0; i < n; i++){
            memset(flag, 0, sizeof(flag));
            for (int j = 0; j < n; j++){
                if (!flag[Sudoku[j][i]]) flag[Sudoku[j][i]] = true;
                else ret++;
            }
        }
        return ret;
    }
    bool operator < (const Map &A)const{
        return H() > A.H();
    }
private:
    //外界不可更改
    //保存哪些位置不可更改
    bool unChanged[20][20];
};

const int gaSum = 50;
double crossFactor = 0.9;
double variationFactor = 0.05;
priority_queue<Map> population, tmpPopulation;
clock_t startTime, endTime;

#endif