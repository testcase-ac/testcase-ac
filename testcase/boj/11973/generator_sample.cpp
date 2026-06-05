#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {

void addUnique(set<int>& used, int x) {
    used.insert(x);
}

void fillRandom(set<int>& used, int n, int lo, int hi) {
    while ((int)used.size() < n) {
        addUnique(used, rnd.next(lo, hi));
    }
}

vector<int> buildClustered(int n) {
    set<int> used;
    int clusters = rnd.next(1, min(n, 4));
    int span = rnd.next(2, 25);

    for (int c = 0; c < clusters && (int)used.size() < n; ++c) {
        int base = rnd.next(0, 1000000000 - span);
        int want = (n - (int)used.size() + clusters - c - 1) / (clusters - c);
        for (int i = 0; i < want && (int)used.size() < n; ++i) {
            addUnique(used, base + rnd.next(0, span));
        }
    }

    fillRandom(used, n, 0, 1000000000);
    return vector<int>(used.begin(), used.end());
}

vector<int> buildGapped(int n) {
    set<int> used;
    int cur = rnd.next(0, 30);
    int gap = rnd.next(20, 5000);
    for (int i = 0; i < n; ++i) {
        addUnique(used, cur);
        cur += gap + rnd.next(0, gap);
        if (cur > 1000000000) break;
    }
    fillRandom(used, n, 0, 1000000000);
    return vector<int>(used.begin(), used.end());
}

vector<int> buildProgression(int n) {
    set<int> used;
    int step = rnd.next(1, 100);
    int maxStart = 1000000000 - step * (n - 1);
    int start = rnd.next(0, max(0, maxStart));
    for (int i = 0; i < n; ++i) {
        int jitter = rnd.next(0, min(step / 2, 3));
        addUnique(used, min(1000000000, start + step * i + jitter));
    }
    fillRandom(used, n, 0, 1000000000);
    return vector<int>(used.begin(), used.end());
}

vector<int> buildBoundary(int n) {
    set<int> used;
    addUnique(used, 0);
    if (n > 1) addUnique(used, 1000000000);
    if (n > 2) addUnique(used, 1);
    if (n > 3) addUnique(used, 999999999);
    fillRandom(used, n, 0, 1000000000);
    return vector<int>(used.begin(), used.end());
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 18);
    if (rnd.next(0, 9) == 0) n = rnd.next(19, 60);

    int k;
    if (rnd.next(0, 4) == 0) {
        k = rnd.next(1, 10);
    } else {
        k = rnd.next(1, min(10, n));
    }

    vector<int> positions;
    if (mode == 0) {
        positions = buildClustered(n);
    } else if (mode == 1) {
        positions = buildGapped(n);
    } else if (mode == 2) {
        positions = buildProgression(n);
    } else {
        positions = buildBoundary(n);
    }

    shuffle(positions.begin(), positions.end());

    println(n, k);
    for (int x : positions) {
        println(x);
    }

    return 0;
}
