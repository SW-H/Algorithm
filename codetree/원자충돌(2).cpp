#include <iostream>
#include <vector>
using namespace std;

int n, atomCnt, t;
// ↑, ↗, →, ↘, ↓, ↙, ←, ↖
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
struct Atom {
    int status;  // 1정상, 0삭제됨
    int m;
    int s;
    int d;
};

vector<Atom> map[51][51];
Atom pool[2501];
int ATOM_CNT = 0;

void move();
int createAtom(int m, int s, int d);
void debug();
void crush();
int calcRes();

int main() {
    cin >> n >> atomCnt >> t;
    int r, c, m, s, d;
    int idx, res = 0;
    for (int atom = 1; atom <= atomCnt; atom++) {
        cin >> r >> c >> m >> s >> d;
        idx = createAtom(m, s, d);
        map[r - 1][c - 1].push_back(pool[idx]);
    }

    for (int sec = 1; sec <= t; sec++) {
        move();
        crush();
    }
    cout << calcRes();
}
int calcRes() {
    int res = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (!map[r][c].empty()) {
                for (auto atom : map[r][c]) {
                    if (atom.status > 0) {
                        res += atom.m;
                    }
                }
            }
        }
    }
    return res;
}

void crush() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (map[r][c].size() > 0) {
                int m = 0, s = 0, d = 0, actualSz = 0;
                bool isEven = false, isOdd = false;
                for (auto atom : map[r][c]) {
                    if (atom.status > 0) {
                        actualSz++;
                    }
                }
                if (actualSz >= 2) {
                    for (int i = 0; i < map[r][c].size(); i++) {
                        if (map[r][c][i].status > 0) {
                            m += map[r][c][i].m;
                            s += map[r][c][i].s;
                            if (map[r][c][i].d % 2 == 0) {
                                isEven = true;
                            } else {
                                isOdd = true;
                            }
                            map[r][c][i].status = 0;
                        }
                    }
                    m /= 5;
                    s /= actualSz;
                    if (isEven == isOdd) {  // 대각선 네방향
                        d = 1;
                    }
                    // map[r][c].clear();
                    if (m > 0) {
                        for (int n = 0; n < 4; n++) {
                            map[r][c].push_back(pool[createAtom(m, s, d)]);
                            d += 2;
                        }
                    }
                }
            }
        }
    }
}

void move() {
    vector<Atom> tmp[51][51];
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (!map[r][c].empty()) {
                for (int atom = 0; atom < map[r][c].size(); atom++) {
                    if (map[r][c][atom].status > 0) {
                        int nr = 
                            (r + (map[r][c][atom].s % n) * dr[map[r][c][atom].d] + n) % n;
                        int nc =
                            (c + (map[r][c][atom].s % n) * dc[map[r][c][atom].d] + n) % n;
                        tmp[nr][nc].push_back(map[r][c][atom]);
                    }
                }
            }
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            map[r][c] = tmp[r][c];
        }
    }
}

int createAtom(int m, int s, int d) {
    pool[ATOM_CNT].m = m;
    pool[ATOM_CNT].s = s;
    pool[ATOM_CNT].d = d;
    pool[ATOM_CNT].status = 1;

    return ATOM_CNT++;
}

void debug() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (!map[r][c].empty()) {
                cout << r << ", " << c << "\n";
            }
            for (auto m : map[r][c]) {
                cout << "방향: " << m.d << " 질량: " << m.m << " 속도: " << m.s
                     << "\n";
            }
        }
    }
}