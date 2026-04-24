#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small and hand-checkable
    int T = rnd.next(3, 10);
    println(T);

    vector<int> ns;
    ns.reserve(T);

    // Helper to pick a random even number in [lo, hi]
    auto pick_even = [&](int lo, int hi, int t)->int {
        if (lo % 2) lo++;
        if (hi % 2) hi--;
        int cnt = (hi - lo) / 2 + 1;  // number of evens
        int idx;
        if (t == 0) {
            idx = rnd.next(cnt);        // uniform [0, cnt-1]
        } else {
            idx = rnd.wnext(cnt, t);    // weighted
        }
        return lo + idx * 2;
    };

    for (int i = 0; i < T; i++) {
        // Three magnitude categories: small, medium, large
        int cat = rnd.next(0, 2);
        int lo, hi;
        if (cat == 0) {
            lo = 4; hi = 50;
        } else if (cat == 1) {
            lo = 52; hi = 2000;
        } else {
            lo = 2002; hi = 10000;
        }
        // Random weight parameter for even selection
        int t = rnd.next(-2, 2);
        int n = pick_even(lo, hi, t);
        ns.push_back(n);
    }

    // Shuffle the test cases to avoid any order bias
    shuffle(ns.begin(), ns.end());

    // Output each test case on its own line
    for (int x : ns) {
        println(x);
    }

    return 0;
}
