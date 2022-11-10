#include <cmath>
#include <iostream>
using namespace std;

#define PREV_SETTING                                                           \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
int arr[128][128];
int tmp[128][128];
int N, opCnt, op, level;
int arrN;
int oper[1001][2];

int main() {
    cin >> N >> opCnt;
    arrN = pow(2.0, N);
    for (int i = 0; i < arrN; i++) {
        for (int j = 0; j < arrN; j++) {
            cin >> arr[i][j];
            tmp[i][j] = arr[i][j];
        }
    }

    for (int i = 0; i < opCnt; i++) {
        cin >> oper[i][0] >> oper[i][1];
    }

    int partialN, partialArrCnt;
    for (int i = 0; i < opCnt; i++) {
        // cin >> op >> level;
        op = oper[i][0];
        level = oper[i][1];
        // cout << "\n" << op << " " << level << "\n";
        partialN = pow(2.0, level);
        partialArrCnt = arrN / partialN;

        if ((op == 1 || op == 2 || op == 3 || op == 4) && (level == 0)) {
            continue;
        } else if (op == 1 && level != 0) {
            for (int gr = 0; gr < partialArrCnt; gr++) {
                for (int row = 0; row < partialN; row++) {
                    for (int j = 0; j < arrN; j++) {
                        arr[gr * partialN + partialN - 1 - row][j] =
                            tmp[gr * partialN + row][j];
                    }
                }
            }
        } else if (op == 2 && level != 0) {
            for (int gr = 0; gr < partialArrCnt; gr++) {
                for (int i = 0; i < arrN; i++) {
                    for (int col = 0; col < partialN; col++) {
                        arr[i][gr * partialN + partialN - 1 - col] =
                            tmp[i][gr * partialN + col];
                    }
                }
            }
        } else if (op == 3 && level != 0) {
            for (int rowGr = 0; rowGr < partialArrCnt; rowGr++) {
                for (int colGr = 0; colGr < partialArrCnt; colGr++) {
                    for (int row = 0; row < partialN; row++) {
                        for (int col = 0; col < partialN; col++) {
                            arr[rowGr * partialN + col]
                               [colGr * partialN + partialN - 1 - row] =
                                   tmp[rowGr * partialN + row]
                                      [colGr * partialN + col];
                        }
                    }
                }
            }
        } else if (op == 4 && level != 0) {
            for (int rowGr = 0; rowGr < partialArrCnt; rowGr++) {
                for (int colGr = 0; colGr < partialArrCnt; colGr++) {
                    for (int row = 0; row < partialN; row++) {
                        for (int col = 0; col < partialN; col++) {
                            arr[rowGr * partialN + partialN - 1 - col]
                               [colGr * partialN + row] =
                                   tmp[rowGr * partialN + row]
                                      [colGr * partialN + col];
                        }
                    }
                }
            }
        } else if (op == 5) {
            int grCnt = arrN / partialN;
            for (int gr = 0; gr < grCnt; gr++) {
                for (int row = 0; row < partialN; row++) {
                    for (int j = 0; j < arrN; j++) {
                        arr[gr * partialN + row][j] =
                            tmp[(grCnt - 1 - gr) * partialN + row][j];
                    }
                }
            }
        } else if (op == 6) {
            for (int gr = 0; gr < partialArrCnt; gr++) {
                for (int i = 0; i < arrN; i++) {
                    for (int col = 0; col < partialN; col++) {
                        arr[i][gr * partialN + col] =
                            tmp[i][(partialArrCnt - 1 - gr) * partialN + col];
                    }
                }
            }
        } else if (op == 7) {
            for (int rowGr = 0; rowGr < partialArrCnt; rowGr++) {
                for (int colGr = 0; colGr < partialArrCnt; colGr++) {
                    for (int row = 0; row < partialN; row++) {
                        for (int col = 0; col < partialN; col++) {
                            arr[colGr * partialN + row]
                               [(partialArrCnt - 1 - rowGr) * partialN + col] =
                                   tmp[rowGr * partialN + row]
                                      [colGr * partialN + col];
                        }
                    }
                }
            }
        } else if (op == 8) {
            for (int rowGr = 0; rowGr < partialArrCnt; rowGr++) {
                for (int colGr = 0; colGr < partialArrCnt; colGr++) {
                    for (int row = 0; row < partialN; row++) {
                        for (int col = 0; col < partialN; col++) {
                            arr[(partialArrCnt - 1 - colGr) * partialN + row]
                               [rowGr * partialN + col] =
                                   tmp[rowGr * partialN + row]
                                      [colGr * partialN + col];
                        }
                    }
                }
            }
        }
        for (int i = 0; i < arrN; i++) {
            for (int j = 0; j < arrN; j++) {
                tmp[i][j] = arr[i][j];
            }
        }
    }

    for (int i = 0; i < arrN; i++) {
        for (int j = 0; j < arrN; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}