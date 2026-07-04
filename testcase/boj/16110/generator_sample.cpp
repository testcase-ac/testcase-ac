#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeCounts(int n, int count, int mode) {
    vector<int> values(count, 1);
    int remaining = n * n - count;

    if (mode == 0) {
        for (int i = 0; i < count && remaining > 0; ++i) {
            int add = min(n - 1, remaining);
            values[i] += add;
            remaining -= add;
        }
    } else if (mode == 1) {
        for (int i = count - 1; i >= 0 && remaining > 0; --i) {
            int add = min(n - 1, remaining);
            values[i] += add;
            remaining -= add;
        }
    } else {
        while (remaining > 0) {
            vector<int> indices;
            for (int i = 0; i < count; ++i) {
                if (values[i] < n) indices.push_back(i);
            }

            int at = rnd.any(indices);
            int add = rnd.next(1, min(n - values[at], remaining));
            values[at] += add;
            remaining -= add;
        }
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    int k;

    if (mode == 0) {
        n = 1;
        m = k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = k = n;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = k = n * n;
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        m = rnd.next(n, min(n * n, n + 6));
        k = rnd.next(max(n, n * n - 6), n * n);
    } else if (mode == 4) {
        n = rnd.next(4, 18);
        m = rnd.next(max(n, n * n / 3), min(n * n, 2 * n * n / 3));
        k = rnd.next(max(n, n * n / 3), min(n * n, 2 * n * n / 3));
    } else if (mode == 5) {
        n = rnd.next(10, 25);
        m = rnd.any(vector<int>{n, n + 1, n * n / 2, n * n});
        k = rnd.next(n, n * n);
    } else {
        n = rnd.next(2, 20);
        m = rnd.next(n, n * n);
        k = rnd.next(n, n * n);
    }

    vector<int> kangaroos = makeCounts(n, m, rnd.next(0, 2));
    vector<int> kiwis = makeCounts(n, k, rnd.next(0, 2));

    println(n, m, k);
    println(kangaroos);
    println(kiwis);
    return 0;
}
