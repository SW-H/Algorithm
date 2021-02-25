
 #include <cstdio>
 int main(){
    int N,res=0;
    long long s[101][10]={0};
    scanf("%d", &N);
    long long rem = 1000000000;
    
    //초기값
    s[1][0]=0;
    for(int i=1;i<=9;i++){
        s[1][i]=1;
    }
    //
    
    for(int i=2;i<=N;i++){
        for(int j=0;j<10;j++){
            if(j-1>=0){
                s[i][j] = (s[i][j]+s[i-1][j-1])%rem;
            }
            if(j+1<10){
                s[i][j] = (s[i][j]+s[i-1][j+1])%rem;
            }
        }
    }
 
    for(int i=0;i<10;i++){
        res=(res+s[N][i])%rem;
    }
    printf("%d\n",res);   

    
    // for(int i=0;i<N;i++){
    //     for(int j=0;j<10;j++){
    //         printf("%-10lld", s[i][j]);
    //     }
    //     printf("\n");
    // }
 }
