// 이동 과정 중에 원자가 만나는 경우는 합성으로 고려하지 않습니다.

#include <iostream>
#include <vector>
using namespace std;

int n, atomCnt, t;
// ↑, ↗, →, ↘, ↓, ↙, ←, ↖
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
struct Atom {
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
        map[r][c].push_back(pool[idx]);
    }

    for (int sec = 1; sec <= t; sec++) {
        move();
        crush();
    }
    cout << calcRes();
}
int calcRes(){
    int res=0;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (!map[r][c].empty()) {
                for (auto atom : map[r][c]) {
                    res += atom.m;
                }
            }
        }
    }
    return res;
}

void crush() {

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (!map[r][c].empty()) {
                bool isEven = false, isOdd = false;
                int m = 0, s = 0, d = 0;
                for (auto atom : map[r][c]) {
                    m += atom.m;
                    s += atom.s;
                    if (atom.d % 2 == 0) {
                        isEven = true;
                    } else {
                        isOdd = true;
                    }
                }
                m /= 5;
                s /= map[r][c].size();
                if (isEven == isOdd) { // 대각선 네방향
                    d = 1;
                }
                map[r][c].clear();
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

void move() {
    vector<Atom> tmp[51][51];
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (!map[r][c].empty()) {
                for (int atom = 0; atom < map[r][c].size(); atom++) {
                    int nr =
                        (r + (map[r][c][atom].s % n) * dr[map[r][c][atom].d] +
                         n) %
                        n;
                    int nc =
                        (c + (map[r][c][atom].s % n) * dc[map[r][c][atom].d] +
                         n) %
                        n;
                    tmp[nr][nc].push_back(map[r][c][atom]);
                }
            }
        }
    }
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            map[r][c] = tmp[r][c];
        }
    }
}

int createAtom(int m, int s, int d) {
    pool[ATOM_CNT].m = m;
    pool[ATOM_CNT].s = s;
    pool[ATOM_CNT].d = d;
    return ATOM_CNT++;
}

void debug() {
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
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