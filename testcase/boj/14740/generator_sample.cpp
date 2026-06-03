#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(3, 30);
    }

    vector<int> diff(n, 0);

    if (mode == 0) {
        diff[0] = 0;
    } else if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) diff[i] = rnd.next(-8, 8);
        int sum = 0;
        for (int x : diff) sum += x;
        diff.back() = -sum;
    } else if (mode == 2) {
        for (int i = 0; i + 1 < n; i += 2) {
            int v = rnd.next(1, 20);
            diff[i] = v;
            diff[i + 1] = -v;
        }
    } else if (mode == 3) {
        int debt = 0;
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < split; ++i) {
            diff[i] = -rnd.next(1, 12);
            debt -= diff[i];
        }
        for (int i = split; i < n; ++i) {
            int remaining = n - i;
            int v = (remaining == 1) ? debt : rnd.next(0, debt);
            diff[i] = v;
            debt -= v;
        }
    } else {
        int ops = rnd.next(n, 3 * n);
        for (int t = 0; t < ops; ++t) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            if (i == j) continue;
            int v = rnd.next(1, 15);
            diff[i] += v;
            diff[j] -= v;
        }
    }

    if (rnd.next(0, 1) == 1) {
        int shift = rnd.next(0, n - 1);
        rotate(diff.begin(), diff.begin() + shift, diff.end());
    }

    int maxAbs = 0;
    for (int x : diff) maxAbs = max(maxAbs, abs(x));

    int base = rnd.next(max(1, maxAbs), max(20, maxAbs + 60));
    vector<int> oil(n), distance(n);
    for (int i = 0; i < n; ++i) {
        oil[i] = base + max(diff[i], 0);
        distance[i] = base + max(-diff[i], 0);
    }

    println(n);
    println(oil);
    println(distance);

    return 0;
}
