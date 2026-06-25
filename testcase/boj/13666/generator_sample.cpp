#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Road {
    int v;
    int w;
    int p;
};

static bool addRoad(vector<Road>& roads, set<pair<int, int>>& used, int v, int w, int p) {
    if (v == w) return false;
    pair<int, int> key = minmax(v, w);
    if (!used.insert(key).second) return false;
    roads.push_back({v, w, p});
    return true;
}

static vector<pair<int, int>> allPairs(int n) {
    vector<pair<int, int>> pairs;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            pairs.push_back({i, j});
        }
    }
    shuffle(pairs.begin(), pairs.end());
    return pairs;
}

static vector<Road> stronglyConnectedCycle(int n) {
    vector<Road> roads;
    set<pair<int, int>> used;
    for (int i = 1; i <= n; ++i) {
        addRoad(roads, used, i, i == n ? 1 : i + 1, rnd.next(1, 2));
    }

    for (auto [v, w] : allPairs(n)) {
        if ((int)roads.size() >= rnd.next(n, min(n * (n - 1) / 2, n + 5))) break;
        if (rnd.next(2) == 0) swap(v, w);
        addRoad(roads, used, v, w, rnd.next(1, 2));
    }
    return roads;
}

static vector<Road> bidirectionalBackbone(int n) {
    vector<Road> roads;
    set<pair<int, int>> used;
    for (int i = 2; i <= n; ++i) {
        addRoad(roads, used, rnd.next(1, i - 1), i, 2);
    }

    for (auto [v, w] : allPairs(n)) {
        if ((int)roads.size() >= rnd.next(n - 1, min(n * (n - 1) / 2, n + 4))) break;
        if (rnd.next(2) == 0) swap(v, w);
        addRoad(roads, used, v, w, rnd.next(1, 2));
    }
    return roads;
}

static vector<Road> oneWayChain(int n) {
    vector<Road> roads;
    set<pair<int, int>> used;
    for (int i = 1; i < n; ++i) {
        addRoad(roads, used, i, i + 1, 1);
    }
    if ((int)roads.size() < 2) {
        addRoad(roads, used, 1, n, 2);
    }

    for (auto [v, w] : allPairs(n)) {
        if ((int)roads.size() >= rnd.next(max(2, n - 1), min(n * (n - 1) / 2, n + 3))) break;
        if (rnd.next(3) == 0) swap(v, w);
        addRoad(roads, used, v, w, rnd.next(1, 2));
    }
    return roads;
}

static vector<Road> disconnectedParts(int n) {
    vector<Road> roads;
    set<pair<int, int>> used;
    int split = rnd.next(1, n - 1);

    for (int lo : {1, split + 1}) {
        int hi = lo == 1 ? split : n;
        if (hi - lo + 1 < 2) continue;
        for (int i = lo; i < hi; ++i) {
            addRoad(roads, used, i, i + 1, rnd.next(1, 2));
        }
        if (hi - lo + 1 >= 3 && rnd.next(2) == 0) {
            addRoad(roads, used, hi, lo, rnd.next(1, 2));
        }
    }

    while ((int)roads.size() < 2) {
        int v = rnd.next(1, n);
        int w = rnd.next(1, n);
        addRoad(roads, used, v, w, rnd.next(1, 2));
    }
    return roads;
}

static vector<Road> randomSparse(int n) {
    vector<Road> roads;
    set<pair<int, int>> used;
    int target = rnd.next(2, min(n * (n - 1) / 2, n + 6));
    for (auto [v, w] : allPairs(n)) {
        if ((int)roads.size() >= target) break;
        if (rnd.next(2) == 0) swap(v, w);
        addRoad(roads, used, v, w, rnd.next(1, 2));
    }
    return roads;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(4, 8);
    for (int tc = 0; tc < testCount; ++tc) {
        int n = rnd.next(3, 12);
        int mode = rnd.next(5);
        vector<Road> roads;

        if (mode == 0) {
            roads = stronglyConnectedCycle(n);
        } else if (mode == 1) {
            roads = bidirectionalBackbone(n);
        } else if (mode == 2) {
            roads = oneWayChain(n);
        } else if (mode == 3) {
            roads = disconnectedParts(n);
        } else {
            roads = randomSparse(n);
        }

        shuffle(roads.begin(), roads.end());
        println(n, (int)roads.size());
        for (const Road& road : roads) {
            println(road.v, road.w, road.p);
        }
    }

    println(0, 0);
    return 0;
}
