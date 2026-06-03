#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 10) {
        n = 2;
    } else {
        n = rnd.next(3, 12);
    }

    vector<int> a(n);
    if (n == 2) {
        a = {1, 1};
    } else {
        int mode = rnd.next(5);
        if (mode == 0) {
            int value = rnd.next(1, 20);
            fill(a.begin(), a.end(), value);
        } else if (mode == 1) {
            int start = rnd.next(1, 20);
            int step = rnd.next(1, 8);
            for (int i = 0; i < n; ++i) {
                a[i] = start + i * step;
            }
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(1, 30);
            }
        } else if (mode == 3) {
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(1, 5);
            }
            a[rnd.next(n)] = rnd.next(40000, 50000);
        } else {
            int high = rnd.next(49980, 50000);
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(max(1, high - 30), high);
            }
        }

        shuffle(a.begin(), a.end());
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        vector<int> row(n);
        for (int j = 0; j < n; ++j) {
            row[j] = (i == j ? 0 : a[i] + a[j]);
        }
        println(row);
    }

    return 0;
}
