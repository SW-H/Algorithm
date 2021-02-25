#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int n;
    int seq[100001], res[100001];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &seq[i]);
    }
    res[0] = seq[0];
    // res[i-1]+seq[i],seq[i]

    for (int i = 0; i < n; i++) {
        res[i] = max(res[i - 1] + seq[i], seq[i]);
    }
    int max = res[0];
    for (int i = 0; i < n; i++) {
        if (res[i] > max) {
            max = res[i];
        }
    }

    printf("%d", max);
}