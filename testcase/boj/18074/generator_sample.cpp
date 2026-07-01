#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 35));
    vector<int> a(n);

    if (mode == 0) {
        a[0] = rnd.next(1, 60);
    } else if (mode == 1) {
        int value = rnd.next(1, 25);
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        int big = rnd.next(20, 90);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 8);
        a[rnd.next(0, n - 1)] = big;
    } else if (mode == 3) {
        int lo = rnd.next(1, 8);
        int hi = rnd.next(12, 50);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? hi : lo);
    } else if (mode == 4) {
        int cur = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 6);
            a[i] = cur;
        }
    } else {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 45);
    }

    int sum = accumulate(a.begin(), a.end(), 0);
    int maxValue = *max_element(a.begin(), a.end());

    vector<int> queries;
    queries.push_back(1);
    queries.push_back(maxValue);
    queries.push_back(sum);
    if (maxValue > 1) queries.push_back(rnd.next(1, maxValue - 1));

    int prefix = 0;
    for (int i = 0; i < n && static_cast<int>(queries.size()) < 12; ++i) {
        prefix += a[i];
        queries.push_back(prefix);
        if (prefix > 1) queries.push_back(prefix - 1);
    }

    int q = rnd.next(8, 25);
    while (static_cast<int>(queries.size()) < q) {
        int t;
        if (rnd.next(0, 3) == 0) {
            t = rnd.next(max(1, maxValue - 5), min(sum, maxValue + 10));
        } else {
            t = rnd.next(1, sum);
        }
        queries.push_back(t);
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(q);

    println(n);
    println(a);
    println(q);
    println(queries);

    return 0;
}
