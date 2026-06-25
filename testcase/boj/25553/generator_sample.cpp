#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        if (n % 2 == 1) ++n;
    } else {
        n = rnd.next(5, 15);
    }

    int q = rnd.next(1, 12);
    int k;
    if (mode == 2) {
        k = 1;
    } else if (mode == 3) {
        k = n;
    } else if (mode == 4) {
        k = rnd.next(1, n);
        if (k % 2 == 0 && k < n) ++k;
    } else {
        k = rnd.next(1, n);
    }

    vector<int> a(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(-5, 5);
    } else if (mode == 1) {
        int oddValue = rnd.next(-20, 20);
        int evenValue = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? oddValue : evenValue);
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) a[i] = rnd.any(vector<int>{-100000, -1, 0, 1, 100000});
    } else {
        int lo = rnd.next(-30, 0);
        int hi = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    }

    vector<pair<int, int>> operations;
    bool hasQuery = false;
    for (int i = 0; i < q; ++i) {
        int t;
        if (i == q - 1 && !hasQuery) {
            t = 3;
        } else {
            t = rnd.next(1, 3);
        }

        if (t == 3) {
            operations.push_back({3, 0});
            hasQuery = true;
        } else {
            int x;
            if (mode == 5) {
                x = rnd.any(vector<int>{-100000, -10, -1, 0, 1, 10, 100000});
            } else {
                x = rnd.next(-25, 25);
            }
            operations.push_back({t, x});
        }
    }

    println(n, q, k);
    println(a);
    for (auto [t, x] : operations) {
        if (t == 3) {
            println(3);
        } else {
            println(t, x);
        }
    }

    return 0;
}
