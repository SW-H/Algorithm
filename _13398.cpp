#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int max(int a, int b, int c);

int main() {
    int n;
    int seq[100001], resL[100001], resR[100001];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &seq[i]);
    }
    if (n == 1) { // 빠뜨리지 않도록 주의!!!!
        printf("%d", seq[0]);
        return 0;
    }

    resL[0] = seq[0];
    resR[n - 1] = seq[n - 1];

    for (int i = 1; i < n; i++) {
        resL[i] = max(resL[i - 1] + seq[i], seq[i]);
    }

    for (int i = n - 2; i >= 0; i--) {
        resR[i] = max(resR[i + 1] + seq[i], seq[i]);
    }
    
    int maxWithNoDel = resL[0];
    for (int i = 0; i < n; i++) {
        if (maxWithNoDel < resL[i]) {
            maxWithNoDel = resL[i];
        }
    }

    int maxValue = resL[0];

    for (int i = 1; i < n-1; i++) { // 범위 주의!!
        if (resL[i - 1] + resR[i + 1] > maxValue) {
            maxValue = resL[i - 1] + resR[i + 1];
        }
    }

    maxValue = max(maxWithNoDel, maxValue,resL[n-2]);
    printf("%d", maxValue);
}

int max(int a, int b, int c) {
    return max(max(a, b), c);
}