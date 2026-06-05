#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int, int, int>> tests;

    auto add = [&](int n, int m, int k) {
        n = max(1, min(10, n));
        m = max(1, min(10, m));
        k = max(1, min(10, k));
        tests.emplace_back(n, m, k);
    };

    int targetT = rnd.next(35, 80);

    add(1, rnd.next(1, 10), rnd.next(1, 10));
    add(rnd.next(2, 10), 1, 1);
    add(10, 1, rnd.next(1, 10));
    add(10, 10, 1);
    add(rnd.next(7, 10), rnd.next(1, 3), rnd.next(2, 4));

    while ((int)tests.size() < targetT) {
        int mode = rnd.next(8);
        if (mode == 0) {
            int n = rnd.next(1, 10);
            int k = rnd.next(1, 10);
            int m = rnd.next((n + k - 1) / k, 10);
            add(n, m, k);
        } else if (mode == 1) {
            int n = rnd.next(2, 10);
            int k = rnd.next(1, 9);
            int m = max(1, (n - 1) / k);
            add(n, m, k);
        } else if (mode == 2) {
            int n = rnd.next(2, 10);
            int m = rnd.next(1, 10);
            int k = max(1, (n + m - 1) / m);
            add(n, m, k);
        } else if (mode == 3) {
            add(rnd.next(1, 10), rnd.next(1, 2), rnd.next(1, 10));
        } else if (mode == 4) {
            add(rnd.next(1, 10), rnd.next(9, 10), rnd.next(1, 2));
        } else if (mode == 5) {
            int k = rnd.next(1, 10);
            add(rnd.next(1, min(10, 2 * k)), 2, k);
        } else if (mode == 6) {
            add(rnd.next(8, 10), rnd.next(1, 10), rnd.next(1, 10));
        } else {
            add(rnd.next(1, 10), rnd.next(1, 10), rnd.next(1, 10));
        }
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (auto [n, m, k] : tests) {
        println(n, m, k);
    }

    return 0;
}
