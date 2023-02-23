#include <iostream>
#include <utility>
#include <vector>
#define SZ 4

using namespace std;

class Monster {
  public:
    // pair<int, int> loc;
    int d;      // 방향
    int status; // 시체인지(<0) 살아있는지(1) 알상태인지(0)
    // int r, int c,
    Monster(int d, int status = 1) {
        // this->loc = make_pair(r, c);
        this->d = d;
        this->status = status;
    }
};

void clone();
void debug();
void move();
pair<int, int> decideLoc(pair<int, int> nowLoc, Monster m);
bool isInRange(pair<int, int> point);
pair<int, int> findAltLoc(pair<int, int> nowLoc, Monster m);
void movePacMan();

// ↑, ↖, ←, ↙, ↓, ↘, →, ↗
int dr[] = {0, -1, -1, 0, 1, 1, 1, 0, 0};
int dc[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

vector<Monster> map[5][5];
vector<Monster> tmp[5][5];
pair<int, int> pacMan;

int main() {
    int monsterCnt, turn;
    cin >> monsterCnt >> turn;
    int r, c, d;
    cin >> r >> c;
    pacMan = make_pair(r, c);
    for (int i = 1; i <= monsterCnt; i++) {
        cin >> r >> c >> d;
        map[r][c].push_back(Monster(d, 1));
    }

    // for(int t = 1;t<=turn;t++){
    clone();      // 1. 몬스터 복제
    move();       // 2. 몬스터 이동
    movePacMan(); // 3. 팩맨 이동
    debug();
    // }
}

void movePacMan() {
    int dr[] = {-1, 1, 0, 0}; // 상하좌우
    int dc[] = {0, 0, -1, 1};

    pair<int, int> moveTo;
    bool isGood;

    int res, tmp;
    vector<pair<int, int> /**/> finalRoutes;
    int _1,_2,_3;
    for (_1 = 0; _1 < 4; _1++) {     // (pacMan + dr[_1], pacMan + dr[_1])
        for (_2 = 0; _2 < 4; _2++) { // (pacMan + dr[_2], pacMan + dr[_2])
            for (_3 = 0; _3 < 4; _3++) {
                tmp = 0;
                int moveD[] = {_1, _2, _3};
                isGood = true;
                for (int i = 0; i < 3; i++) {
                    moveTo = make_pair(pacMan.first + dr[moveD[i]],
                                       pacMan.second + dc[moveD[i]]);
                    if (!isInRange(moveTo)) {
                        isGood = false;
                        break;
                    }
                    for (Monster m : map[moveTo.first][moveTo.second]) {
                        if (m.status > 0) {
                            tmp++;
                        }
                    }
                }
            }
            if (isGood && (res < tmp)) {
                int moveD[] = {_1, _2, _3};
                res = tmp;
                finalRoutes.clear();
                for (int i = 0; i < 3; i++) {
                    finalRoutes.push_back(make_pair(pacMan.first + dr[moveD[i]],
                                       pacMan.second + dr[moveD[i]]));
                }
            }
        }
    }

    for(int i=0;i<3;i++){
        printf("*(%d,%d)\n",finalRoutes[i].first,finalRoutes[i].second);
    }
}

void move() {
    // 방향 d는 1부터 순서대로 ↑, ↖, ←, ↙, ↓, ↘, →, ↗
    memset(tmp, 0, sizeof(tmp));
    for (int r = 1; r <= SZ; r++) {
        for (int c = 1; c <= SZ; c++) {
            if (!map[r][c].empty()) {
                for (int i = 0; i < map[r][c].size(); i++) {
                    if (map[r][c][i].status > 0) {
                        pair<int, int> nowLoc = make_pair(r, c);
                        pair<int, int> moveTo = decideLoc(nowLoc, map[r][c][i]);
                        if ((nowLoc.first != moveTo.first) ||
                            (nowLoc.second != moveTo.second)) {
                            tmp[moveTo.first][moveTo.second].push_back(
                                Monster(map[r][c][i].d));
                            map[r][c].erase(map[r][c].begin() + i);
                        }
                    }
                }
            }
        }
    }

    for (int r = 1; r <= SZ; r++) {
        for (int c = 1; c <= SZ; c++) {
            if (tmp[r][c].empty() == false) {
                map[r][c] = tmp[r][c];
            }
        }
    }
}

pair<int, int> findAltLoc(pair<int, int> nowLoc, Monster m) {
    // 방향 d는 1부터 순서대로 ↑, ↖, ←, ↙, ↓, ↘, →, ↗
    pair<int, int> moveTo;
    bool isGood;

    for (int i = (m.d + 1) % 9; i != m.d; i = (i + 1) % 9) {
        if (i == 0) {
            continue;
        }
        moveTo = make_pair(nowLoc.first + dr[i], nowLoc.second + dc[i]);
        if (isInRange(moveTo) && !((moveTo.first == pacMan.first) &&
                                   (moveTo.second == pacMan.second))) {
            if (map[moveTo.first][moveTo.second].empty() == true) {
                m.d = i;
                return moveTo;
            }
            isGood = true;
            for (Monster m : map[moveTo.first][moveTo.second]) {
                if (m.status < 0) {
                    isGood = false;
                    break;
                }
            }
            if (isGood) {
                return moveTo;
            }
        }
    }
    return nowLoc;
}

pair<int, int> decideLoc(pair<int, int> nowLoc, Monster m) {
    // 움직일 위치 결정
    pair<int, int> moveTo =
        make_pair(nowLoc.first + dr[m.d], nowLoc.second + dc[m.d]);

    if (isInRange(moveTo) &&
        !((moveTo.first == pacMan.first) && (moveTo.second == pacMan.second))) {
        if (map[moveTo.first][moveTo.second].empty()) {
            return moveTo;
        }
        for (Monster m : map[moveTo.first][moveTo.second]) {
            if (m.status < 0) {
                return findAltLoc(nowLoc, m);
            }
        }
        return moveTo;
    }
    return findAltLoc(nowLoc, m);
}

bool isInRange(pair<int, int> point) {
    return (1 <= point.first && point.first <= SZ && 1 <= point.second &&
            point.second <= SZ);
}

void clone() {
    for (int r = 1; r <= SZ; r++) {
        for (int c = 1; c <= SZ; c++) {
            if (map[r][c].empty() == false) {
                for (Monster m : map[r][c]) {
                    map[r][c].push_back(Monster(m.d, 0));
                }
            }
        }
    }
}

void debug() {
    int egg, monster, died;
    for (int r = 1; r <= SZ; r++) {
        for (int c = 1; c <= SZ; c++) {
            egg = monster = died = 0;
            if (map[r][c].empty() == false) {
                for (Monster m : map[r][c]) {
                    if (m.status == 0) {
                        egg++;
                    } else if (m.status == 1) {
                        monster++;
                    } else {
                        died++;
                    }
                }
            }
            printf("[알:%d, 시체:%d, 몬스터 : %d] ", egg, died, monster);
        }
        cout << "\n";
    }
    printf("pacman : (%d, %d) \n ", pacMan.first, pacMan.second);
}