#include <cstdio>

long long LCM(int a, int b);
int GCD(int a, int b);

int main() {
    int T, A, B;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d %d", &A, &B);
        printf("%d\n", LCM(A, B));
    }
}

int GCD(int a, int b) {  // 최대공약수
    if (b == 0) {
        return a;
    } else {
        // return 빠뜨리지 않도록 주의
        return GCD(b, a % b);
    }
}

long long LCM(int a, int b) {  // 최소공배수
    return ((a * b) / GCD(a, b));
}