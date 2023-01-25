#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define STORE 33

int map[16][16];
int n, people;
int directionR[] ={-1, 0, 0, 1}; //  ↑, ←, →, ↓ 
int directionC[] ={0, -1, 1, 0};

vector<pair<int, int> > location;
vector<pair<int, int> > wantedStores;
vector<pair<int, int> > baseCamp;


pair<int, int> setBase(int person);
int getRoutes(int person, int len, pair<int, int> loc);

int main() {
    cin >> n >> people;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> map[i][j]; // 1이면 베이스캠프
            if(map[i][j] == 1){
                baseCamp.push_back(make_pair(i,j));
            }
            // map[i][j] = 0;
        }
    }
    int row, col;
    sort(baseCamp.begin(), baseCamp.end());
    for(int i=1;i<=people;i++){
        cin >> row >> col;
        wantedStores.push_back(make_pair(row, col));
    }


    // for(int minute = 1; ; minute++){ // 각 분에 일어나는 일
    //     if(minute <= people){
    //         // 각 분에 해당하는 사람은 베이스캠프 지정
    //         for(int person = 1; person<minute; person++){
    //             // 올라가 있는 사람
    //         }
    //         // 올라갈 사람

    //     }
    //     else{ // 격자에서

    //     }
    // }

    cout<< "\n" << getRoutes(1, 0, make_pair(2,3)) <<"\n";
    return 0;
}

pair<int, int> setBase(int person){
    
    int length = n * n, tmp;

    for(int i=0;i<4;i++){
        if(length > \
        (tmp = getRoutes(person, 0, make_pair(wantedStores[person -1].first, wantedStores[person-1].second)))){
            length = tmp;
        }
    }
}

int getRoutes(int person, int len, pair<int, int> loc){
    // (wantedStores[person].first, wantedStores[person].second) -> (map[i][j] == 1) 최단거리
    int res = n*n, tmp;
    if(map[loc.first][loc.second] == 1){
        return len;
    }
    else{
        for(int i=0;i<4;i++){
            if(loc.first+directionR[i] >= n || loc.first+directionR[i] < 0 || loc.second+directionC[i] >= n || loc.second+directionC[i] < 0 ||
            map[loc.first+directionR[i]][loc.second+directionC[i]] > 0){
                continue;
            }
            if(res > (tmp = getRoutes(person, len+1, make_pair(loc.first+directionR[i], loc.second+directionC[i])))){
                res = tmp;
            }
        }
    }
    return res;
}