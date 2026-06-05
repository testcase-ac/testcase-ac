#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomInterval(int n) {
    int l = rnd.next(1, n - 1);
    int r = rnd.next(l + 1, n);
    return {l, r};
}

pair<int, int> intervalWithLength(int n, int len) {
    int l = rnd.next(1, n - len + 1);
    return {l, l + len - 1};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 6) {
        n = rnd.next(20, 100);
    } else {
        n = rnd.next(2, 12);
    }

    vector<long long> kChoices = {1, 2, 3, 4, 5, 10, 1000000000LL};
    long long k = rnd.next(0, 3) == 0 ? rnd.any(kChoices) : rnd.next(1LL, 1000000000LL);

    pair<int, int> a;
    pair<int, int> b;

    if (mode == 0) {
        a = randomInterval(n);
        b = a;
    } else if (mode == 1) {
        a = {1, n};
        b = randomInterval(n);
    } else if (mode == 2) {
        int len = rnd.next(2, n);
        a = intervalWithLength(n, len);
        int innerLen = rnd.next(2, len);
        int leftSlack = len - innerLen;
        int b1 = a.first + rnd.next(0, leftSlack);
        b = {b1, b1 + innerLen - 1};
    } else if (mode == 3 && n >= 4) {
        int cut = rnd.next(2, n - 2);
        a = {1, cut};
        b = {cut + 1, n};
    } else if (mode == 4 && n >= 3) {
        int mid = rnd.next(2, n - 1);
        a = {1, mid};
        b = {mid, n};
    } else if (mode == 5 && n >= 3) {
        int left = rnd.next(1, n - 2);
        int right = rnd.next(left + 2, n);
        int mid = rnd.next(left + 1, right - 1);
        a = {left, mid};
        b = {mid, right};
    } else {
        a = randomInterval(n);
        b = randomInterval(n);
    }

    if (rnd.next(0, 1)) {
        swap(a, b);
    }

    println(n, k);
    println(a.first, a.second);
    println(b.first, b.second);

    return 0;
}
