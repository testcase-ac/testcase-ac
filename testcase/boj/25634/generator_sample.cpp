#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int brightness(int mode) {
    if (mode == 0) return rnd.next(1, 9);
    if (mode == 1) return rnd.next(1, 100);
    if (mode == 2) return rnd.next(4900, 5000);
    if (rnd.next(5) == 0) return rnd.any(vector<int>{1, 2, 4999, 5000});
    return rnd.next(1, 5000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(2, 25);
    }

    int valueMode = rnd.next(4);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = brightness(valueMode);
    }

    vector<int> b(n);
    if (mode == 0) {
        b[0] = rnd.next(0, 1);
    } else if (mode == 1) {
        fill(b.begin(), b.end(), 0);
    } else if (mode == 2) {
        fill(b.begin(), b.end(), 1);
    } else if (mode == 3) {
        int start = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) b[i] = (i + start) % 2;
    } else if (mode == 4) {
        int current = rnd.next(0, 1);
        for (int i = 0; i < n;) {
            int len = rnd.next(1, min(6, n - i));
            for (int j = 0; j < len; ++j) b[i + j] = current;
            i += len;
            current ^= 1;
        }
    } else {
        int ones = rnd.next(0, n);
        fill(b.begin(), b.begin() + ones, 1);
        shuffle(b.begin(), b.end());
    }

    println(n);
    println(a);
    println(b);
    return 0;
}
