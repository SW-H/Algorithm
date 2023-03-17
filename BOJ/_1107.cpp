#include <cstring>
#include <iostream>
#define CURRENT_CH 100
#define CH_MAX 500000
using namespace std;
int target;
int M;
int brokenButton[11];

int moveWithVolumne();
int moveWithButton();
bool isBroken(string target);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> target;
    cin >> M;
    int button;
    for (int i = 0; i < M; i++) {
        // cin >> brokenButton[i];
        cin >> button;
        brokenButton[button]++;
    }

    if (target == CURRENT_CH) {
        cout << 0;
        return 0;
    }
    cout << min(moveWithVolumne(), moveWithButton());
}

int moveWithVolumne() { // +,-버튼으로만 이동
    return max(CURRENT_CH - target, target - CURRENT_CH);
}

int moveWithButton() {
    int res = 0, inc = CH_MAX * 2.5, dec = CH_MAX * 2.5;
    int channel = target;
    string targetStr = to_string(channel);

    while (isBroken(targetStr) && channel <= 2.5 * CH_MAX) {
        channel = (channel + 1);
        targetStr = to_string(channel);
    }
    inc = targetStr.size(); // 이동할 채널 버튼 누르기
    inc += abs(channel - target);

    channel = target;
    targetStr = to_string(channel);
    while (isBroken(targetStr) && channel > -1) {
        channel = (channel - 1);
        targetStr = to_string(channel);
    }
    if (channel != -1) {
        dec = abs(channel - target);
        dec += targetStr.size();
    }
    return min(inc, dec);
}

bool isBroken(string target) {
    for (int i = 0; i < target.size(); i++) {
        if(brokenButton[target[i]-'0']){
            return true;
        }
    }
    return false;
    // for (int i = 0; i < target.size(); i++) {
    //     for (int j = 0; j < M; j++) {
    //         if (target[i] == '0' + brokenButton[j]) {
    //             return true;
    //         }
    //     }
    // }
    // return false;
}