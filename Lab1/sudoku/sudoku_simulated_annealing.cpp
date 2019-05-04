#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;
fstream fileName;
int n, k;
mt19937 rng;

class Map{
public:
    int Sudoku[20][20];
    void upgrade(){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (Sudoku[i][j]) unChanged[i][j] = true;
    }
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
    Map operatorMap(){
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
    int H(){
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
private:
    bool unChanged[20][20];
};
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

int simulated_annealing(string outputFile){
    fileName.open(outputFile);
    if (!fileName.is_open()){
        return -1;
    }
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
                    //(double)uniform_int_distribution<int>(0, 1000)(rng) / 1000){
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
    if (fileIO(argv[1]) == -1){
        printf("Open File Fall\n");
        return 0;
    }
    if (simulated_annealing(argv[2]) == -1){
        printf("Open File Faill\n");
        return 0;
    }
}