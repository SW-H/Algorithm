#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> split(string str, string delimiter);

struct dir {
    string name;
    dir *upper;
    unordered_map<string, dir *> subs;
};

dir groups[500000];
dir *root = &groups[0];
int COUNT;

void init(int n) {
    // memset(groups, 0, sizeof(dir) * n);
    groups[0].name = "/"; // 루트디렉토리
    groups[0].subs.clear();
    COUNT = 1;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    string pathStr(path);
    vector<string> routes = split(pathStr, "/");
    dir *loc = &groups[0];
    if (!routes.empty()) {
        for (string route : routes) {
            cout << route << "\n";
            loc = loc->subs[route];
        }
    }
    string nameStr(name);
    groups[COUNT].upper = loc;
    groups[COUNT].name = nameStr;
    loc->subs[nameStr] = &groups[COUNT];
    COUNT++;
}

vector<string> split(string str, string delimiter) {
    vector<string> ret;
    // ret.push_back("/");
    str = str.substr(1, str.length());
    int current, previous = 0;
    current = str.find(delimiter);
    while (current != string::npos) {
        string substring = str.substr(previous, current - previous);
        ret.push_back(substring);
        previous = current + 1;
        current = str.find(delimiter, previous);
    }
    return ret;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
    string pathStr(path);
    vector<string> routes = split(pathStr, "/");
    dir *loc = &groups[0];
    for (int i = 0; i < routes.size() - 1; i++) {
        loc = loc->subs[routes[i]];
    }
    loc->subs.erase(*routes.end());
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    string srcStr(srcPath);
    vector<string> srcRoutes = split(srcStr, "/");
    string dstStr(dstPath);
    vector<string> dstRoutes = split(dstStr, "/");

    dir *srcLoc = &groups[0];
    for (string route : srcRoutes) {
        srcLoc = srcLoc->subs[route];
    }
    dir *dstLoc = &groups[0];
    for (string route : dstRoutes) {
        dstLoc = dstLoc->subs[route];
    }

    for (auto src : srcLoc->subs) {
        dstLoc->subs[src.first] = src.second;
        dstLoc->subs[src.first]->upper = dstLoc;
    }
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    string srcStr(srcPath);
    vector<string> srcRoutes = split(srcStr, "/");
    string dstStr(dstPath);
    vector<string> dstRoutes = split(dstStr, "/");

    dir *srcLoc = &groups[0];
    for (string route : srcRoutes) {
        srcLoc = srcLoc->subs[route];
    }
    dir *dstLoc = &groups[0];
    for (string route : dstRoutes) {
        dstLoc = dstLoc->subs[route];
    }

    for (auto src : srcLoc->subs) {
        dstLoc->subs[src.first] = src.second;
        srcLoc->subs[src.first]->upper = dstLoc;
        srcLoc->subs.erase(src.first);
    }
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
    string pathStr(path);
    vector<string> routes = split(pathStr, "/");
    dir *loc = &groups[0];
    for (string route : routes) {
        loc = loc->subs[route];
    }
    return loc->subs.size();
}

#include <deque>
void bfs(dir *start) {
    deque<dir *> queue;
    queue.push_back(start);
    while (!queue.empty()) {
        // cout << queue.front()->name << " ";
        if (queue.front()->upper) {
            cout << queue.front()->upper->name << " - " << queue.front()->name
                 << "\n";
        }
        queue.pop_front();
        for (auto it = start->subs.begin(); it != start->subs.end(); it++) {
            queue.push_back(it->second);
        }
    }
    cout << "\n";
}

// TODO : BFS 확인 -> 코드(원리) 노션에 정리 -> 테스트 코드 돌려보면서 문제점
// 찾고 코드 수정

int main() {
    init(10);
    char path[] = {'/'};
    char name[] = {'a', 'a'};
    cmd_mkdir(path, name);
    cmd_mkdir("/aa/", "bb");
    cmd_mkdir("/aa/", "cc");
    cmd_mkdir("/aa/bb/", "dd");
    bfs(&groups[0]);
}
