#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int k = rnd.next(2, 9);
    int t;
    vector<int> queries;

    if (mode == 0) {
        t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) {
            queries.push_back(rnd.next(1, 80));
        }
    } else if (mode == 1) {
        vector<int> anchors;
        int power = 1;
        for (int len = 1; len <= 10 && power <= 1999999999 / k; ++len) {
            power *= k;
            anchors.push_back(power);
        }

        t = rnd.next(6, 20);
        for (int i = 0; i < t; ++i) {
            int base = rnd.any(anchors);
            int delta = rnd.next(-15, 15);
            queries.push_back(max(1, min(1999999999, base + delta)));
        }
    } else if (mode == 2) {
        t = rnd.next(8, 35);
        int lo = rnd.next(1, 5000);
        int hi = rnd.next(lo, min(1999999999, lo + rnd.next(1000, 200000)));
        for (int i = 0; i < t; ++i) {
            queries.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        t = rnd.next(10, 45);
        for (int i = 0; i < t; ++i) {
            int span = rnd.next(0, 2000000);
            queries.push_back(1999999999 - span);
        }
    } else {
        t = rnd.next(20, 99);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 4) == 0) {
                queries.push_back(rnd.next(1, 200));
            } else if (rnd.next(0, 2) == 0) {
                queries.push_back(rnd.next(201, 1000000));
            } else {
                queries.push_back(rnd.next(1000001, 1999999999));
            }
        }
    }

    shuffle(queries.begin(), queries.end());

    println(t, k);
    for (int n : queries) {
        println(n);
    }

    return 0;
}
