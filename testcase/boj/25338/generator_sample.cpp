#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int bodyAt(int a, int b, int c, int d, int v) {
    long long x = v - b;
    long long curved = 1LL * a * x * x + c;
    return (int)max<long long>(d, curved);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a, b, c, d;

    if (mode == 0) {
        a = rnd.next(-10, -1);
        b = rnd.next(1, 20);
        d = rnd.next(1, 20);
        c = rnd.next(d + 1, min(10000, d + 60));
    } else if (mode == 1) {
        a = rnd.any(vector<int>{-10, -5, -2, -1});
        b = rnd.next(1, 100);
        c = rnd.next(2, 80);
        d = rnd.next(1, c - 1);
    } else if (mode == 2) {
        a = rnd.next(-10, -1);
        b = rnd.next(9900, 10000);
        d = rnd.next(1, 9999);
        c = rnd.next(d + 1, 10000);
    } else if (mode == 3) {
        a = -1;
        b = rnd.next(1, 10000);
        c = 10000;
        d = rnd.next(9990, 9999);
    } else if (mode == 4) {
        a = rnd.next(-10, -1);
        b = 1;
        c = rnd.next(9000, 10000);
        d = rnd.next(1, c - 1);
    } else {
        a = rnd.next(-3, -1);
        b = rnd.next(1, 40);
        d = rnd.next(1, 40);
        c = rnd.next(d + 1, min(10000, d + 200));
    }

    int n = rnd.next(1, 40);
    vector<pair<int, int>> pants;

    for (int i = 0; i < n; ++i) {
        int kind = rnd.next(0, 5);
        int v;
        if (kind == 0) {
            v = b;
        } else if (kind == 1) {
            v = rnd.next(b, min(10000, b + 12));
        } else if (kind == 2) {
            v = rnd.next(max(b, 9990), 10000);
        } else {
            v = rnd.next(b, 10000);
        }

        int exact = bodyAt(a, b, c, d, v);
        int u;
        if (kind <= 1 && exact > d) {
            u = exact;
        } else if (kind == 2) {
            u = c;
        } else if (kind == 3 && c > d + 1) {
            int delta = rnd.any(vector<int>{-2, -1, 1, 2});
            u = min(c, max(d + 1, exact + delta));
        } else {
            u = rnd.next(d + 1, c);
        }

        pants.emplace_back(u, v);
    }

    if (rnd.next(0, 1)) {
        shuffle(pants.begin(), pants.end());
    }

    println(a, b, c, d);
    println(n);
    for (auto [u, v] : pants) {
        println(u, v);
    }

    return 0;
}
