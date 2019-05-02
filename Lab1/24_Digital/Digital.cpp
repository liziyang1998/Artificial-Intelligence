#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <set>
#include <cmath>
#include <ctime>

using namespace std;
using numBer = int;
#define INF 999999999

class Map{
public:
    int A[5][5];
	int x, y, g, f;
	string Answer;
    size_t genSeed() const{
        return HASH();
    }
	int H1() const{
		int cnt = 1;
		int ret = 0;
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++){
				if (A[i][j] != cnt)ret++;
				cnt++;
				cnt %= 25;				
			}
		}
		return ret;
	}
	int H2() const{
		int cnt = 1;
		double ret = 0;
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++){
				if (A[i][j] != cnt){
					ret++;
					ret += (double)(abs(i - getPos(A[i][j]).first) + abs(j - getPos(A[i][j]).second)) * 0.4;
					// ret += (double)(sqrt((i - getPos(A[i][j]).first) * (i - getPos(A[i][j]).first) + (j - getPos(A[i][j]).second) * (j - getPos(A[i][j]).second))) * 0.3;
				}
				cnt++;
				cnt %= 25;
			}
		}
		return (int)(ret * 3);
	}
	bool operator < (const Map A)const{
		return f > A.f;
	}
	void Print(){
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++)
				cout << A[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}
private:
	size_t HASH() const{
		hash<string>h;
        string Str;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
				Str += char(A[i][j]);
		size_t ret = h(Str);
		return ret;
	}
	pair<int, int> getPos(int num) const{
		if (num == 0)return {4, 4};
		num--;
		return {num / 5, num % 5};
	}
};

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
char Direction[4] = {'R', 'L', 'D', 'U'};
//R L D U
//open
priority_queue<Map>F;
//close
set<size_t>visited;

bool Unicom(int x, int y){
	if (x == 0 && y == 2)return true;
	if (x == 4 && y == 2)return true;
	if (x == 2 && y == 0)return true;
	if (x == 2 && y == 4)return true;
	return false;
}

int cnt = 0;
pair<string, int> Digital(Map initMap){
    F.push(initMap);
	size_t n = initMap.genSeed();
	visited.insert(n);
	int factory = 1;
    while(!F.empty()){
		cnt++;
        auto item = F.top();
		F.pop();
		size_t n = item.genSeed();
		visited.insert(n);
		if(item.H2() == 0){
			return {item.Answer, item.g};
		}
		factory = item.g / 10 + 2;
		// cout << item.g <<  " ";
        int x = item.x;
        int y = item.y;
        for (int i = 0; i < 4; i++){
            int tx = x + dx[i];
            int ty = y + dy[i];
			Map newMap;
			if (Unicom(x, y)){
				tx = (tx + 5) % 5;
				ty = (ty + 5) % 5;
				for (int i = 0; i < 5; i++)
					for (int j = 0; j < 5; j++)
						newMap.A[i][j] = item.A[i][j];
				newMap.Answer = item.Answer + Direction[i];
				newMap.g = item.g + 1;
				swap(newMap.A[x][y], newMap.A[tx][ty]);
				newMap.x = tx; newMap.y = ty;
				size_t n = newMap.genSeed();
				if (visited.count(n))continue;
				newMap.f = newMap.g + newMap.H2() * factory;
				F.push(newMap);
			}
            else if (tx < 0 || tx >= 5 || ty < 0 || ty >= 5)
                continue;
			else{
				for (int i = 0; i < 5; i++)
					for (int j = 0; j < 5; j++)
						newMap.A[i][j] = item.A[i][j];
				newMap.Answer = item.Answer + Direction[i];
				newMap.g = item.g + 1;
				swap(newMap.A[x][y], newMap.A[tx][ty]);
				newMap.x = tx; newMap.y = ty;
				size_t n = newMap.genSeed();
				if (visited.count(n))continue;
				newMap.f = newMap.g + newMap.H2() * factory;
				F.push(newMap);
			}
        }
    }
}

pair<string, int> ID_Digital(Map initMap){
	int deepLimit = initMap.H2();
	int nextDeepLimit;
	while(deepLimit < INF){
		nextDeepLimit = INF;
		while(!F.empty())F.pop();
		visited.clear();

		F.push(initMap);
		size_t n = initMap.genSeed();
		visited.insert(n);
		while(!F.empty()){
			cnt++;
			auto item = F.top();
			F.pop();
			size_t n = item.genSeed();
			visited.insert(n);

			if (item.H2() + item.g > deepLimit){
				nextDeepLimit = min(nextDeepLimit, item.H2() + item.g);
			}
			else{
				if(item.H2() == 0){
					return {item.Answer, item.g};
				}
				int x = item.x;
				int y = item.y;
				for (int i = 0; i < 4; i++){
					int tx = x + dx[i];
					int ty = y + dy[i];
					Map newMap;
					if (Unicom(x, y)){
						tx = (tx + 5) % 5;
						ty = (ty + 5) % 5;
						for (int i = 0; i < 5; i++)
							for (int j = 0; j < 5; j++)
								newMap.A[i][j] = item.A[i][j];
						newMap.Answer = item.Answer + Direction[i];
						newMap.g = item.g + 1;
						swap(newMap.A[x][y], newMap.A[tx][ty]);
						newMap.x = tx; newMap.y = ty;
						size_t n = newMap.genSeed();
						if (visited.count(n))continue;
						newMap.f = newMap.g + newMap.H2();
						F.push(newMap);
					}
					else if (tx < 0 || tx >= 5 || ty < 0 || ty >= 5)
						continue;
					else{
						for (int i = 0; i < 5; i++)
							for (int j = 0; j < 5; j++)
								newMap.A[i][j] = item.A[i][j];
						newMap.Answer = item.Answer + Direction[i];
						newMap.g = item.g + 1;
						swap(newMap.A[x][y], newMap.A[tx][ty]);
						newMap.x = tx; newMap.y = ty;
						size_t n = newMap.genSeed();
						if (visited.count(n))continue;
						newMap.f = newMap.g + newMap.H2();
						F.push(newMap);
					}
				}
			}
		}
		deepLimit = nextDeepLimit;
	}
}

int main(int argc, char * argv[]){
	clock_t start = clock();
    fstream fileName;
    fileName.open(argv[1]);
	if (!fileName.is_open()){
		cout << "Read File False" << endl;
		return 0;
	}
	Map initMap;
    int startX, startY;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            fileName >> initMap.A[i][j];
            if (initMap.A[i][j] == 0){
				initMap.x = i; initMap.y = j;
            }
        }
    }
	initMap.Answer = '\0';
	initMap.g = 0;
    auto item = Digital(initMap);
	cout << cnt << endl;
	cout << item.first << " " << item.second << endl;
	clock_t end = clock();
	cout << (double)(end - start) / CLOCKS_PER_SEC << 's' << endl;
}