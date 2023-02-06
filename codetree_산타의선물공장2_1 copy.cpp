#include <iostream>
#include <vector>
using namespace std;

#define FACTORY 100
#define MOVE_ALL 200
#define REPLACE 300
#define DIVIDE 400
#define GIFT_INFO 500
#define BELT_INFO 600

typedef struct _Gift {
    _Gift *prev;
    _Gift *next;
    int info;
} Gift;

typedef struct _Belt {
    Gift *start;
    Gift *end;
} Belt;

Belt belts[111111];
int giftCnt[111111];
Gift buf[222222];
static int bufCnt;

void construct(int belt, int gift);
void debug();
int belt, gift;

int main() {
    // int q, order;
    int q = 1;
    // cin >> q;
    for (int cnt = 0; cnt < q; cnt++) {
        // cin >> order;
        int order = 100;
        switch (order) {
        case FACTORY:
            // cin >> belt >> gift;
            belt = 4;
            gift = 6;
            construct(belt, gift);
            // for (int i = 0; i < gift; i++) {
            //     cout << buf[i].info<< "\n";
            // }
            debug();
            break;
        case MOVE_ALL:

            break;
        case REPLACE:

            break;
        case DIVIDE:

            break;
        case GIFT_INFO:

            break;
        case BELT_INFO:

            break;
        }
    }

    return 0;
}

void construct(int belt, int gift) {
    int beltN;
    Gift tmp;
    int n[] = {1, 2, 2, 2, 1, 4};
    for (int g = 1; g <= gift; g++) {
        // cin >> beltN;
        beltN = n[g - 1];
        tmp.info = g;
        tmp.prev = tmp.next = NULL;
        buf[bufCnt++] = tmp;

        // TODO : 정렬되도록 삽입(현재는 제일 끝에 삽입)
        // if (belts[beltN].start == NULL) {
        if (giftCnt[beltN] == 0) {
            belts[beltN].start = &buf[g - 1];
            belts[beltN].end = &buf[g - 1];
            // cout << &buf[g-1] << " ";
            // cout << "\""<< belts[beltN].end<<"\"\n";
        } else {
            // cout << belts[beltN].end << " ";
            buf[g-1].prev = belts[beltN].end;
            belts[beltN].end->next = &buf[g - 1];
            belts[beltN].end = &buf[g - 1];
            // cout << tmp.prev << " " << &buf[g-1] << "\n";
            // cout << "\""<< belts[beltN].end<<"\"\n";
        }
        giftCnt[beltN]++;
    }
}

void debug() {
    Gift *tmp;
    for (int i = 1; i <= belt; i++) {
        if (belts[i].start != NULL) {
            // cout << "belt : " << i << "\n";
            tmp = belts[i].start;
            while (tmp != belts[i].end) {
                cout << tmp->info << " ";
                tmp = tmp->next;
            }
            cout << "\n";
        }
    }

    // tmp = belts[2].start;
    // while (tmp != belts[2].end) {
    //     cout << tmp->prev<<" " <<tmp->next<< " " <<tmp->info << " ";

    //     tmp = tmp->next;
    // }
}