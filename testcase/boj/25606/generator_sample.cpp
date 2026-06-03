#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 3) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 35);
    }

    int m;
    if (mode == 1) {
        m = 1;
    } else if (mode == 2) {
        m = rnd.next(9000, 10000);
    } else {
        m = rnd.next(1, 10000);
    }

    int q = rnd.next(4, min(100000, max(4, n * 3)));

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 1) {
            a[i] = rnd.next(1, min(10000, 3 * m + 5));
        } else if (mode == 2) {
            a[i] = rnd.next(max(1, m - 20), 10000);
        } else if (mode == 3) {
            int k = rnd.next(1, 6);
            a[i] = min(10000, k * m);
            if (rnd.next(0, 3) == 0) a[i] = max(1, a[i] - rnd.next(0, min(7, a[i] - 1)));
        } else {
            a[i] = rnd.next(1, 10000);
        }
    }

    vector<pair<int, int>> queries;
    queries.emplace_back(1, 1);
    queries.emplace_back(2, 1);
    queries.emplace_back(1, n);
    if (n > 1) queries.emplace_back(2, n);

    while ((int)queries.size() < q) {
        int type = rnd.next(1, 2);
        int t;
        int bucket = rnd.next(0, 4);
        if (bucket == 0) {
            t = 1;
        } else if (bucket == 1) {
            t = n;
        } else if (bucket == 2) {
            t = rnd.next(1, min(n, 3));
        } else {
            t = rnd.next(1, n);
        }
        queries.emplace_back(type, t);
    }
    shuffle(queries.begin(), queries.end());

    println(n, m, q);
    println(a);
    for (auto [type, t] : queries) {
        println(type, t);
    }

    return 0;
}
