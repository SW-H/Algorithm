#include <cstdio>
#include <iostream>
#include <algorithm> //max
using namespace std;

int solution(int n);

int main(){
    int n,res;
    scanf("%d",&n);
    res = solution(n);
    printf("%d\n",res);
    return 0;
}
int solution(int n){
    int drinks[2*n];
    int dp[2*n];
    for(int i=1;i<=n;i++){
        scanf("%d", &drinks[i]);
        
    }
    dp[0] = 0;
    dp[1] = drinks[1];
    dp[2] = dp[1]+drinks[2];
    // dp[3] = max(dp[2],dp[1]+drinks[3]);
    
    for(int i=3;i<=n;i++){
        dp[i] = max(max(dp[i-1],dp[i-2]+drinks[i]),dp[i-3]+drinks[i-1]+drinks[i]);
    }
    return dp[n];
}
