#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int boundedValue(int mode) {
    if (mode == 0) {
        return rnd.next(1, 5);
    }
    if (mode == 1 && rnd.next(0, 4) == 0) {
        return 100;
    }
    return rnd.next(1, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 4);
    int n = 1, m = 1, q = 1;
    if (shape == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
        q = rnd.next(1, 4);
    } else if (shape == 1) {
        n = rnd.next(4, 8);
        m = rnd.next(2, 6);
        q = rnd.next(2, 6);
    } else if (shape == 2) {
        n = rnd.next(8, 14);
        m = rnd.next(5, 12);
        q = rnd.next(3, 8);
    } else {
        n = rnd.next(2, 10);
        m = rnd.next(8, 16);
        q = rnd.next(1, 5);
    }

    int valueMode = rnd.next(0, 2);
    println(n, m, q);

    for (int i = 0; i < m; ++i) {
        int c;
        if (shape == 0) {
            c = rnd.next(1, n);
        } else if (shape == 2) {
            c = rnd.wnext(n, 2) + 1;
        } else {
            c = rnd.wnext(n, -2) + 1;
        }

        vector<int> indexes(n);
        iota(indexes.begin(), indexes.end(), 1);
        shuffle(indexes.begin(), indexes.end());
        indexes.resize(c);

        vector<int> weights(c);
        for (int& w : weights) {
            w = boundedValue(valueMode);
        }
        int bias = boundedValue(valueMode);

        printf("%d", c);
        for (int p : indexes) {
            printf(" %d", p);
        }
        for (int w : weights) {
            printf(" %d", w);
        }
        printf(" %d\n", bias);
    }

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", boundedValue(valueMode));
    }
    printf(" %d\n", boundedValue(valueMode));

    for (int row = 0; row < q; ++row) {
        vector<int> a(n);
        int queryMode = rnd.next(0, 3);
        int shared = boundedValue(valueMode);
        for (int i = 0; i < n; ++i) {
            if (queryMode == 0) {
                a[i] = shared;
            } else if (queryMode == 1) {
                a[i] = (i % 2 == 0 ? 1 : 100);
            } else {
                a[i] = boundedValue(valueMode);
            }
        }
        println(a);
    }

    return 0;
}
