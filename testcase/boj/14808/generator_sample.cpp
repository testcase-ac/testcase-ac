#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    vector<long long> endurance;
    vector<long long> speed;
    vector<vector<long long>> dist;
    vector<pair<int, int>> queries;
};

static vector<pair<int, int>> pickQueries(const vector<long long>& endurance,
                                         const vector<vector<long long>>& originalDist) {
    const long long INF = 4000000000000000000LL;
    int n = static_cast<int>(endurance.size());
    vector<vector<long long>> dist = originalDist;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == -1) {
                dist[i][j] = INF;
            }
        }
        dist[i][i] = 0;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    vector<vector<char>> canDeliver(n, vector<char>(n, false));
    for (int i = 0; i < n; ++i) {
        canDeliver[i][i] = true;
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] <= endurance[i]) {
                canDeliver[i][j] = true;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                canDeliver[i][j] = canDeliver[i][j] || (canDeliver[i][k] && canDeliver[k][j]);
            }
        }
    }

    vector<pair<int, int>> pairs;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u != v && canDeliver[u][v]) {
                pairs.push_back({u, v});
            }
        }
    }
    shuffle(pairs.begin(), pairs.end());
    return pairs;
}

static CaseData makeCase() {
    CaseData data;
    data.n = rnd.next(2, 9);
    int n = data.n;
    int mode = rnd.next(0, 3);

    data.endurance.assign(n, 0);
    data.speed.assign(n, 0);
    data.dist.assign(n, vector<long long>(n, -1));

    for (int i = 0; i < n; ++i) {
        data.speed[i] = rnd.next(1, 1000);
    }

    if (mode == 0) {
        vector<long long> step(n);
        for (int i = 0; i < n; ++i) {
            step[i] = rnd.next(1, 30);
            data.dist[i][(i + 1) % n] = step[i];
            if (rnd.next(0, 1)) {
                data.dist[(i + 1) % n][i] = rnd.next(1, 30);
            }
        }
        for (int i = 0; i < n; ++i) {
            data.endurance[i] = step[i] + rnd.next(0, 5);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            long long farthest = 0;
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                long long d = rnd.next(1, 80);
                data.dist[i][j] = d;
                farthest = max(farthest, d);
            }
            data.endurance[i] = rnd.next(farthest, farthest + 40);
        }
    } else if (mode == 2) {
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());
        for (int i = 0; i < n; ++i) {
            int u = order[i];
            int v = order[(i + 1) % n];
            data.dist[u][v] = rnd.next(1, 25);
        }
        double extraProbability = rnd.next(0.15, 0.45);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && data.dist[i][j] == -1 && rnd.next() < extraProbability) {
                    data.dist[i][j] = rnd.next(1, 70);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            long long cheapestOutgoing = 1000000000LL;
            for (int j = 0; j < n; ++j) {
                if (data.dist[i][j] != -1) {
                    cheapestOutgoing = min(cheapestOutgoing, data.dist[i][j]);
                }
            }
            data.endurance[i] = rnd.next(cheapestOutgoing, cheapestOutgoing + 15);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long prefix = 0;
            for (int j = i + 1; j < n; ++j) {
                long long d = rnd.next(1, 20);
                data.dist[j - 1][j] = d;
                prefix += d;
                if (rnd.next(0, 1)) {
                    data.dist[i][j] = prefix + rnd.next(0, 10);
                }
            }
            data.endurance[i] = max(1LL, prefix) + rnd.next(0, 10);
        }
        for (int i = 1; i < n; ++i) {
            data.dist[i][i - 1] = rnd.next(1, 25);
            data.endurance[i] = max(data.endurance[i], data.dist[i][i - 1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        data.dist[i][i] = -1;
        data.endurance[i] = max(1LL, min(data.endurance[i], 1000000000LL));
    }

    vector<pair<int, int>> reachable = pickQueries(data.endurance, data.dist);
    int maxQueries = min(100, static_cast<int>(reachable.size()));
    int q = rnd.next(1, maxQueries);
    reachable.resize(q);
    data.queries = reachable;
    return data;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        CaseData data = makeCase();
        println(data.n, static_cast<int>(data.queries.size()));
        for (int i = 0; i < data.n; ++i) {
            println(data.endurance[i], data.speed[i]);
        }
        for (int i = 0; i < data.n; ++i) {
            println(data.dist[i]);
        }
        for (auto [u, v] : data.queries) {
            println(u + 1, v + 1);
        }
    }

    return 0;
}
