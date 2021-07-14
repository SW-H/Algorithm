#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAXR 99
#define MAXC 26

#define MAXL 100

extern void init(int C, int R);
extern void set(int col, int row, char input[]);
extern void update(int value[MAXR][MAXC]);

#define INIT 100
#define SET 200
#define UPDATE 300

static int R;
static int C;

static int gethash(int value[MAXR][MAXC]) {
    int ret = 0;

    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
            ret = (ret * 7 + value[r][c]) & 0x7fffffff;

    return ret;
}

static bool run() {
    int Q;
    bool okay = true;

    scanf("%d", &Q);

    for (int q = 0; q < Q; ++q) {
        int cmd, row, col;
        int userhash, answerhash;

        char input[MAXL];
        int value[MAXR][MAXC];

        scanf("%d", &cmd);

        switch (cmd) {
        case INIT:
            scanf("%d %d", &C, &R);
            if (okay)
                init(C, R);
            break;
        case SET:
            scanf("%d %d %s", &col, &row, input);
            if (okay)
                set(col, row, input);
            break;
        case UPDATE:
            scanf("%d", &answerhash);
            if (okay) {
                update(value);
                userhash = gethash(value);
                if (answerhash != userhash)
                    okay = false;
            }
            break;
        default:
            break;
        }
    }

    return okay && Q > 0;
}
int calculator[MAXR][MAXC];
int load[MAXR][MAXC];
int main() {
    int TC;

    // freopen("sample_input.txt", "r", stdin);

    setbuf(stdout, NULL);
    scanf("%d", &TC);

    int totalscore = 0;
    for (int testcase = 1; testcase <= TC; ++testcase) {
        int score = run() ? 100 : 0;
        printf("#%d %d\n", testcase, score);
        totalscore += score;
    }
    printf("total score = %d\n", totalscore / TC);

    printf("\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%10d", calculator[i][j]);
        }
        printf("\n");
    }
    return 0;
}
// #include <stdlib.h>
///////////
#define MAX 0
#define MIN 1
#define SUM 2
int calc(char *input, char oper);
int calcRange(char *input, int oper);
int rangeMax(int row1, int row2, int col1, int col2, bool isRow);
int rangeMin(int row1, int row2, int col1, int col2, bool isRow);
int rangeSum(int row1, int row2, int col1, int col2, bool isRow);
int sw_strncmp(const char *s1, const char *s2, unsigned long long n);
// #include <malloc.h>

//!!!!!!주석 살려야댐//////////////////////////////////////////////////////
// int calculator[MAXR][MAXC] ;
// int load[MAXR][MAXC] ;
// 음수다루는게 문제일듯 ex.calculator[i][j]-'0' 할때 calculator[i][j]이 값이
// 음수면!!? calculator 가 char 배열일 이유가 있나?

void init(int C, int R) {
    // calculator = (char **)malloc(sizeof(char *) * R);
    // for (int i = 0; i < R; i++) {
    //     calculator[i] = (char *)malloc(sizeof(char) * C);
    // }
    for (int i = 0; i < MAXR; i++) {
        for (int j = 0; j < MAXC; j++) {
            calculator[i][j] = 0;
            load[i][j] = 0;
        }
    }
}

void set(int col, int row, char input[]) {
    int setNum;
    bool isMinus;
    isMinus = false;
    if ((('0' <= input[0] && input[0] <= '9') ||
         (input[0] == '-'))) { // 단독문자
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '-') {
                isMinus = true;
            } else {
                load[row - 1][col - 1] *= 10;
                load[row - 1][col - 1] += (input[i] - '0');
            }
        }
    }
    if (isMinus) {
        load[row - 1][col - 1] *= -1;
    }
    if (input[0] == 'A' || input[0] == 'S' || input[0] == 'M' ||
        input[0] == 'D') {
        if (!sw_strncmp(input, "ADD", 3)) {
            setNum = calc(input + 4, '+');
        } else if (!sw_strncmp(input, "SUB", 3)) {
            setNum = calc(input + 4, '-');
        } else if (!sw_strncmp(input, "MUL", 3)) {
            setNum = calc(input + 4, '*');
        } else if (!sw_strncmp(input, "DIV", 3)) {
            setNum = calc(input + 4, '/');
        } else if (!sw_strncmp(input, "MAX", 3)) {
            setNum = calcRange(input + 4, MAX);
        } else if (!sw_strncmp(input, "MIN", 3)) {
            setNum = calcRange(input + 4, MIN);
        } else { // if(!sw_strncmp(input,"SUM",3)){
            setNum = calcRange(input + 4, SUM);
        }
        load[row - 1][col - 1] = setNum;
    }
}
void update(int value[MAXR][MAXC]) {
    for (int i = 0; i < MAXR; i++) {
        for (int j = 0; j < MAXC; j++) {
            // printf("%d %d\n",i,j);
            // if ((calculator[i][j] == '0') && (load[i][j] != 0)) {
            if (load[i][j] != 0) {
                calculator[i][j] = load[i][j];
            }
        }
    }
    
    
    for (int i = 0; i < MAXR; i++) {
        for (int j = 0; j < MAXC; j++) {
            value[i][j] = calculator[i][j];
            load[i][j] = 0;
        }
    }


    // printf("\n");
    // for (int i = 0; i < MAXR; i++) {
    //     for (int j = 0; j < MAXC; j++) {
    //         printf("%3d", calculator[i][j] - '0');
    //     }
    //     printf("\n");
    // }
}

