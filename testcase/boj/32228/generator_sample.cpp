#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        m = rnd.next(2, 12);
        n = rnd.next(3, 12);
    } else if (mode == 1) {
        vector<int> moduli = {8, 9, 10, 12, 15, 16, 18, 20, 24, 30, 36};
        m = rnd.any(moduli);
        n = rnd.next(3, 18);
    } else if (mode == 2) {
        vector<int> moduli = {11, 13, 17, 19, 23, 29, 31, 37, 101};
        m = rnd.any(moduli);
        n = rnd.next(3, 24);
    } else if (mode == 3) {
        m = rnd.next(900000000, 1000000000);
        n = rnd.next(3, 12);
    } else if (mode == 4) {
        m = rnd.next(2, 2000);
        n = rnd.next(3, 30);
    } else {
        vector<int> moduli = {1000000000, 999999937, 999999929, 999999893};
        m = rnd.any(moduli);
        n = rnd.next(3, 16);
    }

    vector<int> units;
    for (int x = 1; x < m && static_cast<int>(units.size()) < 5000; ++x) {
        if (gcd(x, m) == 1) units.push_back(x);
    }

    vector<int> a;
    a.reserve(n);
    if (!units.empty() && rnd.next(0, 2) != 0) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(units));
    } else {
        for (int i = 0; i < n; ++i) {
            int x;
            do {
                x = rnd.next(1, m - 1);
            } while (gcd(x, m) != 1);
            a.push_back(x);
        }
    }

    if (rnd.next(0, 3) == 0) {
        int repeated = rnd.any(a);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) a[i] = repeated;
        }
    }

    if (rnd.next(0, 2) == 0) reverse(a.begin(), a.end());

    println(n, m);
    println(a);

    return 0;
}
