#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(3, 8);
    vector<int> ns;
    ns.reserve(T);
    // Special candidate values to expose edge cases
    vector<int> specials = {1, 10, 50, 99, 100, 11111111, 12345678, 199999999, 200000000};
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 3);
        int n;
        switch (type) {
            case 0:
                // Small n to catch trivial loops
                n = rnd.next(1, 100);
                break;
            case 1:
                // Medium n for typical cases
                n = rnd.next(101, 1000000);
                break;
            case 2:
                // Large n, biased towards upper bound
                n = rnd.wnext(200000000, 3) + 1;  // [1,200e6], bias high
                break;
            case 3:
            default:
                // Pick a special edge-case value
                n = rnd.any(specials);
                break;
        }
        ns.push_back(n);
    }
    // Shuffle to mix case ordering
    shuffle(ns.begin(), ns.end());
    // Output each n on its own line
    for (int n : ns) {
        println(n);
    }
    return 0;
}
