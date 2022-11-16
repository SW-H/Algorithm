#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define START                                                                  \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

vector<int> getEdge(pair<int, int> start, int height, int width);
vector<int> shift(vector<int> edge);
void apply(pair<int, int> start, vector<int> edge, int height, int width);

vector<vector<int> > edges(301);
vector<int> getEdge(pair<int, int> start, int height, int width);

long long arr[301][301];
int N, M;
long long R;

int main() {
    START
    int orgN, orgM;
    cin >> N >> M >> R;
    orgN = N;
    orgM = M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }
    int cnt = min(N, M) / 2;
    for (int i = 0; i < cnt; i++) {
        edges[i] = (getEdge(make_pair(i, i), N, M));
        edges[i] = shift(edges[i]);
        // for (int tmp = 0; tmp < edges[i].size(); tmp++) {
        //     cout << edges[i][tmp] << " ";
        // }
        // cout << "\n";
        apply(make_pair(i, i), edges[i], N, M);
        // for (int tmp = 0; tmp < edges[i].size(); tmp++) {
        //     cout << edges[i][tmp] << " ";
        // }
        // cout << "\n";
        // for (int i = 0; i < orgN; i++) {
        //     for (int j = 0; j < orgM; j++) {
        //         cout << arr[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        M -= 2;
        N -= 2;
    }

    for (int i = 0; i < orgN; i++) {
        for (int j = 0; j < orgM; j++) {
            cout << arr[i][j] << " ";
        }
        if (i != orgN - 1) {
            cout << "\n";
        }
    }
}

vector<int> getEdge(pair<int, int> start, int height, int width) {
    vector<int> edge;
    for (int col = start.second; col < start.second + width; col++) {
        edge.push_back(arr[start.first][col]);
    }
    for (int row = start.first + 1; row < start.first + height - 1; row++) {
        edge.push_back(arr[row][start.second + width - 1]);
    }
    for (int col = start.second + width - 1; col >= start.second; col--) {
        edge.push_back(arr[start.first + height - 1][col]);
    }
    for (int row = start.first + height - 2; row > start.first; row--) {
        edge.push_back(arr[row][start.second]);
    }
    return edge;
}

vector<int> shift(vector<int> edge) {
    reverse(edge.begin(), edge.begin() + R);
    reverse(edge.begin() + R, edge.end());
    reverse(edge.begin(), edge.end());
    return edge;
}

void apply(pair<int, int> start, vector<int> edge, int height, int width) {
    int cnt = 0;
    for (int col = start.second; col < start.second + width; col++) {
        arr[start.first][col] = edge[cnt];
        cnt++;
    }
    for (int row = start.first + 1; row < start.first + height - 1; row++) {
        arr[row][start.second + width - 1] = edge[cnt];
        cnt++;
    }
    for (int col = start.second + width - 1; col >= start.second; col--) {
        arr[start.first + height - 1][col] = edge[cnt];
        cnt++;
    }
    for (int row = start.first + height - 2; row > start.first; row--) {
        arr[row][start.second] = edge[cnt];
        cnt++;
    }
}