#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(4, 30);
    }

    int base = rnd.next(1, 1000000 - n + 1);
    vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
        weights[i] = base + i;
    }

    if (rnd.next(4) == 0) {
        int step = rnd.next(2, 20);
        base = rnd.next(1, 1000000 - step * (n - 1));
        for (int i = 0; i < n; ++i) {
            weights[i] = base + step * i;
        }
    }

    if (mode == 0) {
        shuffle(weights.begin(), weights.end());
    } else if (mode == 1) {
        reverse(weights.begin(), weights.end());
    } else if (mode == 2) {
        int shifts = rnd.next(1, n - 1);
        rotate(weights.begin(), weights.begin() + shifts, weights.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, min(n, 6));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(n);
            int b = rnd.next(n);
            swap(weights[a], weights[b]);
        }
    } else if (mode == 4) {
        vector<int> arranged;
        arranged.reserve(n);
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            arranged.push_back(weights[hi--]);
            if (lo <= hi) {
                arranged.push_back(weights[lo++]);
            }
        }
        weights = arranged;
    } else {
        shuffle(weights.begin(), weights.end());
    }

    println(n);
    for (int weight : weights) {
        println(weight);
    }

    return 0;
}
