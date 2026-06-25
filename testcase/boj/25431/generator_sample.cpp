#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = 10000000;

int edgeValue() {
    static const vector<int> values = {
        0, 1, 2, 3, 7, 15, 31, 63, 64, 127, 255, 1023,
        1048575, 8388607, MAX_VALUE - 1, MAX_VALUE
    };
    return rnd.any(values);
}

int randomValue(int mode) {
    if (mode == 0) return edgeValue();
    if (mode == 1) return rnd.next(0, 64);
    if (mode == 2) {
        int base = rnd.any(vector<int>{0, 1, 15, 31, 63, 127, 255, 1023, 1048575});
        int bit = rnd.next(0, 23);
        return min(MAX_VALUE, base ^ (1 << bit));
    }
    if (mode == 3) return rnd.next(max(0, MAX_VALUE - 200), MAX_VALUE);
    return rnd.next(0, MAX_VALUE);
}

pair<int, int> randomRange(int n, int mode) {
    if (mode == 0 || n == 1) {
        int p = rnd.next(1, n);
        return {p, p};
    }
    if (mode == 1) return {1, n};

    int l = rnd.next(1, n);
    int span = rnd.next(0, min(n - l, max(0, n / 3)));
    return {l, l + span};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 8);
    } else if (mode == 3) {
        n = rnd.next(8, 20);
    } else {
        n = rnd.next(20, 60);
    }

    vector<int> a(n);
    if (mode == 0) {
        a[0] = randomValue(rnd.next(0, 4));
    } else if (mode == 1) {
        int first = randomValue(0);
        int second = randomValue(rnd.next(0, 2));
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? first : second);
    } else if (mode == 2) {
        int base = randomValue(rnd.next(0, 2));
        for (int i = 0; i < n; ++i) {
            int bit = rnd.next(0, 23);
            a[i] = min(MAX_VALUE, base ^ (1 << bit));
        }
    } else {
        int valueMode = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) a[i] = randomValue(valueMode);
    }

    int q = mode == 4 ? rnd.next(25, 80) : rnd.next(1, 25);
    vector<vector<int>> queries;
    queries.reserve(q);

    for (int i = 0; i < q; ++i) {
        int type;
        if (i == 0) {
            type = rnd.next(1, 2);
        } else if (mode == 3) {
            type = rnd.next(1, 3);
        } else {
            type = rnd.next(0, 9) < 7 ? rnd.next(1, 2) : 3;
        }

        int valueMode = (i % 5 == 0 ? 0 : rnd.next(0, 4));
        int x = randomValue(valueMode);
        if (type == 3) {
            int p = rnd.next(1, n);
            if (mode == 1 && rnd.next(0, 2) == 0) x = a[rnd.next(0, n - 1)];
            a[p - 1] = x;
            queries.push_back({type, p, x});
        } else {
            auto [l, r] = randomRange(n, rnd.next(0, 3));
            queries.push_back({type, l, r, x});
        }
    }

    println(n);
    println(a);
    println(q);
    for (const vector<int>& query : queries) {
        if (query[0] == 3) {
            println(query[0], query[1], query[2]);
        } else {
            println(query[0], query[1], query[2], query[3]);
        }
    }

    return 0;
}
