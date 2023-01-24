#include <cstring> //memset
#include <iostream>
#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
#define DIV 1000000007
#define CASE 16
using namespace std;
int T, N, memo[10001][CASE];
string keys;

int main() {
    INIT;
    int keyCheck;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> keys;
        N = keys.length();
        memset(memo, 0, sizeof(memo));
        for (int i = 1; i < CASE; i++) { // 첫날
            keyCheck = 1 << ('D' - keys[0]);
            if ((i & keyCheck) && (i & 0b1000)) {
                memo[1][i] = 1;
            }
        }
        for (int day = 2; day <= N; day++) {
            keyCheck = 1 << ('D' - keys[day - 1]);
            for (int prevCase = 1; prevCase < CASE; prevCase++) {
                if (memo[day - 1][prevCase] > 0) {
                    for (int curCase = 1; curCase < CASE; curCase++) {
                        if ((prevCase & curCase) && (keyCheck & curCase)) {
                            memo[day][curCase] =
                                (memo[day][curCase] % DIV +
                                 memo[day - 1][prevCase] % DIV) %
                                DIV;
                        }
                    }
                }
            }
        }
        int res = 0;
        for (int fin = 1; fin < CASE; fin++) {
            res = (res % DIV + memo[N][fin] % DIV) % DIV;
        }
        cout << "#" << t << " " << res << "\n";
    }
}
