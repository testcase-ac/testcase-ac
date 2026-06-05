#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int clampWeight(int x) {
    return max(1, min(450, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> weights;

    if (mode == 0) {
        n = rnd.next(1, 5);
        int lo = rnd.next(1, 25);
        int hi = rnd.next(lo, min(450, lo + rnd.next(0, 80)));
        for (int i = 0; i < n; ++i) weights.push_back(rnd.next(lo, hi));
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        int base = rnd.next(1, 450);
        for (int i = 0; i < n; ++i) weights.push_back(base);
    } else if (mode == 2) {
        n = rnd.next(2, 24);
        for (int i = 0; i < n; ++i) {
            weights.push_back(rnd.next(0, 1) == 0 ? rnd.next(1, 8) : rnd.next(430, 450));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 25);
        int base = rnd.next(20, 430);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-15, 15);
            weights.push_back(clampWeight(base + delta));
        }
    } else if (mode == 4) {
        int pairs = rnd.next(1, 12);
        n = 2 * pairs + rnd.next(0, 1);
        for (int i = 0; i < pairs; ++i) {
            int a = rnd.next(1, 450);
            int d = rnd.next(-20, 20);
            weights.push_back(a);
            weights.push_back(clampWeight(a + d));
        }
        if ((int)weights.size() < n) weights.push_back(rnd.next(1, 450));
    } else {
        n = rnd.next(10, 35);
        int lo = rnd.next(1, 200);
        int hi = rnd.next(max(lo, 250), 450);
        for (int i = 0; i < n; ++i) weights.push_back(rnd.next(lo, hi));
    }

    shuffle(weights.begin(), weights.end());

    println(n);
    for (int weight : weights) println(weight);

    return 0;
}
