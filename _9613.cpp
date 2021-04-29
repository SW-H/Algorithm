#include <cstdio>
typedef long long ll;

ll solution(int n);
int GCD(int a, int b);

int main() {
    int howManyT, n;

    scanf("%d", &howManyT);
    for (int i = 0; i < howManyT; i++) {
        scanf("%d", &n);
        printf("%lld\n", solution(n));
    }
}

ll solution(int n) {
    int nums[n];
    ll res=0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            res+=GCD(nums[i],nums[j]);        
        }
    }
    return res;
}

int GCD(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return GCD(b, a % b);
    }
}