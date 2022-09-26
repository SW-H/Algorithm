#include <iostream>
using namespace std;

int solve(int day, int pay);

int N;
int p[16];
int t[16];
int res = 0;
int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> t[i] >> p[i];
    }

    int tmp;
    cout << solve(1, 0);
}

int solve(int day, int pay) {
    if (day >= N + 1) {
        return pay;
    }
    if (day + t[day] <= N + 1) {
        return max(solve(day + t[day], pay + p[day]), solve(day + 1, pay));
    } else {
        return solve(day + 1, pay);
    }
}