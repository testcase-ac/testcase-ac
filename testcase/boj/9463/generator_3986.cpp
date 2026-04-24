#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    // Patterns for permutation generation
    vector<int> ts = {-2, -1, 0, 1, 2};
    vector<string> patterns = {"sorted", "reversed", "one_swap", "random", "rotated"};

    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter for size: skewed or uniform distribution
        int t = rnd.any(ts);
        int n = rnd.wnext(10, t) + 1;  // gives n in [1,10]

        // Generate first permutation
        vector<int> p1(n);
        iota(p1.begin(), p1.end(), 1);
        int pat1 = rnd.next(0, (int)patterns.size() - 1);
        if (patterns[pat1] == "reversed") {
            reverse(p1.begin(), p1.end());
        } else if (patterns[pat1] == "one_swap" && n >= 2) {
            int i = rnd.next(0, n-1), j = rnd.next(0, n-1);
            while (j == i) j = rnd.next(0, n-1);
            swap(p1[i], p1[j]);
        } else if (patterns[pat1] == "random") {
            shuffle(p1.begin(), p1.end());
        } else if (patterns[pat1] == "rotated" && n >= 2) {
            int k = rnd.next(1, n-1);
            rotate(p1.begin(), p1.begin() + k, p1.end());
        }
        // else "sorted" or small n cases do nothing

        // Generate second permutation
        vector<int> p2(n);
        iota(p2.begin(), p2.end(), 1);
        int pat2 = rnd.next(0, (int)patterns.size() - 1);
        if (patterns[pat2] == "reversed") {
            reverse(p2.begin(), p2.end());
        } else if (patterns[pat2] == "one_swap" && n >= 2) {
            int i = rnd.next(0, n-1), j = rnd.next(0, n-1);
            while (j == i) j = rnd.next(0, n-1);
            swap(p2[i], p2[j]);
        } else if (patterns[pat2] == "random") {
            shuffle(p2.begin(), p2.end());
        } else if (patterns[pat2] == "rotated" && n >= 2) {
            int k = rnd.next(1, n-1);
            rotate(p2.begin(), p2.begin() + k, p2.end());
        }

        // Output this test case
        println(n);
        println(p1);
        println(p2);
    }

    return 0;
}
