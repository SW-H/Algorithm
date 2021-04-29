#include <cstdio>
#define mod 1000000000LL

int main() {
    int N, K;
    long long cnt[222][222] = {0};

    scanf("%d %d", &N, &K);
    cnt[0][0] = 1LL;

    /*
    ?????
    
    for 문을  
    for (int i = 0; i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            .. 
        }
    }

    이렇게 하면 왜 안되는지 모르겠다.

    논리적으로 아래가 더 맞는건가.

    마지막 숫자를 나타내는 k 랑 관련있는게 N(즉, i)이니까 그런거 같기도 하다.
    
    */

    for (int j = 1; j <= K; j++) {
        for (int i = 0; i <= N; i++) {
            for (int k = 0; k <= i; k++) {
                cnt[i][j] = (cnt[i][j] + cnt[i - k][j - 1]) % mod;
            }
        }
    }

    printf("%lld", cnt[N][K]);
}