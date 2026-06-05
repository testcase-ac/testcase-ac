#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 5) {
        n = rnd.next(45, 120);
    } else {
        n = rnd.next(4, 30);
    }

    vector<int> k;
    k.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(0, n);
            k.push_back(rnd.next(0, 1) ? value : -value);
        }
    } else if (mode == 1) {
        int pivot = rnd.next(0, n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1)) {
                k.push_back(rnd.next(max(1, pivot), n));
            } else {
                k.push_back(-rnd.next(0, pivot));
            }
        }
    } else if (mode == 2) {
        vector<int> pool = {-n, -rnd.next(0, n), 0, rnd.next(1, n), n};
        for (int i = 0; i < n; ++i) {
            k.push_back(rnd.any(pool));
        }
    } else if (mode == 3) {
        int low = rnd.next(0, n);
        int high = rnd.next(low, n);
        for (int i = 0; i < n; ++i) {
            int magnitude = rnd.next(low, high);
            k.push_back(rnd.next(0, 1) ? magnitude : -magnitude);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int near = rnd.next(max(0, i - 2), min(n, i + 2));
            k.push_back(rnd.next(0, 2) == 0 ? -near : max(1, near));
        }
        shuffle(k.begin(), k.end());
    } else {
        for (int i = 0; i < n; ++i) {
            int magnitude = rnd.wnext(n + 1, rnd.next(-3, 3));
            k.push_back(rnd.next(0, 1) ? magnitude : -magnitude);
        }
    }

    println(n);
    println(k);

    return 0;
}
