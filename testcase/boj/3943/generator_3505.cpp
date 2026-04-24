#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int maxN = 100000;
    // Number of test cases small for hand-checkability
    int T = rnd.next(1, 10);
    vector<int> ns(T);
    // Generate default random values with various distributions
    for (int i = 0; i < T; ++i) {
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            // small values
            ns[i] = rnd.next(1, 100);
        } else if (mode == 1) {
            // near maximum
            ns[i] = rnd.next(max(1, maxN - 999), maxN);
        } else if (mode == 2) {
            // middle range
            ns[i] = rnd.next(101, maxN - 1000);
        } else {
            // biased towards large values
            ns[i] = rnd.wnext(maxN, 2) + 1;
        }
    }
    // Ensure some edge cases are present
    if (T == 1) {
        // Single test: pick one of the classic seeds
        int pick = rnd.next(0, 2);
        if (pick == 0) ns[0] = 1;
        else if (pick == 1) ns[0] = 27;
        else ns[0] = maxN;
    } else {
        // Guarantee at least n=1 and n=maxN
        ns[0] = 1;
        ns[1] = maxN;
        // Also include the notorious 27 if possible
        if (T >= 3) ns[2] = 27;
    }
    // Shuffle order of test cases
    shuffle(ns.begin(), ns.end());
    // Output
    println(T);
    for (int x : ns) {
        println(x);
    }
    return 0;
}
