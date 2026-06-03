#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 5) {
        n = rnd.next(25, 60);
    } else {
        n = rnd.next(5, 18);
    }

    vector<int> k(n), a(n), b(n);
    for (int i = 0; i < n; ++i) {
        array<int, 3> values{};

        if (mode == 0) {
            int base = rnd.any(vector<int>{0, 1, 999999, 1000000});
            int delta = rnd.next(0, 1);
            values = {base, min(1000000, base + delta), max(0, base - delta)};
        } else if (mode == 1) {
            int lo = rnd.next(0, 20);
            int mid = rnd.next(lo, min(1000000, lo + 20));
            int hi = rnd.next(mid, min(1000000, mid + 20));
            values = {lo, mid, hi};
        } else if (mode == 2) {
            int common = rnd.next(0, 1000000);
            int other = rnd.next(0, 1000000);
            if (rnd.next(0, 1) == 0) {
                values = {common, common, other};
            } else {
                values = {common, other, other};
            }
        } else if (mode == 3) {
            int span = rnd.next(1, 1000);
            int mid = rnd.next(span, 1000000 - span);
            values = {mid - span, mid, mid + span};
        } else if (mode == 4) {
            values = {rnd.next(0, 1000000), rnd.next(0, 1000000), rnd.next(0, 1000000)};
        } else {
            int bucket = rnd.next(0, 9) * 100000;
            values = {bucket, min(1000000, bucket + rnd.next(0, 50000)), rnd.next(0, 1000000)};
        }

        shuffle(values.begin(), values.end());
        k[i] = values[0];
        a[i] = values[1];
        b[i] = values[2];
    }

    println(n);
    println(k);
    println(a);
    println(b);

    return 0;
}
