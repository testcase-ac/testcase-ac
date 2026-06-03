#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

struct State {
    long long dist;
    int v;

    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readEoln();

    vector<vector<int>> cost(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        cost[i] = inf.readInts(m, 1, 10000, "cost");
        inf.readEoln();
    }
    inf.readEof();

    const int total = n * m;
    const long long infDist = (1LL << 60);
    vector<long long> dist(total, infDist);
    vector<int> finish(total, -1);
    vector<char> unique(total, true);
    priority_queue<State, vector<State>, greater<State>> pq;

    auto id = [m](int r, int c) {
        return r * m + c;
    };

    for (int r = 0; r < n; ++r) {
        int v = id(r, m - 1);
        dist[v] = 0;
        finish[v] = r;
        pq.push({0, v});
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        if (cur.dist != dist[cur.v]) {
            continue;
        }

        int r = cur.v / m;
        int c = cur.v % m;
        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                continue;
            }

            int nxt = id(nr, nc);
            long long cand = cur.dist + cost[r][c];
            if (cand < dist[nxt]) {
                dist[nxt] = cand;
                finish[nxt] = finish[cur.v];
                unique[nxt] = unique[cur.v];
                pq.push({cand, nxt});
            } else if (cand == dist[nxt]) {
                if (finish[nxt] != finish[cur.v] || !unique[cur.v]) {
                    if (unique[nxt]) {
                        unique[nxt] = false;
                        pq.push({cand, nxt});
                    }
                }
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        int start = id(r, 0);
        ensuref(unique[start], "student %d does not have a unique fastest finish", r + 1);
    }
}
