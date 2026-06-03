#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, n);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(1, 10000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int distinct = rnd.next(1, n);
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) {
            pool.push_back(rnd.next(1, min(30, 10000)));
        }
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(pool);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? 1 : 10000);
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int base = rnd.next(1, 9993);
        for (int i = 0; i < n; ++i) {
            a[i] = base + rnd.next(0, 7);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 10000);
        }
        if (rnd.next(0, 1)) {
            sort(a.begin(), a.end());
        } else {
            sort(a.rbegin(), a.rend());
        }
    }

    println(n, m);
    println(a);

    return 0;
}
