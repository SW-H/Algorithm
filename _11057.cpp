
 #include <cstdio>
 int main(){
    int N,res=0;
    long long s[1001][10]={0};
    scanf("%d", &N);
    long long rem = 10007;
    
    //초기값
    
    for(int i=0;i<=9;i++){
        s[1][i]=1;
    }
    //
    
    for(int i=2;i<=N;i++){
        for(int j=0;j<10;j++){
            for(int k=0;k<j+1;k++){
                s[i][j]=(s[i][j]+s[i-1][k])%rem;
            }
        }
    }
 
    for(int i=0;i<10;i++){
        res=(res+s[N][i])%rem;
    }
    printf("%d\n",res);   
    
        
    // for(int i=0;i<N;i++){
    //     for(int j=0;j<10;j++){
    //         printf("%-7lld", s[i][j]);
    //     }
    //     printf("\n");
    // }
 }
