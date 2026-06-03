#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int clampN(int n) {
    return max(1, min(100000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = rnd.next(1, 40);
    vector<int> ns;
    ns.reserve(t);

    if (mode == 0) {
        t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) {
            ns.push_back(rnd.next(1, 20));
        }
    } else if (mode == 1) {
        t = rnd.next(4, 20);
        int parity = rnd.next(0, 1);
        for (int i = 0; i < t; ++i) {
            int k = rnd.next(0, 50000 - parity);
            ns.push_back(2 * k + 1 + parity);
        }
    } else if (mode == 2) {
        t = rnd.next(6, 24);
        int residue = rnd.next(0, 5);
        for (int i = 0; i < t; ++i) {
            int k = rnd.next(0, (100000 - residue) / 6);
            ns.push_back(clampN(6 * k + residue));
        }
    } else if (mode == 3) {
        t = rnd.next(8, 30);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 2) == 0) {
                ns.push_back(rnd.next(1, 100));
            } else {
                ns.push_back(rnd.next(1000, 100000));
            }
        }
    } else if (mode == 4) {
        t = rnd.next(5, 20);
        int center = rnd.next(1, 100000);
        for (int i = 0; i < t; ++i) {
            ns.push_back(clampN(center + rnd.next(-12, 12)));
        }
    } else {
        t = rnd.next(4, 16);
        for (int i = 0; i < t; ++i) {
            int offset = rnd.next(0, 200);
            ns.push_back(100000 - offset);
        }
    }

    shuffle(ns.begin(), ns.end());

    println(t);
    for (int n : ns) {
        println(n);
    }

    return 0;
}
