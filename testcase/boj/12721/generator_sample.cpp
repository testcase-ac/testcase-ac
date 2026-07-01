#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeQueries(int k, int n, int mode) {
    vector<int> queries;
    queries.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) queries.push_back(i % k + 1);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) queries.push_back(k - (i % k));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) queries.push_back((i % 2 == 0) ? 1 : k);
    } else if (mode == 3) {
        int pivot = rnd.next(1, k);
        for (int i = 0; i < n; ++i) queries.push_back(pivot);
    } else if (mode == 4) {
        int span = min(k, rnd.next(1, 12));
        int base = rnd.next(1, k - span + 1);
        for (int i = 0; i < n; ++i) queries.push_back(base + rnd.next(0, span - 1));
    } else {
        for (int i = 0; i < n; ++i) queries.push_back(rnd.next(1, k));
    }

    return queries;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int T = 100;
    println(T);

    for (int tc = 1; tc <= T; ++tc) {
        int k;
        if (tc <= 8) {
            k = tc;
        } else if (tc <= 18) {
            k = rnd.next(1, 20);
        } else if (tc <= 36) {
            k = rnd.next(21, 120);
        } else if (tc <= 60) {
            k = rnd.next(121, 700);
        } else if (tc <= 82) {
            k = rnd.next(701, 2500);
        } else {
            k = rnd.next(2501, 5000);
        }

        int n;
        if (k <= 8 && tc <= 8) {
            n = k;
        } else if (tc % 10 == 0 || tc > 90) {
            n = 100;
        } else if (tc % 7 == 0) {
            n = rnd.next(1, min(100, k));
        } else {
            n = rnd.next(1, 30);
        }

        int mode = tc % 6;
        vector<int> queries = makeQueries(k, n, mode);

        println(k);
        println(n, queries);
    }

    return 0;
}
