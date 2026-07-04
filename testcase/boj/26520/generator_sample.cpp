#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomValue(int mode) {
    if (mode == 0) {
        return rnd.next(-5, 5);
    }
    if (mode == 1) {
        return rnd.any(vector<int>{-100000, -99999, -1, 0, 1, 99999, 100000});
    }
    return rnd.next(-100000, 100000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 2) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(9, 40);
    }

    int valueMode = rnd.next(0, 4);
    vector<int> a(n + 1);
    if (valueMode == 0) {
        fill(a.begin(), a.end(), randomValue(0));
    } else if (valueMode == 1) {
        int start = rnd.next(-20, 20);
        int step = rnd.next(-8, 8);
        for (int i = 0; i <= n; ++i) {
            a[i] = max(-100000, min(100000, start + step * i));
        }
    } else if (valueMode == 2) {
        for (int i = 0; i <= n; ++i) {
            a[i] = (i % 2 == 0 ? randomValue(1) : randomValue(0));
        }
    } else {
        int mode = rnd.next(0, 2);
        for (int i = 0; i <= n; ++i) {
            a[i] = randomValue(mode);
        }
    }

    int m = rnd.next(1, min(80, max(3, n * 4)));
    int firstType2 = rnd.next(0, m - 1);

    println(n);
    println(a);
    println(m);

    for (int q = 0; q < m; ++q) {
        bool forceQuery = (q == firstType2);
        bool useQuery = forceQuery || rnd.next(0, 99) < 45;
        if (useQuery) {
            int left = rnd.next(0, n);
            int right;
            int intervalMode = rnd.next(0, 4);
            if (intervalMode == 0) {
                right = left;
            } else if (intervalMode == 1) {
                right = n;
            } else if (intervalMode == 2) {
                left = 0;
                right = rnd.next(0, n);
            } else {
                right = rnd.next(left, n);
            }
            println(2, left, right);
        } else {
            int index = rnd.next(0, n);
            int value = randomValue(rnd.next(0, 2));
            println(1, index, value);
        }
    }

    return 0;
}
