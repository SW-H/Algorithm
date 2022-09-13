// 프로그래머스

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int map1[16][16];
int map2[16][16];

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            map1[i][n - j] = arr1[i] % 2;
            arr1[i] /= 2;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            map2[i][n - j] = arr2[i] % 2;
            arr2[i] /= 2;
        }
    }

    string tmp;
    vector<string> res;
    for (int i = 0; i < n; i++) {
        tmp = "";
        for (int j = 0; j < n; j++) {
            if (map1[i][j] | map2[i][j]) {
                tmp += "#";
            } else {
                tmp += " ";
            }
        }
        res.push_back(tmp);
    }

    return res;
}
