#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = 1000000;

int freshValue(int& nextSmall, int& nextHigh, int mode) {
    if (mode == 0 && nextSmall <= MAX_VALUE) return nextSmall++;
    if (nextHigh >= 1) return nextHigh--;
    return rnd.next(1, MAX_VALUE);
}

int seenValue(const vector<int>& seen) {
    return seen[rnd.next((int)seen.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 32 : 18);
    int nextSmall = 1;
    int nextHigh = MAX_VALUE;
    vector<vector<int>> pots;
    vector<int> seen;

    for (int i = 0; i < n; ++i) {
        vector<int> pot(3);
        bool canOverlap = !seen.empty();

        if (mode == 0 || (mode == 4 && i % 3 == 0)) {
            for (int j = 0; j < 3; ++j) pot[j] = freshValue(nextSmall, nextHigh, 0);
        } else if (mode == 1 && canOverlap) {
            pot[0] = seenValue(seen);
            pot[1] = freshValue(nextSmall, nextHigh, i % 2);
            pot[2] = freshValue(nextSmall, nextHigh, i % 2);
        } else if (mode == 2) {
            int v = canOverlap && rnd.next(0, 1) ? seenValue(seen) : freshValue(nextSmall, nextHigh, i % 2);
            pot[0] = v;
            pot[1] = rnd.next(0, 1) ? v : freshValue(nextSmall, nextHigh, i % 2);
            pot[2] = rnd.next(0, 2) == 0 ? v : freshValue(nextSmall, nextHigh, i % 2);
        } else if (mode == 3 && canOverlap) {
            pot[0] = seenValue(seen);
            pot[1] = seenValue(seen);
            pot[2] = freshValue(nextSmall, nextHigh, i % 2);
        } else if (mode == 4 && canOverlap) {
            pot[0] = seenValue(seen);
            pot[1] = freshValue(nextSmall, nextHigh, 0);
            pot[2] = rnd.next(0, 1) ? seenValue(seen) : freshValue(nextSmall, nextHigh, 1);
        } else {
            pot[0] = freshValue(nextSmall, nextHigh, i % 2);
            pot[1] = freshValue(nextSmall, nextHigh, i % 2);
            pot[2] = freshValue(nextSmall, nextHigh, i % 2);
        }

        shuffle(pot.begin(), pot.end());
        pots.push_back(pot);
        for (int x : pot) seen.push_back(x);
    }

    if (mode == 5) {
        int anchor = rnd.next(1, MAX_VALUE);
        for (int i = 0; i < n; ++i) {
            pots[i][rnd.next(0, 2)] = anchor;
            if (rnd.next(0, 4) == 0) {
                int duplicatePos = rnd.next(0, 2);
                pots[i][duplicatePos] = anchor;
            }
        }
    }

    println(n);
    for (const auto& pot : pots) println(pot);

    return 0;
}
