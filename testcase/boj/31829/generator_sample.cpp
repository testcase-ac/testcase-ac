#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Edge = tuple<int, int, long long>;

static long long randomWeight(int mode, long long k) {
    if (mode == 0) {
        return rnd.next(1, 8);
    }
    if (mode == 1) {
        return rnd.next(1, 30);
    }
    if (mode == 2) {
        long long lo = max(1LL, k - 5);
        long long hi = min(1000000000LL, k + 5);
        return rnd.next(lo, hi);
    }
    return rnd.any(vector<long long>{1LL, 2LL, 3LL, 999999937LL, 1000000000LL});
}

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, long long w) {
    if (a > b) {
        swap(a, b);
    }
    if (a == b || used.count({a, b})) {
        return;
    }
    used.insert({a, b});
    edges.emplace_back(a, b, w);
}

static pair<int, int> randomUnusedPair(int n, const set<pair<int, int>>& used) {
    vector<pair<int, int>> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!used.count({i, j})) {
                candidates.emplace_back(i, j);
            }
        }
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, mode == 5 ? 18 : 12);
    long long k;
    if (mode == 0) {
        k = rnd.next(1, 6);
    } else if (mode == 1) {
        k = rnd.next(20, 80);
    } else if (mode == 2) {
        k = rnd.next(1, 100);
    } else if (mode == 3) {
        k = rnd.any(vector<long long>{1LL, 2LL, 999999999LL, 1000000000LL});
    } else {
        k = rnd.next(5, 25);
    }

    vector<Edge> sidewalks;
    vector<Edge> roads;
    set<pair<int, int>> sidewalkUsed;
    set<pair<int, int>> roadUsed;

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    for (int i = 1; i < n; ++i) {
        int a = vertices[i];
        int b = vertices[rnd.next(0, i - 1)];
        bool asSidewalk = mode == 0 || (mode != 1 && rnd.next(0, 1) == 0);
        if (asSidewalk) {
            addEdge(sidewalks, sidewalkUsed, a, b, randomWeight(mode % 4, k));
        } else {
            addEdge(roads, roadUsed, a, b, randomWeight((mode + 1) % 4, k));
        }
    }

    if (sidewalks.empty()) {
        auto [a, b] = randomUnusedPair(n, sidewalkUsed);
        addEdge(sidewalks, sidewalkUsed, a, b, randomWeight(0, k));
    }
    if (roads.empty()) {
        auto [a, b] = randomUnusedPair(n, roadUsed);
        addEdge(roads, roadUsed, a, b, randomWeight(1, k));
    }

    int maxEdges = n * (n - 1) / 2;
    int targetSidewalks = rnd.next((int)sidewalks.size(), min(maxEdges, (int)sidewalks.size() + rnd.next(0, n)));
    int targetRoads = rnd.next((int)roads.size(), min(maxEdges, (int)roads.size() + rnd.next(0, n)));

    while ((int)sidewalks.size() < targetSidewalks) {
        auto [a, b] = randomUnusedPair(n, sidewalkUsed);
        addEdge(sidewalks, sidewalkUsed, a, b, randomWeight(rnd.next(0, 3), k));
    }
    while ((int)roads.size() < targetRoads) {
        auto [a, b] = randomUnusedPair(n, roadUsed);
        addEdge(roads, roadUsed, a, b, randomWeight(rnd.next(0, 3), k));
    }

    shuffle(sidewalks.begin(), sidewalks.end());
    shuffle(roads.begin(), roads.end());

    println(n, k, (int)sidewalks.size(), (int)roads.size());
    for (auto [a, b, w] : sidewalks) {
        println(a, b, w);
    }
    for (auto [a, b, w] : roads) {
        println(a, b, w);
    }

    return 0;
}
