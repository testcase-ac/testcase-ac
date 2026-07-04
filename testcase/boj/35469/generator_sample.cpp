#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomValue(int mode, int i, int j) {
    if (mode == 0) {
        return rnd.next(-5, 5);
    }
    if (mode == 1) {
        return rnd.next(-1000, 1000);
    }
    if (mode == 2) {
        int base = rnd.next(-20, 20);
        return base + (i % 3) - (j % 3);
    }
    if (mode == 3) {
        return (rnd.next(2) == 0 ? -1000 : 1000);
    }
    return (i - j) * rnd.next(-3, 3);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        k = n;
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        k = n - 1;
    } else if (mode == 4) {
        n = rnd.next(4, 14);
        k = rnd.next(2, min(n, 4));
    } else if (mode == 5) {
        n = rnd.next(8, 18);
        k = rnd.next(2, n);
    } else if (mode == 6) {
        k = rnd.next(2, 5);
        n = k * rnd.next(2, 4);
    } else {
        n = rnd.next(2, 15);
        k = rnd.next(1, n);
    }

    int valueMode = rnd.next(5);
    println(n, k);
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            row.push_back(randomValue(valueMode, i, j));
        }
        println(row);
    }

    return 0;
}
