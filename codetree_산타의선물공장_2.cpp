
// 메모리 초과

// m : 벨트 개수
#include <iostream>
#include <vector>

using namespace std;

typedef struct _Box {
    int status; // 1 : 정상, -1 : 삭제/하차
    long long id;
    long long weight;
    int belt;
    _Box *next;
    _Box *prev;
} Box;

typedef struct _Belt {
    int status; // 1 : 정상, -1 : 고장
    Box *front;
    Box *back;
} Belt;

vector<Box> pool(100000000);
Belt belts[11];
int belt, gift, onBelt;

void cmd_100(int belt, int gift);
long long cmd_200(long long arg);
long long cmd_300(long long arg);
int cmd_400(long long arg);
int cmd_500(int arg);
void debug();

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int cmd;
        long long arg;
        cin >> cmd;
        switch (cmd) {
        case 100:
            cin >> gift >> belt;
            onBelt = gift / belt;
            cmd_100(belt, gift);
            break;
        case 200:
            cin >> arg;
            cout << cmd_200(arg);
            break;
        case 300:
            cin >> arg;
            cout << cmd_300(arg);
            break;
        case 400:
            cin >> arg;
            cout << cmd_400(arg);
            break;
        case 500:
            cin >> arg;
            cout << cmd_500(arg);
            break;
        }
        // debug();
    }
}

void cmd_100(int belt, int gift) {
    int id, w;
    int input[2][gift + 1];

    for (int i = 0; i < 2; i++) {
        for (int box = 1; box <= gift; box++) {
            cin >> input[i][box];
        }
    }
    for (int box = 1; box <= gift; box++) {
        id = input[0][box];
        w = input[1][box];
        pool[id].id = id;
        pool[id].weight = w;
        pool[id].status = 1;
        if (box % onBelt == 1) { // 맨앞
            belts[box / onBelt + 1].front = &pool[id];
            pool[id].prev = pool[id].next = NULL;
            if (box + 1 <= gift) {
                pool[id].next = &pool[input[0][box + 1]];
            }
            pool[box].belt = box / onBelt + 1;
        } else if (box % onBelt == 0) { // 맨뒤
            belts[box / onBelt].back = &pool[id];
            pool[id].prev = pool[id].next = NULL;
            if (box - 1 >= 0) {
                pool[id].prev = &pool[input[0][box - 1]];
            }
            pool[box].belt = box / onBelt;
        } else { // 가운데
            if (box - 1 >= 0) {
                pool[id].prev = &pool[input[0][box - 1]];
            }
            if (box + 1 <= gift) {
                pool[id].next = &pool[input[0][box + 1]];
            }
            pool[box].belt = box / onBelt + 1;
        }
    }
}

long long cmd_200(long long arg) {
    long long sum = 0;
    for (int b = 1; b <= belt; b++) {
        if (belts[b].status == -1) { // 벨트 고장
            continue;
        }
        if (belts[b].front->weight <= arg) { // 하차
            sum += (belts[b].front->weight);
            belts[b].front->status = -1;
            if (belts[b].front->next) {
                belts[b].front->next->prev = NULL;
            }
            belts[b].front = belts[b].front->next;
        } else { // 맨뒤로
            if (belts[b].front && (belts[b].front != belts[b].back)) {
                Box *toMove = belts[b].front;
                belts[b].back->next = toMove;
                toMove->prev = belts[b].back;
                belts[b].front = toMove->next;
                belts[b].back = toMove;
                belts[b].front->prev = NULL;
                belts[b].back->next = NULL;
            }
        }
    }
    return sum;
}

long long cmd_300(long long arg) {
    int beltN = 0;
    if (pool[arg].status == -1) {
        return -1;
    }
    pool[arg].status = -1;

    if ((pool[arg].prev != NULL) && (pool[arg].next != NULL)) {
        pool[arg].prev->next = pool[arg].next;
        pool[arg].prev->next->prev = pool[arg].prev;
        return arg;
    }
    if (pool[arg].prev == NULL) { // 벨트의 맨 앞
        pool[arg].next->prev = NULL;
        belts[beltN].front = pool[arg].next;
    } else { // 벨트의 맨 뒤
        pool[arg].prev->next = NULL;
        belts[beltN].back = pool[arg].prev;
    }
    return arg;
}
int cmd_400(long long arg) {return 0;}
int cmd_500(int arg) {return 0;}

void debug() {
    Box *ptr;
    cout << "\n";
    for (int b = 1; b <= belt; b++) {
        cout << "belt " << b << " ";
        if (belts[b].front != NULL) {
            ptr = belts[b].front;
        }

        while (ptr != NULL) {
            cout << "[" << ptr->id << " " << ptr->weight << "]";
            ptr = ptr->next;
        }
        cout << "\n";
    }
    cout << "\n";
}