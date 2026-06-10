#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomMass(int mode) {
    if (mode == 0) return rnd.next(1, 30);
    if (mode == 1) return rnd.next(1, 1000);
    if (mode == 2) return rnd.next(900000000, 1000000000);
    if (rnd.next(0, 3) == 0) return rnd.any(vector<long long>{1, 2, 3, 7, 15, 31, 63, 127});
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    int l;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 80);
        l = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.next(n, 3 * n);
        l = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(8, 20);
        k = rnd.next(1, n);
        l = rnd.next(max(1, n / 2), n);
    } else if (mode == 3) {
        n = rnd.next(15, 45);
        k = rnd.next(15, 80);
        l = rnd.next(1, min(n, 6));
    } else if (mode == 4) {
        n = rnd.next(30, 90);
        k = rnd.next(1, 120);
        l = rnd.next(1, n);
    } else {
        n = rnd.next(2, 25);
        k = rnd.next(1, 60);
        l = rnd.next(1, n);
    }

    vector<long long> masses(n);
    int massMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) masses[i] = randomMass(massMode);

    if (mode == 1) {
        sort(masses.begin(), masses.end());
        if (rnd.next(0, 1)) reverse(masses.begin(), masses.end());
    }

    vector<int> timings(k);
    if (mode == 0) {
        fill(timings.begin(), timings.end(), 1);
    } else if (mode == 1) {
        int focus = rnd.next(1, n);
        for (int i = 0; i < k; ++i) {
            timings[i] = rnd.next(0, 2) == 0 ? focus : rnd.next(1, n);
        }
    } else if (mode == 2) {
        for (int i = 0; i < k; ++i) timings[i] = rnd.next(1, max(1, n / 3));
    } else if (mode == 3) {
        for (int i = 0; i < k; ++i) timings[i] = rnd.next(1, n);
        sort(timings.begin(), timings.end());
    } else {
        for (int i = 0; i < k; ++i) timings[i] = rnd.next(1, n);
    }

    println(n, k, l);
    println(masses);
    println(timings);

    return 0;
}
