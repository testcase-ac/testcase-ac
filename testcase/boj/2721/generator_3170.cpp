#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 1 and 10
    int T = rnd.next(1, 10);
    vector<int> ns;

    if (T == 1) {
        // Only one test case: pick a random n with mixed bias
        int t = rnd.next(0, 2);
        if (t == 0) {
            ns.push_back(rnd.next(1, 300));
        } else if (t == 1) {
            int a = rnd.next(1, 300), b = rnd.next(1, 300);
            ns.push_back(max(a, b));  // bias to larger values
        } else {
            int a = rnd.next(1, 300), b = rnd.next(1, 300);
            ns.push_back(min(a, b));  // bias to smaller values
        }
    } else {
        // Ensure edge cases are included
        ns.push_back(1);
        ns.push_back(300);
        // Fill remaining cases with uniform or biased picks
        for (int i = 2; i < T; ++i) {
            int t = rnd.next(0, 2);
            if (t == 0) {
                ns.push_back(rnd.next(1, 300));
            } else if (t == 1) {
                int a = rnd.next(1, 300), b = rnd.next(1, 300);
                ns.push_back(max(a, b));  // bias to larger
            } else {
                int a = rnd.next(1, 300), b = rnd.next(1, 300);
                ns.push_back(min(a, b));  // bias to smaller
            }
        }
    }

    // Shuffle the order of test cases
    shuffle(ns.begin(), ns.end());

    // Output
    println(T);
    for (int x : ns)
        println(x);

    return 0;
}
