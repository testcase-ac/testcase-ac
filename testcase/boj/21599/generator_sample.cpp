#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        a.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        a.assign(n, 1);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        a.assign(n, n);
    } else if (mode == 3) {
        n = rnd.next(2, 25);
        int hi = rnd.next(0, min(n, 5));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, hi));
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) a.push_back(0);
            else if (bucket == 1) a.push_back(1);
            else if (bucket == 2) a.push_back(rnd.next(2, min(n, 6)));
            else a.push_back(rnd.next(max(0, n - 4), n));
        }
    } else if (mode == 5) {
        n = rnd.next(4, 35);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 3 == 0) ? 0 : rnd.next(1, n));
        }
        sort(a.begin(), a.end());
    } else if (mode == 6) {
        n = rnd.next(5, 45);
        for (int i = 0; i < n; ++i) {
            int base = (i * n) / max(1, n - 1);
            a.push_back(rnd.next(max(0, base - 2), min(n, base + 2)));
        }
        shuffle(a.begin(), a.end());
    } else {
        n = rnd.next(20, 80);
        int zeroCount = rnd.next(0, n / 2);
        int fullCount = rnd.next(0, n / 3);
        a.assign(zeroCount, 0);
        a.insert(a.end(), fullCount, n);
        while ((int)a.size() < n) a.push_back(rnd.next(0, n));
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
