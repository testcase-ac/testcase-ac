#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeScores(int n, bool useExtremes) {
    vector<int> values;
    if (useExtremes && n >= 2) {
        values.push_back(0);
        values.push_back(1000000000);
        for (int i = 1; (int)values.size() < n; ++i) {
            values.push_back(i);
        }
    } else {
        int base = rnd.next(0, 1000000000 - 5 * n);
        for (int i = 0; i < n; ++i) {
            values.push_back(base + 5 * i + rnd.next(0, 3));
        }
    }
    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else {
        n = rnd.next(6, 24);
    }

    int m = rnd.next(1, n - 1);
    int k = rnd.next(1, n - m);

    if (mode == 2) {
        m = rnd.next(1, n / 2);
        k = n - m;
    } else if (mode == 3) {
        k = rnd.next(1, n / 2);
        m = n - k;
    }

    vector<int> a = makeScores(n, mode == 0 || rnd.next(0, 4) == 0);
    vector<int> b(n);

    if (mode == 1) {
        b = a;
        sort(b.begin(), b.end());
    } else if (mode == 2) {
        b = a;
        sort(b.begin(), b.end(), greater<int>());
    } else {
        b = makeScores(n, mode == 0 || rnd.next(0, 4) == 0);
    }

    if (mode == 3) {
        sort(a.begin(), a.end(), greater<int>());
        sort(b.begin(), b.end());
    } else if (mode == 4) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int pivot = rnd.next(1, n - 1);
        rotate(b.begin(), b.begin() + pivot, b.end());
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    println(n, m, k);
    for (int idx : order) {
        println(a[idx], b[idx]);
    }

    return 0;
}
