 #include <cstdio>
 int main(){
    int n;
    long long s[91]={0},res;
 
    scanf("%d", &n);
    s[0]=0;
    s[1]=1;
    
    for(int i=2;i<=n;i++){
        s[i]=s[i-1]+s[i-2];
    }
    
    res = s[n];
    
    printf("%lld\n",res);
    
    // for(int i=0;i<n+1;i++){
    //     for(int j=0;j<3;j++){
    //         printf("%-5d",s[i][j]);
     //     }
    //     printf("\n");
    // }
    
 }   