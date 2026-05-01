#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose even N between 2 and 20
    int k = rnd.next(1, 10);
    int N = 2 * k;
    vector<int> A;
    // Decide whether to generate a possible or impossible case
    bool possible = rnd.next(0, 1) == 1;
    if (possible) {
        // Build A as concatenation of even palindromic segments
        int rem = N;
        while (rem > 0) {
            int maxPairs = rem / 2;
            // Randomly choose number of pairs in this segment
            int pairs = rnd.next(1, maxPairs);
            // Occasionally bias to use the whole remainder
            if (rem > 2 && rnd.next(0, 3) == 0) {
                pairs = maxPairs;
            }
            int Li = pairs * 2;
            // Adjust if leftover would be invalid (<2 but >0)
            if (rem - Li > 0 && rem - Li < 2) {
                Li = rem - 2;
                if (Li % 2 != 0) Li--;
                if (Li <= 0) Li = 2;
                pairs = Li / 2;
            }
            vector<int> seg(Li);
            // Fill segment as palindrome
            for (int j = 0; j < pairs; j++) {
                int x = rnd.next(1, 10000);
                seg[j] = seg[Li - 1 - j] = x;
            }
            A.insert(A.end(), seg.begin(), seg.end());
            rem -= Li;
        }
    } else {
        // Impossible case: all distinct elements, no even palindrome can form
        A.resize(N);
        for (int i = 0; i < N; i++) A[i] = i + 1;
        shuffle(A.begin(), A.end());
    }
    // Output
    println(N);
    println(A);
    return 0;
}
