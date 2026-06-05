#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    return p;
}

vector<int> singleCyclePermutation(int n) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[order[i]] = order[(i + 1) % n];
    }
    return p;
}

vector<int> shortCyclePermutation(int n) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<int> p(n);
    int at = 0;
    while (at < n) {
        int remaining = n - at;
        int len = rnd.next(1, remaining);
        if (remaining > 1 && rnd.next(3) != 0) {
            len = rnd.next(1, min(remaining, 4));
        }

        for (int i = 0; i < len; ++i) {
            p[order[at + i]] = order[at + (i + 1) % len];
        }
        at += len;
    }
    return p;
}

vector<int> randomPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (rnd.next(4) == 0) {
        n = rnd.next(35, 50);
    } else {
        n = rnd.next(2, 18);
    }

    vector<int> p;
    if (mode == 0) {
        p = identityPermutation(n);
    } else if (mode == 1) {
        p = singleCyclePermutation(n);
    } else if (mode == 2) {
        p = shortCyclePermutation(n);
    } else {
        p = randomPermutation(n);
    }

    println(n);
    println(p);
    return 0;
}
