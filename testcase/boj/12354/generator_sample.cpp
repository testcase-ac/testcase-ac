#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

vector<int> increasingHeights(int n) {
    int start = rnd.next(1, 20);
    vector<int> heights(n);
    heights[0] = start;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            heights[i] = heights[i - 1] + rnd.next(1, 8);
        }
    }
    return heights;
}

vector<int> corruptedIncreasingCase(int n, int removed) {
    vector<int> heights = increasingHeights(n);
    set<int> used;
    while (int(used.size()) < removed) {
        used.insert(rnd.next(0, n - 1));
    }

    for (int idx : used) {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            heights[idx] = rnd.next(1, max(1, heights[max(0, idx - 1)]));
        } else if (mode == 1) {
            heights[idx] = rnd.next(1, 30);
        } else {
            heights[idx] = heights[rnd.next(0, n - 1)];
        }
    }

    return heights;
}

vector<int> smallBadCase(int n) {
    vector<int> heights(n);
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        int high = rnd.next(n, 25);
        for (int i = 0; i < n; ++i) {
            heights[i] = high - i;
        }
    } else if (mode == 1) {
        int value = rnd.next(1, 1000);
        fill(heights.begin(), heights.end(), value);
    } else {
        for (int i = 0; i < n; ++i) {
            heights[i] = rnd.next(1, 12);
        }
    }
    return heights;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        vector<int> heights;

        if (mode == 0) {
            int n = rnd.next(1, 50);
            heights = increasingHeights(n);
        } else if (mode == 1) {
            int n = rnd.next(1, 5);
            heights = smallBadCase(n);
        } else {
            int n = rnd.next(5, 50);
            int removed = rnd.next(1, 4);
            heights = corruptedIncreasingCase(n, removed);
        }

        println(int(heights.size()));
        println(heights);
    }

    return 0;
}
