#include <iostream>
using namespace std;

#define PREV_SETTING                                                           \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
#define DAYS 14

int money;
int price[DAYS];

typedef struct _stcok {
    int stockCnt; // 구매 주식 개수
    int money;    // 남은 돈
    int sum;
} stock;

int main() {
    cin >> money;
    for (int i = 0; i < DAYS; i++) {
        cin >> price[i];
    }

    stock bnp, timing;
    bnp.money = timing.money = money;
    bnp.sum = timing.sum = 0;
    bnp.stockCnt = timing.stockCnt = 0;

    // bnp
    for (int i = 0; i < DAYS; i++) {
        if (bnp.money > 0 && bnp.money >= price[i]) {
            bnp.stockCnt += (bnp.money / price[i]);
            bnp.money -= (bnp.stockCnt * price[i]);
        }
    }
    bnp.sum = bnp.money + bnp.stockCnt * price[DAYS - 1];

    // timing
    for (int i = 3; i < DAYS; i++) {
        // 매수
        if ((price[i - 3] > price[i - 2]) && (price[i - 2] > price[i - 1]) &&
            (price[i - 1] > price[i]) && (timing.money > 0) &&
            (timing.money >= price[i])) {
            timing.stockCnt += (timing.money / price[i]);
            timing.money -= (timing.stockCnt * price[i]);
        } else if ((price[i - 3] < price[i - 2]) &&
                   (price[i - 2] < price[i - 1]) && (price[i - 1] < price[i])) {
            timing.money += (timing.stockCnt * price[i]);
            timing.stockCnt = 0;
        }
    }
    timing.sum = timing.money + timing.stockCnt * price[DAYS - 1];

    if (bnp.sum > timing.sum) {
        cout << "BNP";
    } else if (bnp.sum < timing.sum) {
        cout << "TIMING";
    } else {
        cout << "SAMESAME";
    }
}