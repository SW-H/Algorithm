// #include <cstdio>
// #include <iostream>
// #include <algorithm>
// using namespace std;

// int main() {
//     int heights[9] = {0};
//     int ans[9] = {0};
//     int sum = 0, cnt = 0;

//     for (int i = 0; i < 9; i++) {
//         scanf("%d", &heights[i]);
//         sum += heights[i];
//     }

//     for (int i = 0; i < 9; i++) {
//         for (int j = i + 1; j < 9; j++) {
//             if (sum - heights[i] - heights[j] == 100) {
//                 heights[i] = heights[j] = 0;
//                 sort(heights, heights + 9);
//                 for (int k = 0; k < 9; k++) {
//                     if (heights[k] != 0) {
//                         printf("%d\n", heights[k]);
//                     }
//                 }
//                 return 0;
//             }
//         }
//     }
// }

#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    list<int> height;
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        cin >> height[i];
        sum += height[i];
    }
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (sum - height[i] - height[j] == 100) {
                break;
            }
        }
    }
    iterator::
    sort(height.be)
}