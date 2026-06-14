#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampNote(int value) {
    return max(1, min(1000000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 6) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(5, 30);
    }

    vector<int> notes;
    notes.reserve(n);

    if (mode == 0) {
        vector<int> anchors = {1, 2, 999999, 1000000};
        for (int i = 0; i < n; ++i) {
            notes.push_back(rnd.any(anchors));
        }
    } else if (mode == 1) {
        int value = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 3) == 0) {
                value = rnd.next(1, 1000000);
            }
            notes.push_back(value);
        }
    } else if (mode == 2) {
        int start = rnd.next(1, 1000000);
        int step = rnd.next(0, min(20000, (1000000 - start) / max(1, n - 1)));
        for (int i = 0; i < n; ++i) {
            notes.push_back(start + i * step);
        }
        if (rnd.next(0, 1)) reverse(notes.begin(), notes.end());
    } else if (mode == 3) {
        int low = rnd.next(1, 1000);
        int high = rnd.next(999001, 1000000);
        for (int i = 0; i < n; ++i) {
            int jitter = rnd.next(0, 20);
            notes.push_back(i % 2 == 0 ? low + jitter : high - jitter);
        }
    } else if (mode == 4) {
        int value = rnd.next(1, 1000000);
        int maxDelta = rnd.next(1, 5000);
        for (int i = 0; i < n; ++i) {
            notes.push_back(value);
            value = clampNote(value + rnd.next(-maxDelta, maxDelta));
        }
    } else if (mode == 5) {
        int first = rnd.next(1, 1000000);
        int second = rnd.next(1, 1000000);
        int third = rnd.next(1, 1000000);
        int block = 0;
        int remaining = 0;
        for (int i = 0; i < n; ++i) {
            if (remaining == 0) {
                ++block;
                remaining = rnd.next(1, 3);
            }
            int pick = block % 3;
            notes.push_back(pick == 0 ? first : (pick == 1 ? second : third));
            --remaining;
        }
    } else {
        int lo = rnd.next(1, 900000);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 100000)));
        for (int i = 0; i < n; ++i) {
            notes.push_back(rnd.next(lo, hi));
        }
    }

    println(n);
    println(notes);
    return 0;
}
