#include <iostream>
using namespace std;

void solve(int loc);
bool check(int loc);
char signMatrix[56][56];
int res[11];
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    string s;
    cin >> s;

    int idx = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            signMatrix[i][j] = s[idx++];
        }
    }
    solve(1);
}

void solve(int loc) {
    // loc : 몇번째자리 할 차례인지, res : 지금까지 결정된 숫자들
    if (loc == n+1 && check(loc)) {
        for (int i = 1; i <= n; i++) {
            cout << res[i] << " ";
        }
        exit(0);
        return;
    }
    for (int i = -10; i <= 10; i++) {
        res[loc] = i;
        if (check(loc)) {
            solve(loc + 1);
        }
    }
}

bool check(int loc) {
    int sum = 0;
    for (int i = loc; i >= 0; i--) {
        sum += res[i];
        if ((signMatrix[i][loc] == '+' && sum <= 0) ||
            (signMatrix[i][loc] == '-' && sum >= 0) ||
            (signMatrix[i][loc] == '0' && sum != 0)) {
            return false;
        }
    }
    return true;
}

// cf. https://injae-kim.github.io/problem_solving/2020/02/22/baekjoon-1248.html