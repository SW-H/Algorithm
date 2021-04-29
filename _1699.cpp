#include <cstdio>
#include <iostream>
using namespace std;

/*
cnt[N] : N을 제곱수의 합으로 나타냈을 때, 필요한 항의 최소 개수

마지막항을 L 이라고 하면 마지막 항 제외하고 나머지 항의 합 : N-L^2
마지막 항 제외하고 나머지 항의 개수 : cnt[N-L^2] (1<= L^2 <= N)

*/

int main() {
    int N;
    int cnt[100000];

    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        cnt[i] = i;
        for (int j = 1; j * j <= i; j++) {
            if (cnt[i] > cnt[i - j * j] + 1) {
                cnt[i] = cnt[i - j * j] + 1;
            }
        }
    }
    printf("%d", cnt[N]);
}