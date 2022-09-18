/**
#include <cstdio>
#include <cstdlib>

char** chgBothSides(bool isUpDown, int N, int chgPlaceRow, int chgPlaceCol);
int cntCandy(int N, char** temp);
int solution(int N);
char board[50][50];

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%s", board[i]);
    }
    printf("%d", solution(N));

    // char **temp = chgBothSides(false, N, 0,0);// (0,0) ,(1,0)
    // printf("%d",cntCandy(N , temp));

}

int solution(int N) {
    char** temp;

    // 가로 체크
    int maxCandy = 0, nowCandy;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            // j번째, j+1번째, 양옆 바꾸기, 바꾼 보드판 리턴
            temp = chgBothSides(false, N, i, j);

            nowCandy = cntCandy(N, temp);
            if (maxCandy < nowCandy) {
                maxCandy = nowCandy;
            }
        }
    }

    // 세로 체크
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            temp = chgBothSides(true, N, j, i);  // j번째, j+1번째, 위아래
            nowCandy = cntCandy(N, temp);
            if (maxCandy < nowCandy) {
                maxCandy = nowCandy;
            }
        }
    }
    return maxCandy;
}

char** chgBothSides(bool isUpDown, int N, int chgPlaceRow, int chgPlaceCol) {
    char** temp = (char**)(calloc(sizeof(char*), N));
    char chgChar;

    for (int i = 0; i < N; i++) {
        temp[i] = (char*)(calloc(sizeof(char), N));
    }

    for (int i = 0; i < N; i++) {
        for(int j=0;j<N;j++){
            temp[i][j] = board[i][j];
        }
    }

    if (isUpDown) {
        chgChar = temp[chgPlaceRow][chgPlaceCol];
        temp[chgPlaceRow][chgPlaceCol] = temp[chgPlaceRow + 1][chgPlaceCol];
        temp[chgPlaceRow + 1][chgPlaceCol] = chgChar;
    } else {
        chgChar = temp[chgPlaceRow][chgPlaceCol];
        temp[chgPlaceRow][chgPlaceCol] = temp[chgPlaceRow][chgPlaceCol + 1];
        temp[chgPlaceRow][chgPlaceCol + 1] = chgChar;
    }
    return temp;
}

int cntCandy(int N, char** temp) {
    int now = 0 , max = 0;

    // 가로인접 체크
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (temp[i][j] == temp[i][j - 1]) {
                now++;
            } else {
                if (max < now) {
                    printf("(%d,%d):%d\n",i,j,max);
                    max = now;
                }
                now = 0;
            }
        }
        now = 0;
    }

    now = 0;

    // 세로
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (temp[j][i] == temp[j - 1][i]) {
                now++;
            } else {
                if (max < now) {
                    max = now;
                    printf("(%d,%d)\n",j,i);
                }
                now = 0;
            }
        }
        now = 0;
    }
    return max;
}

/*
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;
int cnt(int i, int j, bool isrow);
char **board;
int N;
void myflush();
int main() {
  int nowCnt, maxCnt = 0;
  char temp;

  scanf("%d", &N);
  myflush();

  board = (char **)calloc(N, sizeof(char *));
  for (int i = 0; i < N; i++) {
    board[i] = (char *)(calloc(N, sizeof(char)));
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%c", &board[i][j]);
    }
    myflush();
  }

  // 가로
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N - 1; j++) {
      if (board[i][j] != board[i][j + 1]) {

        nowCnt = cnt(i, j, true);

        if (nowCnt > maxCnt) {
          maxCnt = nowCnt;
        }
      }
    }

  }

  // 세로

  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N - 1; i++) {
      if (board[i][j] != board[i + 1][j]) {
        nowCnt = cnt(i, j, false);

        if (nowCnt > maxCnt) {

          maxCnt = nowCnt;
        }
      }
    }
  }

  printf("%d", maxCnt);
}

int cnt(int i, int j, bool isrow) {  // swap&cnt

  // swap
  char temp;
  if (isrow) {
    temp = board[i][j];
    board[i][j] = board[i][j + 1];
    board[i][j + 1] = temp;

  } else {
    temp = board[i][j];
    board[i][j] = board[i + 1][j];
    board[i + 1][j] = temp;
  }

  // 먹을수있는 사탕
  char target = 0;
  int cnt = 1, maxCnt = 0;
  // 가로 ㅁㅁ
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j] == target) {
        cnt++;
      } else {
        cnt = 1;
        target = board[i][j];
      }

      if (cnt > maxCnt) {
        maxCnt = cnt;
        // for (int j = 0; j < N; j++) {
        //   for (int i = 0; i < N; i++) {
        //     printf("%3c", board[i][j]);
        //   }
        //   printf("\n");
        // }
        // printf("\nmax:%d", maxCnt);
      }
    }
    cnt = 1;
    target=0;
  }

  // 세로
  //ㅁ
  //ㅁ
  // cnt = 0, maxCnt = 0;
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      if (board[i][j] == target) {
        cnt++;
      } else {
        cnt = 1;
        target = board[i][j];
      }
      if (cnt > maxCnt) {
        maxCnt = cnt;
      }
    }
    cnt = 1;
    target = 0;
  }

  // rewind
  if (isrow) {
    temp = board[i][j];
    board[i][j] = board[i][j + 1];
    board[i][j + 1] = temp;
  } else {
    temp = board[i][j];
    board[i][j] = board[i + 1][j];
    board[i + 1][j] = temp;
  }

  return maxCnt;
}

void myflush() {
  while (getchar() != '\n') {
    ;
  }
}

**/

#include <iostream>
#define MAX 50
using namespace std;
char board[MAX][MAX];
void input();
int solve();
void swapRow(int i, int j);
void swapCol(int i, int j);
int check();
int size;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> size;
  input();
  cout << solve();
}

void input() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cin >> board[i][j];
    }
  }
}

int solve() {
  int res;
  int tmp;

  res = check();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - 1; j++) {
      swapRow(i, j);
      if (res < (tmp = check())) {
        res = tmp;
      }
      swapRow(i, j);
    }
  }
  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size - 1; i++) {
      swapCol(i, j);
      if (res < (tmp = check())) {
        res = tmp;
      }
      swapCol(i, j);
    }
  }
  return res;
}

void swapRow(int i, int j) { // 오른쪽 칸과 스왑 & 사탕 최대 개수 계산
  int tmp;
  tmp = board[i][j];
  board[i][j] = board[i][j + 1];
  board[i][j + 1] = tmp;
}

void swapCol(int i, int j) { // 아랫칸과 스왑 & 사탕 최대 개수 계산
  int tmp;
  tmp = board[i][j];
  board[i][j] = board[i + 1][j];
  board[i + 1][j] = tmp;
}

int check() {
  int res = 1;
  int count = 1;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - 1; j++) {
      if (board[i][j] == board[i][j + 1]) {
        count++;
      } else {
        if (count > res) {
          res = count;
        }
        count = 1;
      }
    }
    if (count > res) {
      res = count;
    }
    count = 1;
  }

  count = 1;
  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size - 1; i++) {
      if (board[i][j] == board[i + 1][j]) {
        count++;
      } else {
        if (count > res) {
          res = count;
        }
        count = 1;
      }
    }
    if (count > res) {
      res = count;
    }
    count = 1;
  }
  return res;
}
