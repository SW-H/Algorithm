#define MAXR 99
#define MAXC 26

void init(int C, int R);
int sw_atoi(char *str);
void parse(char input[], char *left, char *right);
void set(int col, int row, char input[]);
int max(int a, int b);
int min(int a, int b);
int calc(int i, int j);
void update(int value[MAXR][MAXC]);

struct Elem {
    int mathSign;
    int op;
    int temp;
    int start[2];
    int end[2];
};

Elem MAP[MAXR][MAXC];
int r, c;
int checked[MAXR][MAXC];

void init(int C, int R) {
    r = R, c = C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++)
            MAP[i][j].op = MAP[i][j].mathSign = 0;
    }
}

void set(int col, int row, char input[]) {
    int i = row - 1;
    int j = col - 1;
    if (('0' <= input[0] && input[0] <= '9') || input[0] == '-') {
        MAP[i][j].op = 0;
        MAP[i][j].mathSign = sw_atoi(input);
    } else {
        MAP[i][j].op = 1;
        char left[4], right[4];
        parse(input, left, right);
        MAP[i][j].start[1] = left[0] - 'A';
        MAP[i][j].start[0] = sw_atoi(left) - 1;
        MAP[i][j].end[1] = right[0] - 'A';
        MAP[i][j].end[0] = sw_atoi(right) - 1;
        switch (input[2]) {
        case 'D':
            MAP[i][j].mathSign = 0;
            break;
        case 'B':
            MAP[i][j].mathSign = 1;
            break;
        case 'L':
            MAP[i][j].mathSign = 2;
            break;
        case 'V':
            MAP[i][j].mathSign = 3;
            break;
        case 'X':
            MAP[i][j].mathSign = 4;
            break;
        case 'N':
            MAP[i][j].mathSign = 5;
            break;
        case 'M':
            MAP[i][j].mathSign = 6;
            break;
        default:
            break;
        }
    }
}

void update(int value[MAXR][MAXC]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            checked[i][j] = 0;
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            value[i][j] = calc(i, j);
        }
    }
}

int sw_atoi(char *str) {
    int idx, num;
    idx = num = 0;
    int flag = 1;
    if (!('0' <= str[idx] && str[idx] <= '9')) {
        if (str[idx] == '-')
            flag = -1;
        idx++;
    }
    do {
        num = num * 10 + (str[idx] - '0');
    } while (str[++idx]);
    return num * flag;
}

void parse(char input[], char *left, char *right) {
    int flag = 0;
    for (int i = 0; *input; *input++, i++) {
        if (*input == ',') {
            flag = 1;
            continue;
        }
        if (3 < i && flag == 0)
            *left++ = *input;
        if (flag == 1 && *input != ')')
            *right++ = *input;
    }
    *right = *left = '\0';
}

int max(int a, int b) {
    int res = a;
    if (res < b)
        res = b;
    return res;
}

int min(int a, int b) {
    int res = a;
    if (res > b)
        res = b;
    return res;
}

int calc(int i, int j) {
    if (checked[i][j] == 1) {
        if (MAP[i][j].op == 0)
            return MAP[i][j].mathSign;
        else
            return MAP[i][j].temp;
    } else {
        checked[i][j] = 1;
        if (MAP[i][j].op == 0)
            return MAP[i][j].mathSign;
        else {
            int res;
            switch (MAP[i][j].mathSign) {
            case 0:
                MAP[i][j].temp = calc(MAP[i][j].start[0], MAP[i][j].start[1]) +
                                 calc(MAP[i][j].end[0], MAP[i][j].end[1]);
                break;
            case 1:
                MAP[i][j].temp = calc(MAP[i][j].start[0], MAP[i][j].start[1]) -
                                 calc(MAP[i][j].end[0], MAP[i][j].end[1]);
                break;
            case 2:
                MAP[i][j].temp = calc(MAP[i][j].start[0], MAP[i][j].start[1]) *
                                 calc(MAP[i][j].end[0], MAP[i][j].end[1]);
                break;
            case 3:
                MAP[i][j].temp = calc(MAP[i][j].start[0], MAP[i][j].start[1]) /
                                 calc(MAP[i][j].end[0], MAP[i][j].end[1]);
                break;
            case 4:
                res = -1000000001;
                for (int i0 = MAP[i][j].start[0]; i0 <= MAP[i][j].end[0];
                     i0++) {
                    for (int j0 = MAP[i][j].start[1]; j0 <= MAP[i][j].end[1];
                         j0++)
                        res = max(calc(i0, j0), res);
                }
                MAP[i][j].temp = res;
                break;
            case 5:
                res = 1000000001;
                for (int i0 = MAP[i][j].start[0]; i0 <= MAP[i][j].end[0];
                     i0++) {
                    for (int j0 = MAP[i][j].start[1]; j0 <= MAP[i][j].end[1];
                         j0++)
                        res = min(calc(i0, j0), res);
                }
                MAP[i][j].temp = res;
                break;
            case 6:
                res = 0;
                for (int i0 = MAP[i][j].start[0]; i0 <= MAP[i][j].end[0];
                     i0++) {
                    for (int j0 = MAP[i][j].start[1]; j0 <= MAP[i][j].end[1];
                         j0++)
                        res += calc(i0, j0);
                }
                MAP[i][j].temp = res;
                break;
            default:
                break;
            }
            return MAP[i][j].temp;
        }
    }
}
