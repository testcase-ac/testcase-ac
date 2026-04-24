#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid dimensions
    int R = rnd.next(1, 5);
    int C = rnd.next(2, 10);
    int T = R * C;
    int maxBroken = min(T, 10);

    // Decide how many broken cells, ensure at least 2 for one horizontal tile
    // Bias broken count with wnext: t = -1 (favor small), 0 (uniform), 1 (favor large)
    vector<int> ts = {-1, 0, 1};
    int t = rnd.any(ts);
    // rnd.wnext(hi, t) gives in [0, hi-1], so hi = maxBroken-1 yields [0, maxBroken-2]
    int brokenBase = rnd.wnext(maxBroken - 1, t);
    int brokenCount = brokenBase + 2;
    if (brokenCount > maxBroken) brokenCount = maxBroken;

    // We must embed a horizontal chain of length >=2
    int chainLenMax = min(C, brokenCount);
    int chainLen = rnd.next(2, chainLenMax);

    set<pair<int,int>> broken;
    // Place the guaranteed horizontal chain
    int row0 = rnd.next(1, R);
    int startC = rnd.next(1, C - chainLen + 1);
    for (int i = 0; i < chainLen; i++) {
        broken.insert({row0, startC + i});
    }
    // Add extra broken cells randomly
    while ((int)broken.size() < brokenCount) {
        int rr = rnd.next(1, R);
        int cc = rnd.next(1, C);
        broken.insert({rr, cc});
    }

    // Build undamaged cells (the input lists undamaged)
    vector<pair<int,int>> und;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (!broken.count({i, j}))
                und.emplace_back(i, j);
        }
    }
    shuffle(und.begin(), und.end());

    // Output
    int K = und.size();
    println(R, C, K);
    for (auto &p : und)
        println(p.first, p.second);

    return 0;
}
