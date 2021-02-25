#include <cstdio>

int main(){
    int N; 
    int seq[1000],length[1000];
    scanf("%d", &N);
    
    for(int i=0;i<N;i++){
        scanf("%d", &seq[i]);
        length[i]=1;
    }
    
    for(int i = 0;i<N;i++){
        for(int j=0;j<i;j++){
            if(seq[j]>seq[i] && length[j]+1>length[i]){
                length[i]=length[j]+1;
            }
        }
    }
    int max = length[0];
    for(int i=0;i<N;i++){
        printf("%3d",length[i]);
        if(length[i]>max){
            max = length[i];
        }
    }
    
    printf("\n");
    printf("%d\n",max);
}