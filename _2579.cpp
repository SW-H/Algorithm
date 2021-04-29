// 마지막 칸은 무조건 도달해야 하니까 마지막칸부터 출발점 까지로 거꾸로 문제를 풀면 오류나는데 그 이유를 모르겠음
// 거꾸로 해도 결국 똑같은거 아닌가?
// (주석 처리해놓은 부분)


#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int howManyStairs;
    int stairs[333], res[333];
    scanf("%d", &howManyStairs);
    for (int i = 1; i <= howManyStairs; i++) {
        scanf("%d", &stairs[i]);
    }
    if (howManyStairs == 1) {
        printf("%d", stairs[1]);
        return 0;
    }
    // stairs[0] = 0;
    
    // res[1] = stairs[1];
    // res[2] = stairs[1] + stairs[2];
    // res[3] = max(stairs[1]+stairs[3], stairs[2]+stairs[3]);        
    // for (int i = 4; i <= howManyStairs; i++) {
    //     res[i] = max(res[i - 3] + stairs[i - 1] + stairs[i], res[i - 2] + stairs[i]);
    // }
    // printf("%d", res[howManyStairs]);




    // stairs[0] = 0;
    res[howManyStairs + 1] = 0;
    res[howManyStairs] = stairs[howManyStairs];
    res[howManyStairs - 1] = stairs[howManyStairs] + stairs[howManyStairs - 1];
    res[howManyStairs - 2] = max(
        res[howManyStairs], res[howManyStairs - 1] + stairs[howManyStairs - 2]);
    for (int i = howManyStairs - 3; i >= 1; i--) {
        res[i] =
            max(res[i + 3] + stairs[i + 1] + stairs[i], res[i + 2] + stairs[i]);
    }



    // printf("\n\n\n#stairs\n\n
    // %3d%3d%3d%3d",stairs[1],stairs[2],stairs[3],stairs[4]);
    // printf("\n\n\n#res\n\n %3d%3d%3d%3d",res[1],res[2],res[3],res[4]);
    printf("%d", max(res[1], res[2]));
}
 