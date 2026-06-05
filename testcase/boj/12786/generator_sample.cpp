#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randInt(int lo, int hi) {
    return lo + static_cast<int>(rnd.next() * (hi - lo + 1));
}

int nextHeightByMove(int h) {
    vector<int> choices;
    choices.push_back(h);
    if (h < 20) choices.push_back(h + 1);
    choices.push_back(min(20, h * 2));
    if (h > 1) choices.push_back(h - 1);
    return choices[randInt(0, static_cast<int>(choices.size()) - 1)];
}

vector<int> randomUniqueHeights(int count) {
    vector<int> pool;
    for (int h = 1; h <= 20; ++h) pool.push_back(h);

    vector<int> heights;
    for (int i = 0; i < count; ++i) {
        int pos = randInt(0, static_cast<int>(pool.size()) - 1);
        heights.push_back(pool[pos]);
        pool.erase(pool.begin() + pos);
    }
    sort(heights.begin(), heights.end());
    return heights;
}

void addNoise(vector<int>& holes, int extraLimit) {
    vector<bool> used(21, false);
    for (int h : holes) used[h] = true;

    vector<int> candidates;
    for (int h = 1; h <= 20; ++h) {
        if (!used[h]) candidates.push_back(h);
    }

    int extra = randInt(0, min(extraLimit, static_cast<int>(candidates.size())));
    for (int i = 0; i < extra; ++i) holes.push_back(candidates[i]);
    sort(holes.begin(), holes.end());
}

vector<int> randomUniqueFromRange(int low, int high, int count) {
    vector<int> pool;
    for (int h = low; h <= high; ++h) pool.push_back(h);

    vector<int> values;
    for (int i = 0; i < count; ++i) {
        int pos = randInt(0, static_cast<int>(pool.size()) - 1);
        values.push_back(pool[pos]);
        pool.erase(pool.begin() + pos);
    }
    sort(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = randInt(0, 5);
    int n = 1;
    int k = 0;
    vector<vector<int>> trees;
    if (mode == 0) {
        n = randInt(1, 4);
        k = randInt(0, 2);
        trees.assign(n, {});
        for (int i = 0; i < n; ++i) {
            trees[i] = randomUniqueHeights(randInt(1, 5));
        }
    } else if (mode == 1) {
        n = randInt(4, 12);
        k = randInt(0, 4);
        trees.assign(n, {});
        for (int i = 0; i < n; ++i) {
            trees[i] = randomUniqueHeights(randInt(8, 20));
        }
    } else if (mode == 2) {
        n = randInt(5, 18);
        k = randInt(0, 3);
        trees.assign(n, {});
        int h = 1;
        for (int i = 0; i < n; ++i) {
            h = nextHeightByMove(h);
            trees[i] = {h};
            addNoise(trees[i], randInt(0, 3));
        }
    } else if (mode == 3) {
        n = randInt(5, 16);
        int forcedTeleports = randInt(1, min(5, n));
        k = randInt(max(0, forcedTeleports - 2), forcedTeleports);
        trees.assign(n, {});
        int h = 1;
        for (int i = 0; i < n; ++i) {
            bool forceTeleport = i > 0 && forcedTeleports > 0 && randInt(0, n - i) < forcedTeleports;
            if (forceTeleport) {
                vector<bool> reachable(21, false);
                reachable[h] = true;
                if (h < 20) reachable[h + 1] = true;
                reachable[min(20, h * 2)] = true;
                if (h > 1) reachable[h - 1] = true;

                vector<int> unreachable;
                for (int nh = 1; nh <= 20; ++nh) {
                    if (!reachable[nh]) unreachable.push_back(nh);
                }
                h = unreachable[randInt(0, static_cast<int>(unreachable.size()) - 1)];
                --forcedTeleports;
            } else {
                h = nextHeightByMove(h);
            }
            trees[i] = {h};
            addNoise(trees[i], randInt(0, 2));
        }
    } else {
        n = randInt(6, 18);
        k = randInt(0, 2);
        trees.assign(n, {});
        int bandLow = randInt(1, 15);
        int bandHigh = randInt(bandLow, min(20, bandLow + randInt(0, 5)));
        for (int i = 0; i < n; ++i) {
            int count = randInt(1, bandHigh - bandLow + 1);
            trees[i] = randomUniqueFromRange(bandLow, bandHigh, count);
        }
    }

    println(n);
    println(k);
    for (const vector<int>& holes : trees) {
        printf("%d", static_cast<int>(holes.size()));
        for (int h : holes) printf(" %d", h);
        printf("\n");
    }

    return 0;
}
