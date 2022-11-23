#include <iostream>
using namespace std;

#define START                                                                  \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

int pixel[64][64];
int n;

void input();
void solve(int startRow, int startCol, int splited);

int main() {
    START
    input();
    solve(0, 0, n);
}

void input() {
    string line;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> line;
        for (int j = 0; j < n; j++) {
            pixel[i][j] = line[j] - '0';
        }
    }
}

void solve(int startRow, int startCol, int splited) {
    bool solved = true;
    for (int i = 0; i < splited; i++) {
        for (int j = 0; j < splited; j++) {
            if (pixel[startRow + i][startCol + j] !=
                pixel[startRow][startCol]) {
                solved = false;
                break;
            }
        }
    }
    if (!solved) {
        cout << "(";
        splited /= 2;
        solve(startRow, startCol, splited);
        solve(startRow, startCol + splited, splited);
        solve(startRow + splited, startCol, splited);
        solve(startRow + splited, startCol + splited, splited);
        cout << ")";
    } else {
        cout << pixel[startRow][startCol];
    }
}
