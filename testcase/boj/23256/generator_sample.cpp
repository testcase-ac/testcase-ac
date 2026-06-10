#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1000000;
    int mode = rnd.next(0, 5);
    int T;
    vector<int> ns;

    if (mode == 0) {
        T = rnd.next(1, 12);
        for (int i = 0; i < T; ++i) {
            ns.push_back(rnd.next(1, 20));
        }
    } else if (mode == 1) {
        T = rnd.next(8, 40);
        int center = rnd.next(1, MAX_N);
        int radius = rnd.next(0, 1000);
        for (int i = 0; i < T; ++i) {
            int lo = max(1, center - radius);
            int hi = min(MAX_N, center + radius);
            ns.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        T = rnd.next(10, 60);
        for (int i = 0; i < T; ++i) {
            if (rnd.next(0, 1) == 0) {
                ns.push_back(rnd.next(1, 50));
            } else {
                ns.push_back(rnd.next(MAX_N - 49, MAX_N));
            }
        }
    } else if (mode == 3) {
        T = rnd.next(30, 120);
        for (int i = 0; i < T; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                ns.push_back(rnd.next(1, 100));
            } else if (bucket == 1) {
                ns.push_back(rnd.next(1000, 10000));
            } else if (bucket == 2) {
                ns.push_back(rnd.next(100000, 200000));
            } else {
                ns.push_back(rnd.next(900000, MAX_N));
            }
        }
    } else if (mode == 4) {
        T = 1000;
        for (int i = 0; i < T; ++i) {
            ns.push_back(rnd.next(1, MAX_N));
        }
    } else {
        T = rnd.next(1, 1000);
        for (int i = 0; i < T; ++i) {
            ns.push_back(rnd.next(1, MAX_N));
        }
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(ns.begin(), ns.end());
    }

    println(T);
    for (int n : ns) {
        println(n);
    }

    return 0;
}
