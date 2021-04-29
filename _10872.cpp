#include <cstdio>
typedef long long ll;

int main(){
    int n;
    ll factorial = 1;
    scanf("%d",&n);
    if(n==0){
        printf("1\n");
        return 0;
    }
    
    while(n>0){
        factorial *= n;
        n--;
    }

    printf("%lld\n",factorial);
}