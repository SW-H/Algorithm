#include <iostream>
#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
#define DIV 1000000007
#define CASE 16
using namespace std;
int T, N, res;
string keys;

void solve(int day, int prev);
int main() {
    INIT

    int prev;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> keys;
        prev = 0b1111;
        N = keys.length();
        res = 0;
        // TODO : 1,000,000,007로 나눈 나머지 출력
        for (int i = 1; i < CASE; i++) {
            int keyCheck = 1 << ('D' - keys[0]);
            if ((i & keyCheck) && (i & prev) && (i & 8)) {
                solve(1, i);
            }
        }
        cout << "#" << t << " " << res;
    }
}

void solve(int day, int prev) {
    if (day == N) {
        res++;
        return;
    }
    for (int i = 1; i < CASE; i++) {
        int keyCheck = 1 << ('D' - keys[day]);
        if ((i & keyCheck) && (i & prev)) {
            solve(day + 1, i);
        }
    }
    return;
}