#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomPi(int profile) {
    if (profile == 0) return rnd.next(1, 20);
    if (profile == 1) return rnd.next(95, 105);
    if (profile == 2) return rnd.next(99990, 100000);
    return rnd.next(1, 100000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int x;
    vector<int> p;

    if (mode == 0) {
        n = 1;
        x = rnd.any(vector<int>{1, 50, 99, 100});
        p.push_back(randomPi(rnd.next(0, 3)));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        x = rnd.next(1, 100);
        int base = randomPi(rnd.next(0, 3));
        for (int i = 0; i < n; ++i) p.push_back(base);
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        x = rnd.any(vector<int>{1, 2, 50, 99, 100});
        int profile = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) p.push_back(randomPi(profile));
    } else if (mode == 3) {
        n = rnd.next(4, 16);
        x = rnd.next(1, 100);
        int base = randomPi(rnd.next(0, 3));
        int spread = rnd.next(0, min(20, max(0, base - 1)));
        for (int i = 0; i < n; ++i) {
            int lo = max(1, base - spread);
            int hi = min(100000, base + spread);
            p.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 18);
        x = rnd.next(60, 100);
        vector<int> choices = {1, 2, 3, 10, 50, 99, 100, 101, 99999, 100000};
        for (int i = 0; i < n; ++i) p.push_back(rnd.any(choices));
    } else {
        n = rnd.next(2, 20);
        x = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) p.push_back(randomPi(rnd.next(0, 3)));
    }

    shuffle(p.begin(), p.end());
    int kMode = rnd.next(0, 3);
    int k;
    if (kMode == 0) k = 1;
    else if (kMode == 1) k = n;
    else k = rnd.next(1, n);

    println(n, x, k);
    println(p);

    return 0;
}
