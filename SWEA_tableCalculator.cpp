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
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MAX 4
#define MIN 5
#define SUM 6

#define ROW1 0
#define COL1 1
#define ROW2 2
#define COL2 3

typedef struct {
    bool isDone;
    int value;
    int oper;
    int operand1;
    int operand2;
    int range[4];
    // int r;
    // int c;
} elem;
void load(char *input, int oper, int row, int col);
void update_delegate(int row, int col);
void calc(int row, int col);
void calcRange(int row, int col);
void rangeMax(int row, int col);
void rangeMin(int row, int col);
void rangeSum(int row, int col);
int sw_strncmp(const char *s1, const char *s2, unsigned long long n);

elem calculator[MAXR][MAXC];

int main() {
    int TC;

    freopen("input.txt", "r", stdin);

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
            printf("%10d", calculator[i][j].value);
        }
        printf("\n");
    }
    return 0;
}
// #include <stdlib.h>
///////////

// int load[MAXR][MAXC];

void init(int C, int R) {
    // calculator = (char **)malloc(sizeof(char *) * R);
    // for (int i = 0; i < R; i++) {
    //     calculator[i] = (char *)malloc(sizeof(char) * C);
    // }
    for (int i = 0; i < MAXR; i++) {
        for (int j = 0; j < MAXC; j++) {
            calculator[i][j].isDone = true;
            calculator[i][j].value = 0;
            // load[i][j] = 0;
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
                setNum *= 10;
                setNum += (input[i] - '0');
            }
        }
        if (isMinus) {
            setNum *= -1;
        }
        calculator[row - 1][col - 1].value = setNum;
    } else {
        switch (input[2]) {
        case 'D':
            load(input + 4, ADD, row - 1, col - 1);
            break;
        case 'B':
            load(input + 4, SUB, row - 1, col - 1);
            break;
        case 'L':
            load(input + 4, MUL, row - 1, col - 1);
            break;
        case 'V':
            load(input + 4, DIV, row - 1, col - 1);
            break;
        case 'X':
            load(input + 4, MAX, row - 1, col - 1);
            break;
        case 'N':
            load(input + 4, MIN, row - 1, col - 1);
            break;
        case 'M':
            load(input + 4, SUM, row - 1, col - 1);
            break;
        }
    }
    // if (input[0] == 'A' || input[0] == 'S' || input[0] == 'M' ||
    //     input[0] == 'D') {
    //     if (!sw_strncmp(input, "ADD", 3)) {
    //         setNum = calc(input + 4, '+');
    //     } else if (!sw_strncmp(input, "SUB", 3)) {
    //         setNum = calc(input + 4, '-');
    //     } else if (!sw_strncmp(input, "MUL", 3)) {
    //         setNum = calc(input + 4, '*');
    //     } else if (!sw_strncmp(input, "DIV", 3)) {
    //         setNum = calc(input + 4, '/');
    //     } else if (!sw_strncmp(input, "MAX", 3)) {
    //         setNum = calcRange(input + 4, MAX);
    //     } else if (!sw_strncmp(input, "MIN", 3)) {
    //         setNum = calcRange(input + 4, MIN);
    //     } else { // if(!sw_strncmp(input,"SUM",3)){
    //         setNum = calcRange(input + 4, SUM);
    //     }
    //     calculator[row - 1][col - 1] = setNum;
    // }
}
void update(int value[MAXR][MAXC]) {
    // for (int i = 0; i < MAXR; i++) {
    //     for (int j = 0; j < MAXC; j++) {
    //         // printf("%d %d\n",i,j);
    //         // if ((calculator[i][j] == '0') && (load[i][j] != 0)) {

    //         // if (load[i][j] != 0) {
    //             // calculator[i][j] = load[i][j];
    //         // }
    //     }
    // }

    for (int i = 0; i < MAXR; i++) {
        for (int j = 0; j < MAXC; j++) {
            update_delegate(i, j);
        }
    }

    for (int i = 0; i < MAXR; i++) {
        for (int j = 0; j < MAXC; j++) {
            value[i][j] = calculator[i][j].value;
        }
    }
    // printf("\n");
    // for (int i = 0; i < MAXR; i++) {
    //     for (int j = 0; j < MAXC; j++) {
    //         printf("%3d", calculator[i][j] - '0');
    //     }
    //     printf("\n");
    //
}

void update_delegate(int row, int col) {
    if (calculator[row][col].isDone == false) {
        switch (calculator[row][col].oper) {
        case MAX:
            rangeMax(row, col);
            break;
        case MIN:
            rangeMin(row, col);
            break;
        case SUM:
            rangeSum(row, col);
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            calc(row, col);
            break;
        }
    } else {
        return;
    }
}

