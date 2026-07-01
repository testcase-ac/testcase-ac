#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int c;
    vector<int> weights;

    if (mode == 0) {
        c = rnd.next(1, 30);
        weights.push_back(rnd.next(1, c));
    } else if (mode == 1) {
        c = rnd.next(3, 80);
        int base = rnd.next(1, c);
        int n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-2, 2);
            weights.push_back(min(c, max(1, base + delta)));
        }
    } else if (mode == 2) {
        c = rnd.next(6, 120);
        int n = rnd.next(4, 20);
        weights.push_back(c);
        weights.push_back(rnd.next(max(1, c / 2 - 3), min(c, c / 2 + 3)));
        weights.push_back(rnd.next(1, min(c, 5)));
        while ((int)weights.size() < n) {
            weights.push_back(rnd.next(1, c));
        }
    } else if (mode == 3) {
        c = rnd.next(8, 90);
        int n = rnd.next(6, 24);
        int hi = rnd.next(1, min(c, 15));
        for (int i = 0; i < n; ++i) {
            weights.push_back(rnd.next(1, hi));
        }
    } else if (mode == 4) {
        c = rnd.next(1000, 100000);
        weights.push_back(1);
        weights.push_back(c);
        weights.push_back(max(1, c - 1));
        weights.push_back(max(1, c / 2));
        weights.push_back(min(c, c / 2 + 1));
        int n = rnd.next(5, 14);
        while ((int)weights.size() < n) {
            weights.push_back(rnd.next(max(1, c - 20), c));
        }
    } else {
        c = rnd.next(20, 200);
        int n = rnd.next(8, 25);
        int cur = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            cur = min(c, cur + rnd.next(0, 8));
            weights.push_back(cur);
        }
    }

    shuffle(weights.begin(), weights.end());

    println((int)weights.size(), c);
    for (int w : weights) {
        println(w);
    }

    return 0;
}
