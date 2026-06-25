#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> ns;

    if (mode == 0) {
        int t = rnd.next(1, 8);
        for (int i = 0; i < t; ++i) {
            ns.push_back(rnd.next(1, 16));
        }
    } else if (mode == 1) {
        int lo = rnd.next(1, 16);
        int hi = rnd.next(lo, 16);
        for (int n = lo; n <= hi; ++n) {
            ns.push_back(n);
        }
    } else if (mode == 2) {
        ns = {1, 2, 3, 4, 15, 16};
        shuffle(ns.begin(), ns.end());
        ns.resize(rnd.next(2, (int)ns.size()));
    } else if (mode == 3) {
        int t = rnd.next(8, 20);
        for (int i = 0; i < t; ++i) {
            ns.push_back(rnd.wnext(16, 2) + 1);
        }
    } else {
        int repeated = rnd.next(1, 16);
        int t = rnd.next(2, 12);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 2) == 0) {
                ns.push_back(repeated);
            } else {
                ns.push_back(rnd.next(1, 16));
            }
        }
    }

    println((int)ns.size());
    for (int n : ns) {
        println(n);
    }

    return 0;
}
