#include <iostream>
#include <vector>
using namespace std;
void solve();
vector<int> loc;
int n;

int main() {
    for (int i = 0; i < 5; i++) {
        loc.clear();
        cin >> n;
        while (n) {
            loc.push_back(n % 10);
            n /= 10;
        }
        solve();
    }
    return 0;
}

void solve() {
    long long res = 0;
    for (int i = 0; i < loc.size(); i += 2) {
        // 홀수 번째 자리
        res += loc[i];
    }
    for (int i = 1; i < loc.size(); i += 2) {
        if (loc[i] != 0) {
            res *= loc[i];
        }
    }
    cout << res % 10 << "\n";
}