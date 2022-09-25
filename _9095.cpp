#include <iostream>
using namespace std;

int makeSum(int sum, int count);

int n;
int main() {
    int caseCnt;
    cin >> caseCnt;
    for (int i = 0; i < caseCnt; i++) {
        cin >> n;
        cout << makeSum(0, 0) << "\n";
    }
}

int makeSum(int sum, int count) {
    if (sum == n) {
        return count + 1;
    } else if (sum > n) {
        return 0;
    }
    return makeSum(sum + 1, count) + makeSum(sum + 2, count) +
           makeSum(sum + 3, count);
}