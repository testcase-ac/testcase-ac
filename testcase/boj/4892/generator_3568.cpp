#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int T = rnd.next(1, 10);
    vector<int> ns;
    ns.reserve(T + 1);
    int max_k = 19; // so that (1<<k)-1 < 1e6

    for (int i = 0; i < T; i++) {
        int c = rnd.next(0, 3);
        int n0;
        if (c == 0) {
            // small numbers
            n0 = rnd.next(1, 100);
        } else if (c == 1) {
            // near the upper bound
            n0 = rnd.next(999900, 999999);
        } else if (c == 2) {
            // special of form 2^k - 1
            int k = rnd.next(1, max_k);
            n0 = (1 << k) - 1;
        } else {
            // skewed distribution: sometimes low, sometimes high
            if (rnd.next(0, 1) == 0)
                n0 = rnd.wnext(1000000, -2) + 1;
            else
                n0 = rnd.wnext(1000000, 2) + 1;
        }
        // clamp into valid range 1..999999
        if (n0 <= 0) n0 = 1;
        if (n0 >= 1000000) n0 = 999999;
        ns.push_back(n0);
    }

    // shuffle the order of test cases
    shuffle(ns.begin(), ns.end());
    // output each test case on its own line, then a terminating 0
    for (int x : ns) println(x);
    println(0);
    return 0;
}
