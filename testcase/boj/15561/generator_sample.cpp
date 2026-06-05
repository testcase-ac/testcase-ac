#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int smallValue(int mode) {
    if (mode == 0) return rnd.next(-3, 3);
    if (mode == 1) return rnd.any(vector<int>{-100, -20, -1, 0, 1, 20, 100});
    return rnd.next(-100, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(8, 20);
    }

    int q = rnd.next(1, 25);
    int u = rnd.next(-5, 5);
    int v = rnd.next(-5, 5);

    if (mode == 0 && rnd.next(0, 1) == 0) u = 0;
    if (mode == 1) v = rnd.any(vector<int>{-5, 0, 5});

    vector<int> k(n);
    int valueMode = rnd.next(0, 2);
    for (int i = 0; i < n; ++i) {
        if (mode == 2) {
            k[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 100);
        } else {
            k[i] = smallValue(valueMode);
        }
    }

    println(n, q, u, v);
    println(k);

    for (int i = 0; i < q; ++i) {
        bool forceRange = (i == 0 || mode == 0);
        int c = forceRange ? 0 : rnd.next(0, 1);

        if (c == 0) {
            int a = rnd.next(1, n);
            int b = rnd.next(a, n);

            if (rnd.next(0, 4) == 0) {
                a = 1;
                b = n;
            } else if (rnd.next(0, 4) == 0) {
                b = a;
            }

            println(0, a, b);
        } else {
            int a = rnd.next(1, n);
            int b = smallValue(rnd.next(0, 2));
            println(1, a, b);
        }
    }

    return 0;
}
