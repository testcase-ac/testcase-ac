#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long t;
    int p;
    vector<int> k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        p = rnd.next(1, 8);
        k.resize(n);
        for (int i = 0; i < n; ++i) k[i] = rnd.next(1, 12);
        t = rnd.next(1, 25);
    } else if (mode == 1) {
        n = rnd.next(8, 20);
        p = rnd.next(1, 3);
        k.resize(n);
        int cheap = rnd.next(1, 4);
        int expensive = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            k[i] = (rnd.next(0, 3) == 0 ? expensive : cheap + rnd.next(0, 3));
        }
        t = rnd.next(15, 120);
    } else if (mode == 2) {
        n = rnd.next(6, 18);
        p = rnd.next(20, 100);
        k.resize(n);
        for (int i = 0; i < n; ++i) k[i] = rnd.next(1, 15);
        t = rnd.next(1LL, min(1000000000LL, 3LL * p + 80));
    } else if (mode == 3) {
        n = rnd.next(10, 30);
        p = rnd.next(1, 20);
        k.resize(n);
        int low = rnd.next(1, 5);
        int high = rnd.next(50, 200);
        for (int i = 0; i < n; ++i) k[i] = (i % 2 == 0 ? low + rnd.next(0, 5) : high + rnd.next(0, 50));
        t = rnd.next(50, 500);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        p = rnd.next(90000, 100000);
        k.resize(n);
        for (int i = 0; i < n; ++i) k[i] = rnd.next(90000, 100000);
        t = rnd.next(1, 1000000000);
    } else {
        n = rnd.next(25, 60);
        p = rnd.next(1, 100);
        k.resize(n);
        int segment = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            bool cheapSegment = (i / segment) % 2 == 0;
            k[i] = cheapSegment ? rnd.next(1, 8) : rnd.next(30, 120);
        }
        t = rnd.next(100, 1000);
    }

    println(n, t, p);
    println(k);

    return 0;
}
