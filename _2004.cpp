#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

int cnt(int target, ll n);

/*

N!에 포함된 2의 지수 개수 ( N! = 2^? ) 구하는 방법

ex) N은 25, k는 2인 경우

25 / 2 = 12 (2, 4, 6, ... , 24)

25 / 4 = 6 (4, 8, 12, 16, 20, 24)

25 / 8 = 3 (8, 16, 24)

25 / 16 = 1 (16)

따라서, N!에 포함된 2의 지수 개수는 22개이다.
N! = 2^22 ...


*/

int main() {
    ll n, m;
    scanf("%llu %llu", &n, &m);
    if (m == 0) {
        printf("0");
        return 0;
    }
    int sol = min(cnt(2, n) - cnt(2, m) - cnt(2, n - m),
                  cnt(5, n) - cnt(5, m) - cnt(5, n - m));
    printf("%d\n", sol);
}

int cnt(int target, ll n) {
    int res = 0;
    for (ll i = target; i <= n; i *= target) {
        res += n / i;
    }
    return res;
}
