#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Pair = pair<int, int>;

int smallValue() {
    return rnd.next(-20, 20);
}

Pair randomPair() {
    int band = rnd.next(0, 9);
    if (band == 0) {
        return {rnd.any(vector<int>{-1000000, -999999, 999999, 1000000}),
                rnd.any(vector<int>{-1000000, -1, 0, 1, 1000000})};
    }
    if (band <= 2) {
        return {rnd.next(-1000, 1000), rnd.next(-1000, 1000)};
    }
    return {smallValue(), smallValue()};
}

void addDistinctPair(vector<Pair>& pairs, set<Pair>& used, Pair candidate) {
    for (int attempt = 0; attempt < 100 && used.count(candidate); ++attempt) {
        candidate = randomPair();
    }
    if (used.insert(candidate).second) {
        pairs.push_back(candidate);
    }
}

vector<Pair> makeUniqueish() {
    int n = rnd.next(1, 18);
    vector<Pair> pairs;
    set<Pair> used;
    int style = rnd.next(0, 2);

    for (int i = 0; i < n; ++i) {
        Pair p;
        if (style == 0) {
            int a = i + 1;
            int b = rnd.next(-8, 8);
            p = {a, b};
        } else if (style == 1) {
            int a = rnd.next(-12, 12);
            int b = i + rnd.next(1, 5);
            p = {a, b};
        } else {
            p = randomPair();
        }
        addDistinctPair(pairs, used, p);
    }

    while ((int)pairs.size() < n) {
        addDistinctPair(pairs, used, randomPair());
    }
    return pairs;
}

vector<Pair> makeDuplicateCluster() {
    Pair base = randomPair();
    int n = rnd.next(4, 14);
    vector<Pair> pairs(n, base);

    int noise = rnd.next(0, min(4, n - 1));
    for (int i = 0; i < noise; ++i) {
        pairs[rnd.next(n)] = randomPair();
    }
    shuffle(pairs.begin(), pairs.end());
    return pairs;
}

vector<Pair> makeZeroHeavy() {
    int n = rnd.next(3, 20);
    vector<Pair> pairs;
    vector<Pair> pool = {{0, 0}, {0, 1}, {1, 0}, {-1, 0}, {0, -1},
                         {1, 1}, {-1, -1}, {2, 0}, {0, 2}};
    for (int i = 0; i < n; ++i) {
        Pair p = rnd.any(pool);
        if (rnd.next(0, 4) == 0) {
            p = {rnd.next(-3, 3), rnd.next(-3, 3)};
        }
        pairs.push_back(p);
    }
    return pairs;
}

vector<Pair> makeBoundaryMix() {
    vector<Pair> pool = {{-1000000, -1000000}, {-1000000, 1000000},
                         {1000000, -1000000}, {1000000, 1000000},
                         {-1000000, 0},       {1000000, 0},
                         {0, -1000000},       {0, 1000000},
                         {-999999, 1000000},  {999999, -1000000}};
    shuffle(pool.begin(), pool.end());
    pool.resize(rnd.next(1, (int)pool.size()));
    return pool;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    vector<Pair> pairs;
    if (mode == 0) {
        pairs = makeUniqueish();
    } else if (mode == 1) {
        pairs = makeDuplicateCluster();
    } else if (mode == 2) {
        pairs = makeZeroHeavy();
    } else {
        pairs = makeBoundaryMix();
    }

    println((int)pairs.size());
    for (Pair p : pairs) {
        println(p.first, p.second);
    }

    return 0;
}
