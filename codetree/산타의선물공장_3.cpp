#include <iostream>
#include <unordered_map>
using namespace std;

typedef struct _Box {
    long long id;
    long long weight;
    int belt;
    int status; // 1 : 정상, -1 : 삭제/하차
    _Box *prev;
    _Box *next;
} Box;

typedef struct _Belt {
    Box *front;
    Box *back;
    int status; // 1 : 정상, -1 : 고장
} Belt;

unordered_map<long long, Box *> boxes;
Box pool[111111];
Belt belts[11];
long long n, m, onBelt;
int capacity;

void cmd_100(int belt, int gift);
long long cmd_200(long long arg);
long long cmd_300(long long arg);
int cmd_400(long long arg);
int cmd_500(int arg);
void moveToBack(Box *box, int belt);
void deleteBox(Box *box);
void moveToFront(int belt, Box *from, Box *to = NULL);
void debug();

int main() {
    int q, cmd;
    long long arg;
    cin >> q;
    for (int r = 0; r < q; r++) {
        cin >> cmd;
        if (cmd == 100) {
            cin >> n >> m;
            onBelt = n / m;
            cmd_100(m, n);
        } else {
            cin >> arg;
            switch (cmd) {
            case 200:
                cout << cmd_200(arg) << "\n";
                break;
            case 300:
                cout << cmd_300(arg) << "\n";
                break;
            case 400:
                cout << cmd_400(arg) << "\n";
                break;
            case 500:
                cout << cmd_500(arg) << "\n";
                break;
            }
        }
        debug();
    }
}

void cmd_100(int belt, int gift) {
    int id[gift];
    int w[gift];

    for (int box = 1; box <= gift; box++) {
        cin >> id[box];
    }
    for (int box = 1; box <= gift; box++) {
        cin >> w[box];
    }

    for (int b = 1; b <= belt; b++) {
        belts[b].front = &pool[capacity++];
        belts[b].front->next = &pool[capacity];
        belts[b].front->prev = NULL;
        belts[b].status = 1;
        for (int box = 1; box <= onBelt; box++) {
            int idx = (b - 1) * onBelt + box;
            pool[capacity].id = id[idx];
            pool[capacity].belt = b;
            pool[capacity].status = 1;
            pool[capacity].weight = w[idx];
            pool[capacity].prev = &pool[capacity - 1];
            pool[capacity].next = &pool[capacity + 1];
            boxes.insert(make_pair(id[idx], &pool[capacity++]));
        }
        belts[b].back = &pool[capacity];
        belts[b].back->prev = &pool[capacity - 1];
        belts[b].back->next = NULL;
        capacity++;
    }
}
long long cmd_200(long long arg) {
    long long sum = 0;
    for (int b = 1; b <= m; b++) {
        if ((belts[b].front->next == belts[b].back) || // 해당 벨트가 빈 경우
            (belts[b].status == -1)) {
            continue;
        }
        if (belts[b].front->next->weight <= arg) { // 하차
            sum += belts[b].front->next->weight;
            deleteBox(belts[b].front->next);
        } else {
            moveToBack(belts[b].front->next, b);
        }
    }
    return sum;
}
void moveToBack(Box *box, int belt) {
    box->prev->next = box->next;
    box->next->prev = box->prev;
    box->prev = belts[belt].back->prev;
    belts[belt].back->prev = box;
    box->prev->next = box;
    box->next = belts[belt].back;
}

void deleteBox(Box *box) {
    box->prev->next = box->next;
    box->next->prev = box->prev;
    box->status = -1;
}

long long cmd_300(long long arg) {
    if (boxes.find(arg) == boxes.end() || boxes[arg]->status == -1) {
        return -1;
    }
    deleteBox(boxes[arg]);
    return arg;
}

int cmd_400(long long arg) {
    if (boxes.find(arg) == boxes.end() || boxes[arg]->status == -1) {
        return -1;
    }
    Box *from = boxes[arg];
    Box *to = belts[boxes[arg]->belt].back->prev;
    int belt = boxes[arg]->belt;
    if (from == to) {
        moveToFront(belt, from);
    } else {
        moveToFront(belt, from, to);
    }
    return belt;
}

void moveToFront(int belt, Box *from, Box *to) {
    if (to == NULL) {
        from->prev->next = from->next;
        from->next->prev = from->prev;
        from->next = belts[belt].front->next;
        from->prev = belts[belt].front;
        belts[belt].front->next = from;
        from->next->prev = from;
    } else {
        from->prev->next = to->next;
        to->next->prev = from->prev;
        to->next = belts[belt].front->next;
        to->next->prev = to;
        from->prev = belts[belt].front;
        from->prev->next = from;
    }
}

int cmd_500(int arg) {
    if (belts[arg].status == -1) {
        return -1;
    }
    int moveTo = 0;
    belts[arg].status = -1;
    Box *range;
    if (belts[arg].front->next != belts[arg].back) {
        int b = (arg + 1) % (m + 1);
        while (true) {
            if (belts[b].status > 0) {
                moveTo = b;
                range = belts[arg].front->next;
                belts[b].back->prev->next = belts[arg].front->next;
                belts[arg].front->next->prev = belts[b].back->prev;
                belts[b].back->prev = belts[arg].back->prev;
                belts[arg].back->prev->next = belts[b].back;
                break;
            }
            b = (b + 1) % (m + 1);
        }
    }

    Box *ptr;
    ptr = range;
    while (ptr != belts[moveTo].back) {
        ptr->belt = moveTo;
        ptr = ptr->next;
    }

    return arg;
}

void debug() {
    Box *ptr;
    cout << "\n";
    for (int b = 1; b <= m; b++) {
        cout << "belt " << b << " ";
        if (belts[b].status == -1) {
            continue;
        }
        ptr = belts[b].front->next;
        while (ptr != belts[b].back) {
            cout << "[" << ptr->id << " " << ptr->weight << "]";
            ptr = ptr->next;
        }
        cout << "\n";
    }
    cout << "\n";
}
