#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int> c;

    if (mode == 0) {
        n = rnd.next(1, 8);
        c.assign(n, rnd.next(0, 3));
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int h = rnd.next(0, n);
        c.reserve(n);
        for (int i = 0; i < h; ++i) {
            c.push_back(rnd.next(h, min(1000000000, h + 20)));
        }
        for (int i = h; i < n; ++i) {
            c.push_back(h == 0 ? 0 : rnd.next(0, h - 1));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 35);
        int center = rnd.next(1, n);
        c.reserve(n);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-2, 2);
            c.push_back(max(0, center + delta));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 60);
        c.reserve(n);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) c.push_back(0);
            else if (bucket == 1) c.push_back(rnd.next(1, n));
            else if (bucket == 2) c.push_back(rnd.next(n + 1, 2 * n + 20));
            else c.push_back(1000000000);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        c.reserve(n);
        for (int i = 0; i < n; ++i) {
            c.push_back(i % 2 == 0 ? rnd.next(0, 2) : rnd.next(n / 2, n + 10));
        }
    } else {
        n = rnd.next(30, 120);
        int maxCitation = rnd.next(n, 3 * n);
        c.reserve(n);
        for (int i = 0; i < n; ++i) {
            c.push_back(rnd.next(0, maxCitation));
        }
    }

    int order = rnd.next(0, 2);
    if (order == 0) {
        shuffle(c.begin(), c.end());
    } else if (order == 1) {
        sort(c.begin(), c.end());
    } else {
        sort(c.rbegin(), c.rend());
    }

    println(n);
    for (int value : c) {
        println(value);
    }

    return 0;
}
