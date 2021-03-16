#include <cstdio>

void primeFactorization(int N);

int main() {
    int N;
    scanf("%d", &N);
    primeFactorization(N);
}

void primeFactorization(int N) {
    for (int i = 2; i * i <= N; i++) { // i * i < N 이 아니라 i * i <= N (등호 주의)
        while (N % i == 0) { // for문안에 while 문 적는거 주의
            printf("%d\n", i);
            N /= i;
        }
    }
    if (N > 1) {
        printf("%d\n", N);
    }
}