int calc(char *input, char oper) {
    int i, row1, row2, col1, col2;
    bool isMinus;
    isMinus = false;
    // printf("%s\n", input);
    for (i = 0; input[i] != ','; i++) {
        if (('0' <= input[i]) && (input[i] <= '9')) {
            row1 *= 10;
            row1 += (input[i] - '1');
        } else {
            col1 = (input[i] - 'A');
        }
    }
    for (++i; input[i] != ')'; i++) {
        // printf("[%c]", input[i]);
        if ('0' <= input[i] && input[i] <= '9') {
            row2 *= 10;
            row2 += (input[i] - '1');
        } else {
            col2 = (input[i] - 'A');
        }
    }

    switch (oper) {
    case '+':
        return calculator[row1][col1] + calculator[row2][col2];
    case '-':
        return calculator[row1][col1] - calculator[row2][col2];
    case '*':
        return calculator[row1][col1] * calculator[row2][col2];
    default:
        if (calculator[row1][col1] == 0 || calculator[row2][col2] == 0) {

            // printf("[%d %d %d %d]\n", row1, col1, row2, col2);
            // printf("[%d %d %d %d]\n", row1, col1, row2, col2);
            return 0;
        }
        return calculator[row1][col1] / calculator[row2][col2];
    }
}

int calcRange(char *input, int oper) {
    int i, row1, row2, col1, col2;
    bool isRow;
    for (i = 0; input[i] != ','; i++) {
        if ('0' <= input[i] && input[i] <= '9') {
            row1 *= 10;
            row1 += input[i] - '1';
        } else {
            col1 = input[i] - 'A';
        }
    }
    for (++i; input[i] != ')'; i++) {
        if ('0' <= input[i] && input[i] <= '9') {
            row2 *= 10;
            row2 += input[i] - '1';
        } else {
            col2 = input[i] - 'A';
        }
    }
    isRow = row1 == row2;
    switch (oper) {
    case MAX:
        return rangeMax(row1, row2, col1, col2, isRow);
    case MIN:
        return rangeMin(row1, row2, col1, col2, isRow);
    default: // case SUM:
        return rangeSum(row1, row2, col1, col2, isRow);
    }
}

int rangeMax(int row1, int row2, int col1, int col2, bool isRow) {
    int max;
    max = calculator[row1][col1];

    if (isRow) { //-------
        for (int i = col1; i <= col2; i++) {
            if ((calculator[row1][i]) > max) {
                max = (calculator[row1][i]);
            }
        }
        return max;
    } else {
        for (int i = row1; i <= row2; i++) {
            if ((calculator[i][col1]) > max) {
                max = (calculator[i][col1]);
            }
        }
    }
    return max;
}

int rangeMin(int row1, int row2, int col1, int col2, bool isRow) {
    int min;
    min = calculator[row1][col1];

    if (isRow) { //-------
        for (int i = col1; i <= col2; i++) {
            if ((calculator[row1][i]) < min) {
                min = (calculator[row1][i]);
            }
        }
        return min;
    } else {
        for (int i = row1; i <= row2; i++) {
            if ((calculator[i][col1]) < min) {
                min = (calculator[i][col1]);
            }
        }
    }
    return min;
}

int rangeSum(int row1, int row2, int col1, int col2, bool isRow) {
    int sum;
    sum = 0;

    if (isRow) { //-------
        for (int i = col1; i <= col2; i++) {
            sum += (calculator[row1][i]);
            // printf("[%5d]")
        }
        return sum;
    } else {
        for (int i = row1; i <= row2; i++) {
            sum += (calculator[i][col1]);
        }
    }
    return sum;
}

/////

int sw_strncmp(const char *s1, const char *s2, unsigned long long n) {
    if (n == 0) {
        return (0);
    }
    while (*s1 && --n) {
        if (*(unsigned char *)s1 != *(unsigned char *)s2) {
            return (*(unsigned char *)s1 - *(unsigned char *)s2);
        }
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*
1
20
100 5 5
200 3 2 5
200 5 2 13
200 1 5 2
200 2 1 6
200 1 1 -9
200 3 4 9
200 2 2 3
200 2 4 7
200 5 3 2
200 3 1 5
300 181832945
200 3 4 -9
200 1 2 SUM(A5,E5)
200 4 2 8
200 4 5 MUL(E2,E3)
200 2 2 SUB(E4,B4)
200 1 4 -9
200 1 5 ADD(C2,A4)
300 63801884
*/
