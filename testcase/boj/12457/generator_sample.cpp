#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampN(int value) {
    return max(1, min(10000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> ns;
    int t = rnd.next(8, 30);
    int mode = rnd.next(5);

    while ((int)ns.size() < t) {
        int n;
        if (mode == 0) {
            vector<int> edges = {1, 2, 3, 4, 5, 31, 63, 64, 65, 127, 255, 9999, 10000};
            n = rnd.any(edges);
        } else if (mode == 1) {
            int bit = rnd.next(0, 13);
            int base = 1 << bit;
            n = base + rnd.next(-2, 2);
        } else if (mode == 2) {
            int bit = rnd.next(1, 13);
            n = (1 << bit) - 1 + rnd.next(-1, 1);
        } else if (mode == 3) {
            int lo = rnd.next(1, 200);
            int hi = rnd.next(lo, 10000);
            n = rnd.next(lo, hi);
        } else {
            n = rnd.wnext(10000, rnd.next(-3, 3)) + 1;
        }
        ns.push_back(clampN(n));

        if (rnd.next(4) == 0) {
            mode = rnd.next(5);
        }
    }

    println((int)ns.size());
    for (int n : ns) {
        println(n);
    }

    return 0;
}
