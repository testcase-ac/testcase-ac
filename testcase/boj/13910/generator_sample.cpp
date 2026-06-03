#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;
    vector<int> sizes;

    if (mode == 0) {
        n = rnd.next(1, 30);
        m = rnd.next(1, 8);
        for (int i = 0; i < m; ++i) sizes.push_back(rnd.next(1, n));
    } else if (mode == 1) {
        int unit = rnd.next(2, 12);
        n = unit * rnd.next(2, 12);
        m = rnd.next(1, 10);
        for (int i = 0; i < m; ++i) sizes.push_back(unit * rnd.next(1, n / unit));
    } else if (mode == 2) {
        n = rnd.next(20, 120);
        int distinct = rnd.next(1, 5);
        vector<int> base;
        for (int i = 0; i < distinct; ++i) base.push_back(rnd.next(1, n));
        m = rnd.next(distinct, 20);
        for (int i = 0; i < m; ++i) sizes.push_back(rnd.any(base));
    } else if (mode == 3) {
        n = rnd.next(50, 250);
        m = rnd.next(5, 25);
        int lo = max(1, n - rnd.next(20, 80));
        for (int i = 0; i < m; ++i) sizes.push_back(rnd.next(lo, n));
    } else if (mode == 4) {
        n = rnd.next(200, 1000);
        m = rnd.next(20, 60);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(3) == 0) {
                sizes.push_back(rnd.next(1, 20));
            } else {
                sizes.push_back(rnd.next(1, n));
            }
        }
    } else {
        n = rnd.next(5000, 10000);
        m = rnd.next(60, 100);
        for (int i = 0; i < m; ++i) sizes.push_back(rnd.next(1, n));
    }

    shuffle(sizes.begin(), sizes.end());

    println(n, m);
    println(sizes);

    return 0;
}
