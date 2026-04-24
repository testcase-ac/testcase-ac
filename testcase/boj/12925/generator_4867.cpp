#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 2 and 10
    int T = rnd.next(2, 10);

    // Always include the minimum and maximum edge cases
    vector<int> ns;
    ns.push_back(2);
    ns.push_back(2000000000);

    // Fill the rest with diverse values across different ranges
    int rem = T - 2;
    for (int i = 0; i < rem; i++) {
        int cat = rnd.next(0, 3);
        int lo, hi;
        if (cat == 0) {
            // small n
            lo = 3; hi = 10;
        } else if (cat == 1) {
            // moderate n
            lo = 11; hi = 1000;
        } else if (cat == 2) {
            // larger but not huge
            lo = 1001; hi = 100000000;
        } else {
            // near the upper limit
            lo = 100000001; hi = 2000000000;
        }
        ns.push_back(rnd.next(lo, hi));
    }

    // Shuffle so edge cases aren't always first
    shuffle(ns.begin(), ns.end());

    // Output
    println(T);
    for (int x : ns) {
        println(x);
    }
    return 0;
}
