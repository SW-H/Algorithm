#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef struct _Gift {
    _Gift *prev;
    _Gift *next;
    int info;
} Gift;

pair<Gift *, Gift *> belts[111111]; // 각 벨트 처음과 끝
Gift pool[222222];
int giftCnt[111111];

static int poolCapacity;
int belt, gift;

void order_100(int belt, int gift);
int order_200(int src, int dst);
int order_300(int src, int dst);
int order_400(int src, int dst, int cnt);
int order_500(int giftNum);
int order_600(int beltNum);
void giftCopy(Gift *to, Gift *from);
void debug();

int main() {
    int order, orderN;
    cin >> order;

    int src, dst;
    for (int q = 0; q < order; q++) {
        cin >> orderN;
        switch (orderN) {
        case (100):
            cin >> belt >> gift;
            order_100(belt, gift);
            break;
        case (200):
            cin >> src >> dst;
            cout << order_200(src, dst) << "\n";
            break;
        case (300):
            cin >> src >> dst;
            cout << order_300(src, dst) << "\n";
            break;
        case (400):
            cin >> src >> dst;
            cout << order_400(src, dst, (giftCnt[src] / 2)) << "\n";
            break;
        case (500):
            cin >> src;
            cout << order_500(src) << "\n";
            break;
        case (600):
            cin >> src;
            cout << order_600(src) << "\n";
            break;
        }
    }
}

void order_100(int belt, int gift) {
    int beltNum;
    for (int g = 1; g <= gift; g++) {
        cin >> beltNum;
        if (belts[beltNum].first == NULL) {
            pool[poolCapacity].info = g;
            belts[beltNum].first = belts[beltNum].second = &pool[poolCapacity];
            poolCapacity++;
        } else {
            pool[poolCapacity].info = g;
            pool[poolCapacity].prev = belts[beltNum].second;
            belts[beltNum].second->next = &pool[poolCapacity];
            belts[beltNum].second = &pool[poolCapacity];
            poolCapacity++;
        }
        giftCnt[beltNum]++;
    }
}

int order_200(int src, int dst) { // src != dst
    if (giftCnt[src] > 0) {
        belts[src].second->next = NULL;
        if (belts[dst].first != NULL) {
            belts[src].second->next = belts[dst].first;
            belts[dst].first->prev = belts[src].second;
        } else {
            belts[dst].second = belts[src].second;
        }
        belts[dst].first = belts[src].first;
        belts[src].first = belts[src].second = NULL;
    }
    giftCnt[dst] += giftCnt[src];
    giftCnt[src] = 0;
    return giftCnt[dst];
}

int order_300(int src, int dst) {
    if ((giftCnt[src] > 0) && (giftCnt[dst] > 0)) {
        Gift *tmp;
        giftCopy(tmp, belts[src].first);
        giftCopy(belts[src].first,belts[dst].first);
        giftCopy(belts[dst].first,tmp);
    } else if (giftCnt[src] > 0) { // 선물 src->dst이동
        belts[dst].first = belts[dst].second = belts[src].first;
        belts[src].first = belts[src].first->next;
        belts[dst].first->next = belts[dst].first->prev=NULL;
        if(belts[src].first == NULL){
            belts[src].second = NULL;
        }
        giftCnt[src]--;
        giftCnt[dst]++;
    } else if (giftCnt[dst] > 0) { // dst->src
        belts[src].first = belts[src].second = belts[dst].first;
        belts[dst].first = belts[dst].first->next;
        belts[src].first->next = belts[src].first->prev=NULL;
        if(belts[dst].first == NULL){
            belts[dst].second = NULL;
        }
        giftCnt[src]++;
        giftCnt[dst]--;
    } else {
        ;
    }
    return giftCnt[dst];
}

void giftCopy(Gift *to, Gift *from) {
    to->prev = from->prev;
    to->next = from->next;
    to->info = from->info;
}

int order_400(int src, int dst, int cnt) {
    if (giftCnt[src] > 1) {
        Gift *lastGift = belts[src].first;
        for (int nxt = 0; (nxt < cnt - 1) && (lastGift != NULL);
             nxt++) {
            lastGift = lastGift->next;
        }
        Gift *newSrcFirst = lastGift->next;
        Gift *newDstFirst = belts[src].first;
        if (belts[dst].first != NULL) {
            belts[dst].first->prev = lastGift;
            lastGift->next = belts[dst].first;
        } else {
            belts[dst].second = lastGift;
            lastGift->next = NULL;
        }
        belts[src].first = newSrcFirst;
        if(belts[src].first == NULL){
            belts[src].second = NULL;
        }
        belts[dst].first = newDstFirst;
        giftCnt[dst] += cnt;
        giftCnt[src] -= cnt;
    }
    
    return giftCnt[dst];
    // dst의 선물 총개수 리턴
}

int order_500(int giftNum) {
    int prev = -1;
    int next = -1;

    if (pool[giftNum - 1].prev != NULL) {
        prev = pool[giftNum - 1].prev->info;
    }
    if (pool[giftNum - 1].next != NULL) {
        next = pool[giftNum - 1].next->info;
    }
    return prev + next * 2;
}

int order_600(int beltNum) {
    int front = -1;
    int end = -1;
    int cnt = 0;
    if (giftCnt[beltNum] > 0) {
        front = belts[beltNum].first->info;
        end = belts[beltNum].second->info;
        cnt = giftCnt[beltNum];
    }
    return front + 2 * end + 3 * cnt;
}

void debug() {
    Gift *tmp;
    cout << "\n[debug]\n";
    for (int i = 1; i <= belt; i++) {
        cout << "[belt_" << i << "]";
        if (belts[i].first != NULL) {
            tmp = belts[i].first;
            while (true) {
                cout << tmp->info << " ";
                if (((tmp = tmp->next) == NULL) ||
                    (belts[i].first == belts[i].second)) {
                    break;
                }
            }
        }
        cout << "\n";
    }
    cout << "[end]\n";
}