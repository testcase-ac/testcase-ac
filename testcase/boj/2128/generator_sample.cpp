#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> maskToProblems(int mask, int d) {
    vector<int> problems;
    for (int i = 0; i < d; ++i) {
        if (mask & (1 << i)) {
            problems.push_back(i + 1);
        }
    }
    shuffle(problems.begin(), problems.end());
    return problems;
}

int randomSubmask(int baseMask) {
    int mask = 0;
    for (int bit = 0; bit < 15; ++bit) {
        if ((baseMask & (1 << bit)) && rnd.next(2)) {
            mask |= 1 << bit;
        }
    }
    return mask;
}

int randomMaskWithLimit(int d, int limit) {
    vector<int> problems;
    for (int i = 0; i < d; ++i) {
        problems.push_back(i);
    }
    shuffle(problems.begin(), problems.end());

    int count = rnd.next(0, limit);
    int mask = 0;
    for (int i = 0; i < count; ++i) {
        mask |= 1 << problems[i];
    }
    return mask;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int d = rnd.next(1, 15);
    int k = rnd.next(1, d);
    int n = rnd.next(1, 40);
    vector<int> masks;

    if (mode == 0) {
        n = rnd.next(1, 25);
        int limit = rnd.next(0, d);
        for (int i = 0; i < n; ++i) {
            masks.push_back(randomMaskWithLimit(d, limit));
        }
    } else if (mode == 1) {
        n = rnd.next(8, 45);
        k = rnd.any(vector<int>{1, d});
        int groups = rnd.next(1, min(6, 1 << d));
        vector<int> patterns;
        for (int i = 0; i < groups; ++i) {
            patterns.push_back(randomMaskWithLimit(d, d));
        }
        for (int i = 0; i < n; ++i) {
            masks.push_back(rnd.any(patterns));
        }
    } else if (mode == 2) {
        n = rnd.next(10, 50);
        int baseSize = rnd.next(k, d);
        int baseMask = randomMaskWithLimit(d, baseSize);
        while (__builtin_popcount(baseMask) < k) {
            baseMask = randomMaskWithLimit(d, baseSize);
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 70) {
                masks.push_back(randomSubmask(baseMask));
            } else {
                masks.push_back(randomMaskWithLimit(d, d));
            }
        }
    } else {
        d = rnd.next(10, 15);
        k = rnd.next(max(1, d - 3), d);
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            int limit = rnd.next(max(0, k - 2), d);
            masks.push_back(randomMaskWithLimit(d, limit));
        }
    }

    println(n, d, k);
    for (int mask : masks) {
        vector<int> problems = maskToProblems(mask, d);
        printf("%d", int(problems.size()));
        for (int problem : problems) {
            printf(" %d", problem);
        }
        printf("\n");
    }

    return 0;
}
