#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MAX_A = 1000000000;

int bounded(long long x) {
    return (int)max(1LL, min((long long)MAX_A, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 18);
    vector<int> a;

    if (mode == 0) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 80);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 1) {
        int g = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) a.push_back(g * rnd.next(1, 20));
    } else if (mode == 2) {
        int g = rnd.next(2, 200000);
        a.push_back(g);
        while ((int)a.size() < n) {
            int type = rnd.next(0, 3);
            if (type == 0) {
                a.push_back(bounded(2LL * g));
            } else if (type == 1) {
                a.push_back(bounded(2LL * g + rnd.next(1, 10)));
            } else if (type == 2) {
                a.push_back(bounded(3LL * g + rnd.next(0, 10)));
            } else {
                a.push_back(bounded(1LL * g * rnd.next(1, 30)));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        int m = rnd.next(1, 30);
        a.push_back(m);
        for (int i = 1; i < n; ++i) {
            int delta = rnd.next(-2, 2);
            a.push_back(bounded(m + delta));
        }
    } else if (mode == 4) {
        n = rnd.next(3, 16);
        int base = rnd.next(100000000, 500000000);
        for (int i = 0; i < n; ++i) {
            int offset = rnd.next(0, 1000);
            a.push_back(bounded(2LL * base + offset));
        }
    } else if (mode == 5) {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(MAX_A - rnd.next(0, 1000));
        }
    } else {
        n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                a.push_back(rnd.next(1, 10));
            } else if (bucket == 1) {
                a.push_back(rnd.next(11, 1000));
            } else if (bucket == 2) {
                a.push_back(rnd.next(100000, 10000000));
            } else {
                a.push_back(rnd.next(900000000, MAX_A));
            }
        }
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);
    return 0;
}
