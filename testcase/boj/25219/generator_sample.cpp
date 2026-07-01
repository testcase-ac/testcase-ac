#include "testlib.h"

#include <vector>
using namespace std;

vector<int> makeArray(int n, int k, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = i % k + 1;
    } else if (mode == 1) {
        int x = rnd.next(1, k);
        int y = rnd.next(1, k);
        while (y == x) y = rnd.next(1, k);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? x : y);
    } else if (mode == 2) {
        int cycleLen = rnd.next(2, k);
        vector<int> labels;
        for (int i = 1; i <= k; ++i) labels.push_back(i);
        shuffle(labels.begin(), labels.end());
        labels.resize(cycleLen);
        for (int i = 0; i < n; ++i) a[i] = labels[i % cycleLen];
    } else if (mode == 3) {
        int pos = 0;
        while (pos < n) {
            int value = rnd.next(1, k);
            int len = rnd.next(1, min(4, n - pos));
            for (int j = 0; j < len; ++j) a[pos++] = value;
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a[i] = min(i + 1, k);
        for (int i = k; i < n; ++i) a[i] = rnd.next(1, k);
        shuffle(a.begin(), a.end());
    } else {
        int active = rnd.next(2, k);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, active);
    }

    return a;
}

pair<int, int> makeQuery(int n, int mode) {
    if (mode == 0) {
        int x = rnd.next(1, n - 1);
        return {x, x + 1};
    }
    if (mode == 1) {
        int x = rnd.next(1, n - 1);
        int y = rnd.next(x + 1, min(n, x + rnd.next(2, 6)));
        return {x, y};
    }
    if (mode == 2) {
        int x = rnd.next(1, n / 2);
        int y = rnd.next(max(x + 1, n / 2), n);
        return {x, y};
    }
    int x = rnd.next(1, n - 1);
    int y = rnd.next(x + 1, n);
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 5) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(6, 25);
    }

    int k;
    if (mode == 1) {
        k = 2;
    } else if (mode == 4 && n >= 5) {
        k = rnd.next(5, n);
    } else {
        k = rnd.next(2, n);
    }

    int q = (mode == 5 ? rnd.next(20, 80) : rnd.next(1, 18));
    vector<int> a = makeArray(n, k, mode);

    println(n, k, q);
    println(a);
    for (int i = 0; i < q; ++i) {
        pair<int, int> query = makeQuery(n, rnd.next(0, 3));
        println(query.first, query.second);
    }

    return 0;
}
