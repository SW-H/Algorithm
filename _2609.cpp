#include <cstdio>

int GCD(int a, int b);
int LCM(int a, int b);

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n%d", GCD(a, b), LCM(a, b));
    return 0;
}

int GCD(int a, int b) {  // 최대공약수
    if (b == 0) {
        return a;
    } else {
        // return 빠뜨리지 않도록 주의
        return GCD(b, a % b);
    }
}

int LCM(int a, int b) {  // 최소공배수
    return ((a * b) / GCD(a, b));
}