#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    vector<int> ns;

    if (T == 1) {
        // Single test: random n in [5,100]
        ns.push_back(rnd.next(5, 100));
    } else {
        // Ensure edge cases 5 and 100 are included
        ns = {5, 100};
        // Generate remaining with different skews
        for (int i = 2; i < T; ++i) {
            int mode = rnd.next(0, 2);
            int v;
            if (mode == 0) {
                // Uniform
                v = rnd.next(5, 100);
            } else if (mode == 1) {
                // Skew to small
                v = rnd.wnext(96, -1) + 5;
            } else {
                // Skew to large
                v = rnd.wnext(96, 1) + 5;
            }
            // Clip to [5,100]
            v = min(100, max(5, v));
            ns.push_back(v);
        }
        shuffle(ns.begin(), ns.end());
    }

    // Output
    println(T);
    for (int n : ns) {
        println(n);
    }

    return 0;
}
