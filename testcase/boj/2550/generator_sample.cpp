#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> values(n);
    iota(values.begin(), values.end(), 1);
    return values;
}

static void shuffleBlocks(vector<int>& values) {
    int n = int(values.size());
    for (int left = 0; left < n;) {
        int width = rnd.next(1, min(5, n - left));
        if (rnd.next(0, 1)) {
            reverse(values.begin() + left, values.begin() + left + width);
        }
        left += width;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
    } else if (mode == 5) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(6, 20);
    }

    vector<int> switches = identityPermutation(n);
    vector<int> bulbs = identityPermutation(n);

    if (mode == 0) {
        shuffle(switches.begin(), switches.end());
        shuffle(bulbs.begin(), bulbs.end());
    } else if (mode == 1) {
        shuffle(switches.begin(), switches.end());
    } else if (mode == 2) {
        shuffle(switches.begin(), switches.end());
        bulbs = switches;
        reverse(bulbs.begin(), bulbs.end());
    } else if (mode == 3) {
        shuffleBlocks(switches);
        bulbs = identityPermutation(n);
        shuffleBlocks(bulbs);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int j = (i % 2 == 0) ? i / 2 : n - 1 - i / 2;
            bulbs[i] = j + 1;
        }
        shuffle(switches.begin(), switches.end());
    } else {
        shuffle(switches.begin(), switches.end());
        shuffle(bulbs.begin(), bulbs.end());
    }

    if (rnd.next(0, 3) == 0) {
        reverse(switches.begin(), switches.end());
    }
    if (rnd.next(0, 3) == 0) {
        reverse(bulbs.begin(), bulbs.end());
    }

    println(n);
    println(switches);
    println(bulbs);

    return 0;
}
