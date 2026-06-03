#include "testlib.h"

#include <algorithm>
#include <functional>
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

static bool hasUniqueStarts(const vector<vector<int>>& cost) {
    int n = int(cost.size());
    int m = int(cost[0].size());
    int total = n * m;
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
        if (!unique[id(r, 0)]) {
            return false;
        }
    }
    return true;
}

static vector<vector<int>> rowDominant(int n, int m) {
    vector<vector<int>> cost(n, vector<int>(m));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            cost[r][c] = rnd.next(1, 9) + c;
        }
    }
    for (int r = 0; r < n; ++r) {
        int bonus = rnd.next(0, 2);
        for (int c = 0; c < m; ++c) {
            cost[r][c] += bonus;
        }
    }
    return cost;
}

static vector<vector<int>> funnelToRow(int n, int m) {
    int target = rnd.next(n);
    vector<vector<int>> cost(n, vector<int>(m, 50));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            cost[r][c] += abs(r - target) * 8 + rnd.next(0, 3);
        }
    }
    for (int c = 0; c < m; ++c) {
        cost[target][c] = rnd.next(1, 4);
    }
    for (int r = 0; r < n; ++r) {
        cost[r][0] = rnd.next(1, 7);
        cost[r][m - 1] += r == target ? 0 : 35 + abs(r - target);
    }
    return cost;
}

static vector<vector<int>> descendingColumns(int n, int m) {
    vector<vector<int>> cost(n, vector<int>(m));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            int edgeBias = (m - 1 - c) * rnd.next(1, 4);
            int rowBias = (r + 1) * rnd.next(1, 3);
            cost[r][c] = 1 + edgeBias + rowBias + rnd.next(0, 5);
        }
    }
    return cost;
}

static vector<vector<int>> randomSmall(int n, int m) {
    vector<vector<int>> cost(n, vector<int>(m));
    int hi = rnd.next(4, 30);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            cost[r][c] = rnd.next(1, hi);
        }
    }
    return cost;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    if (mode == 1) {
        n = rnd.next(2, 12);
    }
    if (mode == 2) {
        m = rnd.next(2, 12);
    }

    vector<vector<int>> cost;
    for (int attempt = 0; attempt < 200; ++attempt) {
        if (mode == 0) {
            cost = rowDominant(n, m);
        } else if (mode == 1) {
            cost = funnelToRow(n, m);
        } else if (mode == 2) {
            cost = descendingColumns(n, m);
        } else {
            cost = randomSmall(n, m);
        }

        if (hasUniqueStarts(cost)) {
            break;
        }
    }

    if (!hasUniqueStarts(cost)) {
        cost.assign(n, vector<int>(m, 100));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                cost[r][c] = 1 + c + r * 20;
            }
        }
    }

    println(n, m);
    for (int r = 0; r < n; ++r) {
        println(cost[r]);
    }
    return 0;
}
