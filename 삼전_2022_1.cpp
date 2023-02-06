#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#define STORE 33

int map[16][16];
int routes[16][16];
bool isDone[16];
int directionR[] = {-1, 0, 0, 1}; //  ↑, ←, →, ↓
int directionC[] = {0, -1, 1, 0};
int n, people;

vector<pair<int, int>/**/> location(16);
vector<pair<int, int>/**/> wantedStores;
vector<pair<int, int>/**/> baseCamp;

void setRoutes(int person, pair<int, int> baseCamp);
bool isAllDone();

int main() {
    cin >> n >> people;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j]; // 1이면 베이스캠프
            if (map[i][j] == 1) {
                baseCamp.push_back(make_pair(i, j));
            }
            // map[i][j] = 0;
        }
    }
    int row, col;
    sort(baseCamp.begin(), baseCamp.end());
    for (int i = 1; i <= people; i++) {
        cin >> row >> col;
        wantedStores.push_back(make_pair(row, col));
    }
    for (int minute = 1;; minute++) { // 각 분에 일어나는 일
        cout << minute << "\n";
        if (isAllDone()) {
            cout << minute;
            return 0;
        }
        if (minute <= people) {
            // 각 분에 해당하는 사람은 베이스캠프 지정
            for (int person = 1; person < minute; person++) {
                // 올라가 있는 사람
                if (!isDone[person]) {
                    cout <<"\n";
                    for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                            cout << routes[i][j] <<" ";
                        }
                        cout <<"\n";
                    }
                    setRoutes(minute, make_pair(0, 0));
                    pair<int, int> moveTo;
                    pair<int, int> curLoc = location[person];
                    int len = n * n;
                    for (int dir = 0; dir < 4; dir++) {
                        if (curLoc.first + directionR[dir] < 0 ||
                            curLoc.first + directionR[dir] >= n ||
                            curLoc.second + directionC[dir] < 0 ||
                            curLoc.second + directionC[dir] >= n) {
                            continue;
                        }
                        if (routes[curLoc.first + directionR[dir]]
                                  [curLoc.second + directionC[dir]] < len) {
                            len = routes[curLoc.first + directionR[dir]]
                                        [curLoc.second + directionC[dir]];
                            moveTo = make_pair(curLoc.first + directionR[dir],
                                               curLoc.second + directionC[dir]);
                        }
                    }
                    location[person] = moveTo;
                    if (moveTo.first == wantedStores[person].first &&
                        moveTo.second == wantedStores[person].second) {
                        map[moveTo.first][moveTo.second] = -1;
                        isDone[person] = true;
                    }
                }
            }
            // 베이스캠프 지정 (minute번째 사람)
            setRoutes(minute, make_pair(0, 0));
            pair<int, int> moveTo;
            int len = n * n;
            for (int r = 1; r <= n; r++) {
                for (int c = 1; c <= n; c++) {
                    if (map[r][c] == 1 && routes[r][c] < len) {
                        len = routes[r][c];
                        moveTo = make_pair(r, c);
                    }
                }
            }
            map[moveTo.first][moveTo.second] = -1;
            location[minute] = moveTo;

        } else { // 격자에서
            for (int person = 1; person < people; person++) {
                if (!isDone[person]) {
                    setRoutes(minute, make_pair(0, 0));
                    pair<int, int> moveTo;
                    pair<int, int> curLoc = location[person];
                    int len = n * n;
                    for (int dir = 0; dir < 4; dir++) {
                        if (curLoc.first + directionR[dir] < 0 ||
                            curLoc.first + directionR[dir] >= n ||
                            curLoc.second + directionC[dir] < 0 ||
                            curLoc.second + directionC[dir] >= n) {
                            continue;
                        }
                        if (routes[curLoc.first + directionR[dir]]
                                  [curLoc.second + directionC[dir]] < len) {
                            len = routes[curLoc.first + directionR[dir]]
                                        [curLoc.second + directionC[dir]];
                            moveTo = make_pair(curLoc.first + directionR[dir],
                                               curLoc.second + directionC[dir]);
                        }
                    }
                    location[person] = moveTo;
                    if (moveTo.first == wantedStores[person].first &&
                        moveTo.second == wantedStores[person].second) {
                        map[moveTo.first][moveTo.second] = -1;
                        isDone[person] = true;
                        cout << "도착 : " << person << "\n";
                    }
                }
            }
        }
    }
    return 0;
}
bool isAllDone() {
    for (int i = 0; i < people; i++) {
        if (isDone[i] == false) {
            return false;
        }
    }
    return true;
}
void setRoutes(int person, pair<int, int> baseCamp) { // BFS
    // (wantedStores[person].first, wantedStores[person].second) -> (map[i][j]
    // == 1) 최단거리 (=편의점 -> 현재위치/베이스캠프/loc)

    // 현재 코드 : 모든 곳 방문 - 시간초과나면 loc 활용하는 걸로 변경
    pair<int, int> start = wantedStores[person];
    bool visited[16][16] = {0};
    memset(routes, 0, sizeof(routes)); //// ?
    deque<pair<int, int>/**/> queue;
    queue.push_back(start);
    while (!queue.empty()) {
        pair<int, int> tmp = queue.front();
        queue.pop_front();
        // if(!visited[tmp.first][tmp.second]){
        visited[tmp.first][tmp.second] = true;
        // }
        for (int dir = 0; dir < 4; dir++) {
            if (tmp.first + directionR[dir] < 0 ||
                tmp.first + directionR[dir] >= n ||
                tmp.second + directionC[dir] < 0 ||
                tmp.second + directionC[dir] >= n ||
                visited[tmp.first + directionR[dir]]
                       [tmp.second + directionC[dir]] ||
                map[tmp.first + directionR[dir]][tmp.second + directionC[dir]] <
                    0) { // 지나가지 못하는 곳(베이스캠프/도착 편의점) = 0
                continue;
            }
            // visited[tmp.first+directionR[dir]][tmp.second+directionC[dir]] =
            // true;
            queue.push_back(make_pair(tmp.first + directionR[dir],
                                      tmp.second + directionC[dir]));
            routes[tmp.first + directionR[dir]][tmp.second + directionC[dir]] =
                routes[tmp.first][tmp.second] + 1;
        }
    }
}