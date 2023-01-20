#include <cstring>
#include <iostream>

using namespace std;

#define REM 1000000007
#define A 0b1000
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    string str;
    cin >> T;
    long long ret;
    int prev;

    // 재귀
    for (int t = 1; t <= T; t++) {
        cin >> str;          // 책임자
        int res[2][16] = {}; // 전날+해당일
        for (int init = 1; init <= 15; init++) {
            if ((init & A) && (init & (1 << ('D' - str[0])))) { // 첫날A
                res[0][init] = 1;
            }
        }

        for (int day = 2; day <= str.length(); day++) {
            int mustHave = 1 << ('D' - str[day - 1]);
            for (int prev = 1; prev <= 15; prev++) {
                if (res[0][prev] > 0) {
                    for (int tc = 1; tc <= 15; tc++) {
                        if ((tc & prev) && (tc & mustHave)) {
                            res[1][tc] =
                                ((res[1][tc] % REM) + (res[0][prev] % REM)) %
                                REM;
                        }
                    }
                }
            }
            for (int d = 1; d <= 15; d++) {
                res[0][d] = res[1][d];
                res[1][d] = 0;
            }
        }
        ret = 0;
        for (int d = 1; d <= 15; d++) {
            ret += (res[0][d] % REM);
        }
        cout << "#" << t << " " << ret % REM << "\n";
    }
}