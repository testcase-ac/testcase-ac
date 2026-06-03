#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    vector<int> a;
    vector<int> b;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
        a.assign(n, 0);
        b.assign(m, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
        a.resize(n);
        b.resize(m);
        for (int& x : a) x = rnd.next(0, 2);
        for (int& x : b) x = rnd.next(0, 1);
    } else if (mode == 2) {
        n = rnd.next(1, 5);
        m = rnd.next(4, 12);
        a.resize(n);
        b.resize(m);
        for (int& x : a) x = rnd.next(1, 10);
        for (int& x : b) x = rnd.next(8, 10);
    } else if (mode == 3) {
        n = rnd.next(8, 12);
        m = rnd.next(8, 12);
        a.resize(n);
        b.resize(m);
        for (int& x : a) x = rnd.next(0, 10);
        for (int& x : b) x = rnd.any(vector<int>{0, 1, 2, 10});
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        a.resize(n);
        b.resize(m);
        int maxA = rnd.next(0, 10);
        int maxB = rnd.next(0, 10);
        for (int& x : a) x = rnd.next(0, maxA);
        for (int& x : b) x = rnd.next(0, maxB);
    } else {
        n = 12;
        m = 12;
        a.resize(n);
        b.resize(m);
        for (int i = 0; i < n; ++i) a[i] = (i % 3 == 0 ? 0 : rnd.next(7, 10));
        for (int i = 0; i < m; ++i) b[i] = (i % 4 == 0 ? 0 : rnd.next(2, 10));
        shuffle(a.begin(), a.end());
        shuffle(b.begin(), b.end());
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
