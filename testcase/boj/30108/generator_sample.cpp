#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 25);

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            parent[i] = 1;
        } else if (mode == 1) {
            parent[i] = i - 1;
        } else if (mode == 2) {
            parent[i] = max(1, i / 2);
        } else if (mode == 3) {
            int spine = max(2, min(n, rnd.next(2, 8)));
            parent[i] = (i <= spine ? i - 1 : rnd.next(1, spine));
        } else {
            parent[i] = rnd.next(1, i - 1);
        }
    }

    vector<long long> a(n + 1);
    long long rootValue = rnd.next(1, 1000000000);
    a[1] = rootValue;

    int valueMode = rnd.next(4);
    for (int i = 2; i <= n; ++i) {
        long long limit = a[parent[i]];
        if (valueMode == 0) {
            a[i] = limit;
        } else if (valueMode == 1) {
            a[i] = rnd.next(1LL, limit);
        } else if (valueMode == 2) {
            long long drop = rnd.next(0LL, min(20LL, limit - 1));
            a[i] = limit - drop;
        } else {
            long long cap = min(limit, 1000LL);
            a[i] = rnd.next(1LL, cap);
        }
    }

    println(n);
    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            printf(" ");
        }
        printf("%d", parent[i]);
    }
    printf("\n");

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            printf(" ");
        }
        printf("%lld", a[i]);
    }
    printf("\n");

    return 0;
}
