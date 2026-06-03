#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(8, 18);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> values = {1, 2, 3, 5, 1000000000};
    for (int i = 0; i < 5; ++i) {
        values.push_back(rnd.next(1, 20));
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 2) {
            a[i] = (i % 2 == 0 ? values.front() : values.back());
        } else if (mode == 3) {
            a[i] = values[min<int>(i % values.size(), values.size() - 1)];
        } else if (mode == 4) {
            a[i] = values[rnd.wnext((int)values.size(), -2)];
        } else {
            a[i] = rnd.any(values);
        }
    }

    int q = rnd.next(1, 45);
    int forcedTypeOne = rnd.next(0, q - 1);

    println(n);
    println(a);
    println(q);

    for (int i = 0; i < q; ++i) {
        bool ask = (i == forcedTypeOne) || rnd.next(0, 99) < 60;
        int l, r;
        if (mode == 0 && rnd.next(0, 99) < 45) {
            l = r = rnd.next(1, n);
        } else if (mode == 1 && rnd.next(0, 99) < 45) {
            l = 1;
            r = n;
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }

        if (ask) {
            int k;
            if (rnd.next(0, 99) < 80) {
                k = rnd.any(values);
            } else {
                k = rnd.next(1, 1000000000);
            }
            println(1, l, r, k);
        } else {
            println(2, l, r);
        }
    }

    return 0;
}
