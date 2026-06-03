#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int pickCost() {
    int mode = rnd.next(8);
    if (mode == 0) return 0;
    if (mode == 1) return 1;
    if (mode == 2) return 1000;
    if (mode <= 4) return rnd.next(0, 20);
    return rnd.next(0, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(6, 18);
    } else {
        n = rnd.next(2, 35);
    }

    int a = pickCost();
    int b = pickCost();
    vector<int> x;

    if (mode == 0) {
        x.push_back(rnd.next(0, 1000000));
    } else if (mode == 1) {
        int value = rnd.next(0, 1000000);
        x.assign(n, value);
    } else if (mode == 2) {
        int start = rnd.next(0, 1000000);
        int step = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            long long value = start + 1LL * i * step;
            if (value > 1000000) value = 1000000 - (value % 17);
            x.push_back((int)value);
        }
    } else if (mode == 3) {
        x.push_back(0);
        if (n > 1) x.push_back(1000000);
        while ((int)x.size() < n) x.push_back(rnd.next(0, 1000000));
    } else if (mode == 4) {
        int base = rnd.next(0, 999950);
        for (int i = 0; i < n; ++i) x.push_back(base + rnd.next(0, 50));
    } else if (mode == 5) {
        int clusters = rnd.next(2, min(5, n));
        vector<int> centers;
        for (int i = 0; i < clusters; ++i) centers.push_back(rnd.next(0, 1000000));
        for (int i = 0; i < n; ++i) {
            int center = rnd.any(centers);
            int delta = rnd.next(-10, 10);
            x.push_back(max(0, min(1000000, center + delta)));
        }
    } else {
        for (int i = 0; i < n; ++i) x.push_back(rnd.next(0, 1000000));
    }

    if (rnd.next(2)) shuffle(x.begin(), x.end());
    if (rnd.next(5) == 0) sort(x.begin(), x.end());
    if (rnd.next(5) == 0) reverse(x.begin(), x.end());

    println(n, a, b);
    for (int value : x) println(value);

    return 0;
}
