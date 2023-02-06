#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
class Soldier {
  public:
    int mID;
    int mTeam;
    int mScore;

    Soldier(int mID, int mTeam, int mScore) {
        this->mID = mID;
        this->mTeam = mTeam;
        this->mScore = mScore;
    }
};

vector<map<int, Soldier> /**/> soldiers(6, map<int, Soldier>());
bool comparator(pair<int, Soldier> &a, pair<int, Soldier> &b);

void init() {
    for (int team = 1; team <= 5; team++) {
        soldiers[team].clear();
    }
}

void hire(int mID, int mTeam, int mScore) {
    Soldier newSoldier = Soldier(mID, mTeam, mScore);
    soldiers[mTeam].insert(
        soldiers[mTeam].end(),
        pair<int, Soldier>(mID, Soldier(mID, mTeam, mScore)));
}

void fire(int mID) {
    for (int team = 1; team <= 5; team++) {
        if (soldiers[team].erase(mID) > 0) {
            break;
        }
    }
}

void updateSoldier(int mID, int mScore) {
    map<int, Soldier>::iterator it;
    for (int team = 1; team <= 5; team++) {
        if ((it = soldiers[team].find(mID)) != soldiers[team].end()) {
            it->second.mScore = mScore;
        }
    }
}

void updateTeam(int mTeam, int mChangeScore) {
    map<int, Soldier>::iterator it;
    for (it = soldiers[mTeam].begin(); it != soldiers[mTeam].end(); it++) {
        if (it->second.mScore + mChangeScore > 5) {
            it->second.mScore = 5;
        } else if (it->second.mScore + mChangeScore < 1) {
            it->second.mScore = 1;
        } else {
            it->second.mScore += mChangeScore;
        }
    }
}

int bestSoldier(int mTeam) {
    int bestScore,id;
    if (soldiers[mTeam].size() == 1) {
        return soldiers[mTeam].begin()->first;
    }
    vector<pair<int, Soldier> /**/> tmp(soldiers[mTeam].begin(),
                                        soldiers[mTeam].end());
    sort(tmp.begin(), tmp.end(), comparator);
    return tmp[0].first;
    // map<int, Soldier>::iterator it;
    // for (it = soldiers[mTeam].begin(); it != soldiers[mTeam].end(); it++) {
    //     if (it->second.mScore >= bestScore) {
    //         if (it->second.mScore == bestScore && it->first > id) {
    //             bestScore = it->second.mScore;
    //             id = it->first;
    //         }
    //     }
    //     return id;
    // }
}
bool comparator(pair<int, Soldier> &a, pair<int, Soldier> &b) {
    if (a.second.mScore >= b.second.mScore) {
        if (a.second.mScore == b.second.mScore) {
            return a.second.mID > b.second.mID;
        }
        return a.second.mScore > b.second.mScore;
    }
    return false;
}

////////////////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_HIRE 2
#define CMD_FIRE 3
#define CMD_UPDATE_SOLDIER 4
#define CMD_UPDATE_TEAM 5
#define CMD_BEST_SOLDIER 6

extern void init();
extern void hire(int mID, int mTeam, int mScore);
extern void fire(int mID);
extern void updateSoldier(int mID, int mScore);
extern void updateTeam(int mTeam, int mChangeScore);
extern int bestSoldier(int mTeam);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run() {
    int numQuery;

    int mID, mTeam, mScore, mChangeScore;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i) {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
        case CMD_INIT:
            init();
            isCorrect = true;
            break;
        case CMD_HIRE:
            scanf("%d %d %d", &mID, &mTeam, &mScore);
            hire(mID, mTeam, mScore);
            break;
        case CMD_FIRE:
            scanf("%d", &mID);
            fire(mID);
            break;
        case CMD_UPDATE_SOLDIER:
            scanf("%d %d", &mID, &mScore);
            updateSoldier(mID, mScore);
            break;
        case CMD_UPDATE_TEAM:
            scanf("%d %d", &mTeam, &mChangeScore);
            updateTeam(mTeam, mChangeScore);
            break;
        case CMD_BEST_SOLDIER:
            scanf("%d", &mTeam);
            userAns = bestSoldier(mTeam);
            scanf("%d", &ans);
            if (userAns != ans) {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

int main() {
    setbuf(stdout, NULL);
    freopen("/Users/seung-won/Downloads/sample_25_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}