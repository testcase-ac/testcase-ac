#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_V = 1000000000LL;

vector<long long> makeNondecreasing(int n, bool duplicateHeavy) {
    vector<long long> a(n);
    long long current = rnd.next(1, duplicateHeavy ? 5 : 30);
    for (int i = 0; i < n; ++i) {
        if (i > 0 && (!duplicateHeavy || rnd.next(0, 2) == 0)) {
            current += rnd.next(0, duplicateHeavy ? 3 : 20);
        }
        a[i] = min(current, MAX_V);
    }
    return a;
}

void printCase(const vector<long long>& a) {
    println((int)a.size());
    println(a);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<long long> a;

    if (mode == 0 || n == 1) {
        a = makeNondecreasing(n, rnd.next(0, 1));
    } else if (mode == 1) {
        a = makeNondecreasing(n, false);
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        reverse(a.begin() + l, a.begin() + r + 1);
    } else if (mode == 2) {
        a = makeNondecreasing(n, true);
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        reverse(a.begin() + l, a.begin() + r + 1);
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        a = makeNondecreasing(n, false);
        swap(a[1], a[2]);
        swap(a[n - 3], a[n - 2]);
    } else if (mode == 4) {
        n = rnd.next(3, 12);
        a = makeNondecreasing(n, true);
        a.front() = MAX_V;
        a.back() = rnd.next(1, 20);
    } else {
        n = rnd.next(4, 20);
        a.resize(n);
        long long lo = rnd.next(1, 50);
        long long hi = rnd.next(lo, lo + 80);
        for (long long& x : a) {
            x = rnd.next(lo, hi);
        }
    }

    printCase(a);
    return 0;
}
