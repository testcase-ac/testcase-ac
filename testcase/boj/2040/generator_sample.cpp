#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int VALUE_LIMIT = 10000;

vector<int> makeRow(int n) {
    int mode = rnd.next(8);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(-3, 3);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int x = rnd.next(1, 20);
        int y = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? x : -y);
    } else if (mode == 2) {
        int nonZero = rnd.next(1, min(n, 4));
        fill(a.begin(), a.end(), 0);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < nonZero; ++i) a[pos[i]] = rnd.next(-50, 50);
    } else if (mode == 3) {
        int cur = rnd.next(-10, 10);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-5, 5);
            a[i] = max(-100, min(100, cur));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a[i] = rnd.any(vector<int>{-VALUE_LIMIT, -100, -1, 0, 1, 100, VALUE_LIMIT});
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(-20, 20);
        if (n >= 2) {
            a[0] = rnd.next(-VALUE_LIMIT, VALUE_LIMIT);
            a[n - 1] = rnd.next(-VALUE_LIMIT, VALUE_LIMIT);
        }
    } else if (mode == 6) {
        int block = rnd.next(1, min(n, 5));
        for (int i = 0; i < n; ++i) {
            int sign = ((i / block) % 2 == 0 ? 1 : -1);
            a[i] = sign * rnd.next(0, 30);
        }
    } else {
        int lo = rnd.next(-100, 0);
        int hi = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 5);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 12);
    } else if (sizeMode == 3) {
        n = rnd.next(13, 25);
    } else {
        n = rnd.next(26, 60);
    }

    println(n);
    for (int row = 0; row < 3; ++row) println(makeRow(n));

    return 0;
}
