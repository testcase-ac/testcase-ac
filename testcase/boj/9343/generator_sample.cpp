#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    vector<int> ns;
    ns.reserve(t);

    int smallCount = rnd.next(3, 8);
    for (int i = 0; i < smallCount && (int)ns.size() < t; ++i) {
        ns.push_back(rnd.next(1, 20));
    }

    vector<int> anchors = {
        1, 2, 3, 4, 5, 10, 50, 100, 999, 1000, 1001,
        99991, 100000, 100001, 499999, 500000, 500001,
        999997, 999998, 999999, 1000000
    };

    while ((int)ns.size() < t) {
        int mode = rnd.next(0, 5);
        int n;

        if (mode == 0) {
            n = rnd.any(anchors);
        } else if (mode == 1) {
            int base = rnd.any(anchors);
            n = min(1000000, max(1, base + rnd.next(-20, 20)));
        } else if (mode == 2) {
            int p = 1 << rnd.next(0, 19);
            n = min(1000000, max(1, p + rnd.next(-3, 3)));
        } else if (mode == 3) {
            n = rnd.next(1, 1000);
        } else if (mode == 4) {
            n = rnd.next(1000, 100000);
        } else {
            n = rnd.next(900000, 1000000);
        }

        ns.push_back(n);
    }

    shuffle(ns.begin(), ns.end());

    println((int)ns.size());
    for (int n : ns) {
        println(n);
    }

    return 0;
}
