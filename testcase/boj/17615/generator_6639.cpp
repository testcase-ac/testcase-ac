#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate N biased towards small values but up to 30
    int N = rnd.wnext(30, -2) + 1; // [1..30], skewed small

    string s;
    // Occasionally produce all same colors
    if (rnd.next(0, 9) == 0 || N == 1) {
        char c = rnd.any(string("RB"));
        s = string(N, c);
    } else {
        // Mixed colors: choose number of runs between 2 and min(N,10)
        int rmax = min(N, 10);
        int runs = rnd.wnext(rmax - 1, -1) + 2; // [2..rmax], skewed small

        // Partition N into 'runs' positive lengths
        vector<int> len(runs);
        int rem = N;
        for (int i = 0; i < runs - 1; i++) {
            // leave at least 1 for each remaining run
            int maxv = rem - (runs - i - 1);
            len[i] = rnd.next(1, maxv);
            rem -= len[i];
        }
        len[runs - 1] = rem;
        // Build string with alternating colors
        char start = rnd.any(string("RB"));
        s.reserve(N);
        for (int i = 0; i < runs; i++) {
            char c = (i % 2 == 0 ? start : (start == 'R' ? 'B' : 'R'));
            s += string(len[i], c);
        }
    }

    // Output
    println(N);
    println(s);
    return 0;
}
