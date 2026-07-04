#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Edge = tuple<int, int, long long>;
using Observation = tuple<int, int, long long>;

const long long kInf = 4000000000000000000LL;

vector<vector<long long>> floyd(int n, const vector<Edge>& edges) {
    vector<vector<long long>> dist(n, vector<long long>(n, kInf));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }
    for (const auto& [a, b, t] : edges) {
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
    return dist;
}

long long observedTime(const vector<vector<long long>>& dist, int a, int b, int x, int y) {
    long long best = dist[a][b];
    best = min(best, dist[a][x] + dist[y][b]);
    best = min(best, dist[a][y] + dist[x][b]);
    return best;
}

int countCandidates(const vector<vector<long long>>& dist, const vector<Observation>& observations) {
    int n = dist.size();
    int candidates = 0;
    for (int x = 0; x < n; ++x) {
        for (int y = x + 1; y < n; ++y) {
            bool ok = true;
            for (const auto& [a, b, observed] : observations) {
                if (observedTime(dist, a, b, x, y) != observed) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ++candidates;
            }
        }
    }
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    for (int attempt = 0; attempt < 2000; ++attempt) {
        int n = rnd.next(2, 10);

        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                pairs.emplace_back(i, j);
            }
        }
        shuffle(pairs.begin(), pairs.end());

        vector<Edge> edges;
        vector<pair<int, int>> tree;
        for (int v = 1; v < n; ++v) {
            tree.emplace_back(v, rnd.next(0, v - 1));
        }
        shuffle(tree.begin(), tree.end());
        for (const auto& [a, b] : tree) {
            edges.emplace_back(a, b, rnd.next(1, 30));
        }

        int extra = rnd.next(0, min<int>(pairs.size() - tree.size(), n));
        for (const auto& [a, b] : pairs) {
            bool already = false;
            for (const auto& [u, v, t] : edges) {
                if ((a == u && b == v) || (a == v && b == u)) {
                    already = true;
                    break;
                }
            }
            if (!already && extra > 0) {
                edges.emplace_back(a, b, rnd.next(1, 40));
                --extra;
            }
        }

        int x = rnd.next(0, n - 1);
        int y = rnd.next(0, n - 2);
        if (y >= x) {
            ++y;
        }

        auto dist = floyd(n, edges);
        vector<Observation> allObservations;
        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                long long observed = observedTime(dist, a, b, x, y);
                allObservations.emplace_back(a, b, observed);
            }
        }
        shuffle(allObservations.begin(), allObservations.end());

        vector<Observation> observations;
        for (const auto& observation : allObservations) {
            observations.push_back(observation);
            if (countCandidates(dist, observations) == 1 && observations.size() >= 1U) {
                break;
            }
        }
        if (countCandidates(dist, observations) != 1) {
            continue;
        }

        println(n, static_cast<int>(edges.size()));
        shuffle(edges.begin(), edges.end());
        for (const auto& [a, b, t] : edges) {
            if (rnd.next(2) == 0) {
                println(a + 1, b + 1, t);
            } else {
                println(b + 1, a + 1, t);
            }
        }
        println(static_cast<int>(observations.size()));
        for (const auto& [a, b, t] : observations) {
            if (rnd.next(2) == 0) {
                println(a + 1, b + 1, t);
            } else {
                println(b + 1, a + 1, t);
            }
        }
        return 0;
    }

    quitf(_fail, "failed to generate a uniquely solvable instance");
}
