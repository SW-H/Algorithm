// #include <cstdio>
// bool solution(int target);
// int main() {
//     int N, target, cnt;
//     scanf("%d", &N);
//     cnt = 0;
//     for (int i = 0; i < N; i++) {
//         scanf("%d", &target);
//         if (solution(target)) {
//             cnt++;
//         }
//     }
//     printf("%d", cnt);
// }

// bool solution(int target) {
//     if (target == 1) {
//         return false;
//     }
//     for (int i = 2; i * i <= target; i++) {
//         if (target % i == 0) {
//             return false;
//         }
//     }
//     return true;
// }

#include <iostream>
using namespace std;
bool isPrime[1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    fill_n(isPrime, 1001, true);
    isPrime[1] = false;
    for (int i = 2; i <= 1000; i++) {
        for (int j = 2; j * i <= 1000; j++) {
            isPrime[i * j] = false;
        }
    }
    int N, cnt, res = 0;
    cin >> cnt;
    for (int i = 0; i < cnt; i++) {
        cin >> N;
        if (isPrime[N]) {
            res++;
        }
    }
    cout << res;
}