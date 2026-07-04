#include "testlib.h"

#include <cstdio>
#include <vector>

using namespace std;

vector<int> makeParents(int n, int mode) {
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            p[i] = i - 1;
        } else if (mode == 1) {
            p[i] = 1;
        } else if (mode == 2) {
            p[i] = max(1, i / 2);
        } else {
            p[i] = rnd.next(1, i - 1);
        }
    }
    return p;
}

vector<long long> makeValues(int n, int mode) {
    vector<long long> values(n + 1);
    int base = rnd.next(1, 20);
    for (int i = 1; i <= n; ++i) {
        if (mode == 0) {
            values[i] = base + i;
        } else if (mode == 1) {
            values[i] = base + n - i;
        } else if (mode == 2) {
            values[i] = base + (i % rnd.next(2, 5));
        } else if (mode == 3) {
            values[i] = base + (i % 2 == 0 ? rnd.next(0, 5) : rnd.next(6, 12));
        } else {
            values[i] = rnd.next(1, 100);
        }
    }

    if (rnd.next(4) == 0) {
        values[rnd.next(1, n)] = 1000000000LL;
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(10) == 0) {
        n = 1;
    } else {
        n = rnd.next(2, 18);
    }

    vector<int> parents = makeParents(n, rnd.next(0, 3));
    vector<long long> values = makeValues(n, rnd.next(0, 4));

    println(n);
    if (n == 1) {
        printf("\n");
    } else {
        for (int i = 2; i <= n; ++i) {
            if (i > 2) {
                printf(" ");
            }
            printf("%d", parents[i]);
        }
        printf("\n");
    }
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            printf(" ");
        }
        printf("%lld", values[i]);
    }
    printf("\n");

    return 0;
}
