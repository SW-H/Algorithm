#include <iostream>
using namespace std;

void solve(int loc);
int factorialSum(int n);
bool check(int loc);
int rangeSum(int begin, int end);
char signMatrix[56][56];
int res[11];
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            cin >> signMatrix[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (signMatrix[i][i] == '-') {
            res[i] = -11;
        } else {
            res[i] = 0;
        }
    }
    solve(1);
}

void solve(int loc) {
    // loc : 몇번째자리 할 차례인지 , res : 지금까지 결정된 숫자들
    int original;
    if (loc == n) {
        for (int i = 1; i <= n; i++) {
            cout << res[i] << " ";
        }
        exit(0);
        return;
    }
    for (int i = 0; i <= 10; i++) {
        res[loc]++;
        if (check(loc)) {
            solve(loc + 1);
        }
    }
}

int factorialSum(int n) {
    int res = 0;
    while (n) {
        res += n;
        n--;
    }
    return res;
}

bool check(int loc) {
    for (int i = 1; i <= loc; i++) {
        for (int j = 1; j <= loc; j++) {
            if (!(signMatrix[i][j] == '-' && rangeSum(i, j) < 0) &&
                !(signMatrix[i][j] == '+' && rangeSum(i, j) > 0) &&
                !(signMatrix[i][j] == '0' && rangeSum(i, j) == 0)) {
                // cout << "(" << i << "," << j << ")" << rangeSum(i, j) <<
                // "\n";
                return false;
            }
        }
    }
    return true;
}

int rangeSum(int begin, int end) {
    int rangeSum = 0;
    for (int i = begin; i <= end; i++) {
        rangeSum += res[i];
    }
    return rangeSum;
}