void load(char *input, int oper, int row, int col) {
    int i, row1, row2, col1, col2;
    row1 = row2 = col1 = col2 = 0;
    for (i = 0; input[i] != ','; i++) {
        if (('0' <= input[i]) && (input[i] <= '9')) {
            row1 *= 10;
            row1 += (input[i] - '1');
        } else {
            col1 = (input[i] - 'A');
        }
    }
    for (++i; input[i] != ')'; i++) {
        if ('0' <= input[i] && input[i] <= '9') {
            row2 *= 10;
            row2 += (input[i] - '1');
        } else {
            col2 = (input[i] - 'A');
        }
    }
    elem target = calculator[row][col];
    target.oper = oper;
    target.isDone = false;
    update_delegate(row1, col1);
    update_delegate(row2, col2);
    if ((oper == ADD) || (oper == SUB) || (oper == MUL) || (oper == DIV)) {
        target.operand1 = calculator[row1][col1].value;
        target.operand2 = calculator[row2][col2].value;
    } else {
        target.range[ROW1] = row1;
        target.range[COL1] = col1;
        target.range[ROW2] = row2;
        target.range[COL2] = col2;
    }
}
void calc(int row, int col) {
    elem target = calculator[row][col];
    update_delegate(row, col);
    target.isDone = true;
    switch (target.oper) {
    case ADD:
        target.value = target.operand1 + target.operand2;
        break;
    case SUB:
        target.value = target.operand1 - target.operand2;
        break;
    case MUL:
        target.value = target.operand1 * target.operand2;
        break;
    case DIV:
        if (target.operand1 && target.operand2)
            target.value = target.operand1 / target.operand2;
        else
            target.value = 0;
        break;
    }
}
// void calcRange(int row, int col) {
//     int i, row1, row2, col1, col2;
//     bool isRow;
//     for (i = 0; input[i] != ','; i++) {
//         if ('0' <= input[i] && input[i] <= '9') {
//             row1 *= 10;
//             row1 += input[i] - '1';
//         } else {
//             col1 = input[i] - 'A';
//         }
//     }
//     for (++i; input[i] != ')'; i++) {
//         if ('0' <= input[i] && input[i] <= '9') {
//             row2 *= 10;
//             row2 += input[i] - '1';
//         } else {
//             col2 = input[i] - 'A';
//         }
//     }
//     isRow = row1 == row2;
//     switch (oper) {
//     case MAX:
//         return rangeMax(row1, row2, col1, col2, isRow);
//     case MIN:
//         return rangeMin(row1, row2, col1, col2, isRow);
//     default: // case SUM:
//         return rangeSum(row1, row2, col1, col2, isRow);
//     }
// }

void rangeMax(int row, int col) {
    int max, row1, row2, col1, col2;
    row1 = row2 = col1 = col2 = 0;
    bool isRow;
    row1 = calculator[row][col].range[ROW1];
    col1 = calculator[row][col].range[COL1];
    row2 = calculator[row][col].range[ROW2];
    col2 = calculator[row][col].range[COL2];
    isRow = row1 == row2;
    update_delegate(row1, col1);
    max = calculator[row1][col1].value;

    if (isRow) { //-------
        for (int i = col1; i <= col2; i++) {
            // if(calculator[row1][i].isDone==false){

            // }
            update_delegate(row1, i);
            if ((calculator[row1][i].value) > max) {

                max = (calculator[row1][i].value);
            }
        }
    } else {
        for (int i = row1; i <= row2; i++) {
            // if(calculator[i][col1].isDone==false){
            // }
            update_delegate(i, col1);
            if ((calculator[i][col1].value) > max) {
                max = (calculator[i][col1].value);
            }
        }
    }
    calculator[row][col].isDone = true;
    calculator[row][col].value = max;
}

void rangeMin(int row, int col) {
    int min, row1, row2, col1, col2;
    row1 = row2 = col1 = col2 = 0;
    bool isRow;
    row1 = calculator[row][col].range[ROW1];
    col1 = calculator[row][col].range[COL1];
    row2 = calculator[row][col].range[ROW2];
    col2 = calculator[row][col].range[COL2];
    isRow = row1 == row2;
    update_delegate(row1, col1);
    min = calculator[row1][col1].value;

    if (isRow) { //-------
        for (int i = col1; i <= col2; i++) {
            update_delegate(row1, i);
            // if(calculator[row1][i].isDone==false){
            // }
            if ((calculator[row1][i].value) < min) {
                min = (calculator[row1][i].value);
            }
        }
    } else {
        for (int i = row1; i <= row2; i++) {
            update_delegate(i, col1);
            // if(calculator[i][col1].isDone==false){
            // }
            if ((calculator[i][col1].value) < min) {
                min = (calculator[i][col1].value);
            }
        }
    }
    calculator[row][col].isDone = true;
    calculator[row][col].value = min;
}

void rangeSum(int row, int col) {
    int sum, row1, row2, col1, col2;
    row1 = row2 = col1 = col2 = 0;
    bool isRow;
    row1 = calculator[row][col].range[ROW1];
    col1 = calculator[row][col].range[COL1];
    row2 = calculator[row][col].range[ROW2];
    col2 = calculator[row][col].range[COL2];
    isRow = row1 == row2;
    sum = 0;

    if (isRow) { //-------
        for (int i = col1; i <= col2; i++) {
            update_delegate(row1, i);
            // if(calculator[row1][i].isDone==false){
            // }
            sum += (calculator[row1][i].value);
            // printf("[%5d]")
        }
    } else {
        for (int i = row1; i <= row2; i++) {
            update_delegate(i, col1);
            // if(calculator[i][col1].isDone==false){
            // }
            sum += (calculator[i][col1].value);
        }
    }
    calculator[row][col].isDone = true;
    calculator[row][col].value = sum;
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
