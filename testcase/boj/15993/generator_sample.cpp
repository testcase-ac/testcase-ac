#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    vector<int> ns;

    if (mode == 0) {
        t = rnd.next(1, 8);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 12));
    } else if (mode == 1) {
        t = rnd.next(3, 15);
        int lo = rnd.next(1, 200);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 500)));
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(lo, hi));
    } else if (mode == 2) {
        t = rnd.next(5, 20);
        int start = rnd.next(1, 99980);
        for (int i = 0; i < t; ++i) ns.push_back(start + i);
    } else if (mode == 3) {
        t = rnd.next(4, 18);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(99900, 100000));
    } else if (mode == 4) {
        t = rnd.next(2, 12);
        for (int i = 0; i < t; ++i) {
            int base = rnd.any(vector<int>{1, 2, 3, 4, 5, 99999, 100000});
            ns.push_back(max(1, min(100000, base + rnd.next(-2, 2))));
        }
    } else {
        t = rnd.next(10, 30);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 100000);
            if (rnd.next(0, 3) == 0) n = rnd.wnext(100000, 3) + 1;
            ns.push_back(n);
        }
    }

    if (rnd.next(0, 1)) shuffle(ns.begin(), ns.end());

    println((int)ns.size());
    for (int n : ns) println(n);

    return 0;
}
