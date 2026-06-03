#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 10);
    int k = rnd.next(1, 18);
    int q = rnd.next(1, 24);

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        k = rnd.next(12, 24);
    } else if (mode == 2) {
        m = rnd.next(1, 3);
        q = rnd.next(16, 30);
    }

    vector<int> limits(m);
    int limitMode = rnd.next(0, 3);
    for (int& limit : limits) {
        if (limitMode == 0) {
            limit = rnd.next(1, min(200000, max(1, k / 2 + 2)));
        } else if (limitMode == 1) {
            limit = rnd.next(1, min(200000, k + 2));
        } else {
            limit = rnd.next(1, min(200000, 2 * k + 5));
        }
    }

    vector<int> grow(k);
    for (int day = 0; day < k; ++day) {
        if (mode == 1 && rnd.next(0, 99) < 65) {
            grow[day] = 1;
        } else if (mode == 3 && n >= 2 && rnd.next(0, 99) < 70) {
            grow[day] = rnd.next(1, 2);
        } else {
            grow[day] = rnd.next(1, n);
        }
    }

    println(n, m, k, q);
    println(limits);
    println(grow);

    for (int query = 0; query < q; ++query) {
        int i = rnd.next(1, n);
        int j = rnd.next(1, n);

        if (mode == 4) {
            j = i;
        } else if (mode == 5 && n >= 2) {
            i = rnd.next(1, min(n, 3));
            j = rnd.next(1, min(n, 3));
        } else if (rnd.next(0, 99) < 20) {
            j = i;
        }

        int ride = rnd.next(1, m);
        println(i, j, ride);
    }

    return 0;
}
