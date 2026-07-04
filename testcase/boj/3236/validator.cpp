#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxTime = 1000000000000LL;
    const long long kMaxObservedTime = 200LL * kMaxTime;
    const long long kInf = 4000000000000000000LL;

    int n = inf.readInt(1, 200, "N");
    inf.readSpace();
    int m = inf.readInt(1, 20000, "M");
    inf.readEoln();

    vector<vector<long long>> dist(n, vector<long long>(n, kInf));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "corridor_A");
        inf.readSpace();
        int b = inf.readInt(1, n, "corridor_B");
        inf.readSpace();
        // CHECK: The statement gives no upper bound for corridor times; this is
        // a practical cap that keeps all-pairs shortest paths well inside int64.
        long long t = inf.readLong(1LL, kMaxTime, "corridor_T");
        inf.readEoln();

        // CHECK: A corridor connects two rooms; self-loops are not useful input.
        ensuref(a != b, "corridor %d is a self-loop at room %d", i + 1, a);
        --a;
        --b;
        dist[a][b] = min(dist[a][b], t);
        dist[b][a] = min(dist[b][a], t);
    }

    for (int mid = 0; mid < n; ++mid) {
        for (int from = 0; from < n; ++from) {
            if (dist[from][mid] == kInf) {
                continue;
            }
            for (int to = 0; to < n; ++to) {
                if (dist[mid][to] == kInf) {
                    continue;
                }
                dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
            }
        }
    }

    int k = inf.readInt(1, 5000, "K");
    inf.readEoln();

    vector<tuple<int, int, long long>> observations;
    observations.reserve(k);
    for (int i = 0; i < k; ++i) {
        int a = inf.readInt(1, n, "walk_A");
        inf.readSpace();
        int b = inf.readInt(1, n, "walk_B");
        inf.readSpace();
        // CHECK: The statement gives no upper bound for observed travel times;
        // this allows the largest simple-path scale implied by N and corridor T.
        long long t = inf.readLong(0LL, kMaxObservedTime, "walk_T");
        inf.readEoln();

        ensuref(a != b, "walk %d uses the same start and end room %d", i + 1, a);
        observations.emplace_back(a - 1, b - 1, t);
    }

    int candidateCount = 0;
    for (int x = 0; x < n; ++x) {
        for (int y = x + 1; y < n; ++y) {
            bool ok = true;
            for (const auto& [a, b, observed] : observations) {
                long long best = dist[a][b];
                if (dist[a][x] != kInf && dist[y][b] != kInf) {
                    best = min(best, dist[a][x] + dist[y][b]);
                }
                if (dist[a][y] != kInf && dist[x][b] != kInf) {
                    best = min(best, dist[a][y] + dist[x][b]);
                }
                if (best != observed) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ++candidateCount;
            }
        }
    }

    ensuref(candidateCount == 1,
            "teleport location must be possible and unique, found %d candidates",
            candidateCount);

    inf.readEof();
}
