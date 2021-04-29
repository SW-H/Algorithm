#include <cstdio>
bool isPrime(int target);

int main(){
    int n,a,b;
    bool res;
    while(1){
        res = false;
        scanf("%d",&n);
        if (n==0){
            return 0;
        }
        else{
            for(int i=1;i<n;i++){
                if (isPrime(i) && isPrime(n-i)){
                    // printf("%d = %d + %d\n",n,i,n-i);
                    res = true;
                    a = i;
                    b= n-i;
                    break;
                }    
            }
            if(res){
                printf("%d = %d + %d\n",n,a,b);
            }
            else{
                printf("Goldbach's conjecture is wrong.");
            }
            
        }
    }
}



bool isPrime(int target){
    if(target==1){
        return false;
    }
    for(int i=2;i*i<=target;i++){
        if (target%i==0){
            return false;
        }
    }
    return true;
}