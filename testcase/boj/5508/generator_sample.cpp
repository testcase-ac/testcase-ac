#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

array<int, 101> applyButtons(int n, int mask) {
    array<int, 101> state{};
    state.fill(1);

    if (mask & 1) {
        for (int i = 1; i <= n; ++i) state[i] ^= 1;
    }
    if (mask & 2) {
        for (int i = 1; i <= n; i += 2) state[i] ^= 1;
    }
    if (mask & 4) {
        for (int i = 2; i <= n; i += 2) state[i] ^= 1;
    }
    if (mask & 8) {
        for (int i = 1; i <= n; i += 3) state[i] ^= 1;
    }

    return state;
}

vector<int> candidateMasks(int c) {
    vector<int> masks;
    for (int mask = 0; mask < 16; ++mask) {
        int presses = __builtin_popcount(static_cast<unsigned>(mask));
        if (presses <= c && presses % 2 == c % 2) masks.push_back(mask);
    }
    return masks;
}

vector<int> chooseHints(const vector<int>& lamps, int limit) {
    vector<int> shuffled = lamps;
    shuffle(shuffled.begin(), shuffled.end());
    int count = rnd.next(0, min(limit, static_cast<int>(shuffled.size())));
    shuffled.resize(count);
    return shuffled;
}

void printLampList(const vector<int>& lamps) {
    for (int lamp : lamps) {
        printf("%d ", lamp);
    }
    println(-1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int c;
    if (mode == 0) {
        n = rnd.next(10, 16);
        c = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(90, 100);
        c = rnd.next(9990, 10000);
    } else if (mode == 2) {
        n = rnd.any(vector<int>{10, 11, 12, 99, 100});
        c = rnd.any(vector<int>{1, 2, 3, 4, 9999, 10000});
    } else {
        n = rnd.next(10, 100);
        c = rnd.next(1, 10000);
    }

    vector<int> masks = candidateMasks(c);
    int mask = rnd.any(masks);
    array<int, 101> state = applyButtons(n, mask);

    vector<int> onCandidates;
    vector<int> offCandidates;
    for (int lamp = 1; lamp <= n; ++lamp) {
        if (state[lamp]) {
            onCandidates.push_back(lamp);
        } else {
            offCandidates.push_back(lamp);
        }
    }

    vector<int> on;
    vector<int> off;
    if (mode == 3) {
        on = chooseHints(onCandidates, 2);
        off = chooseHints(offCandidates, 0);
    } else if (mode == 4) {
        on = chooseHints(onCandidates, 0);
        off = chooseHints(offCandidates, 2);
    } else {
        on = chooseHints(onCandidates, 2);
        off = chooseHints(offCandidates, 2);
    }

    println(n);
    println(c);
    printLampList(on);
    printLampList(off);

    return 0;
}
