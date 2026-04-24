#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter for n: skew small or large
        int skew = rnd.any(vector<int>{-2, -1, 0, 1, 2});
        // Generate n in [1..10], skewed
        int n = rnd.wnext(10, skew) + 1;

        // Build various types of permutations S
        vector<int> S(n);
        for (int i = 0; i < n; i++) S[i] = i + 1;
        int type = rnd.next(0, 3);
        if (type == 0) {
            // Fully random
            shuffle(S.begin(), S.end());
        } else if (type == 1) {
            // Completely reversed
            reverse(S.begin(), S.end());
        } else if (type == 2) {
            // Random block rotation
            shuffle(S.begin(), S.end());
            if (n >= 2) {
                int a = rnd.next(0, n - 2);
                int len = rnd.next(1, n - a);
                rotate(S.begin() + a, S.begin() + a + len, S.end());
            }
        } else {
            // Mostly sorted with a few swaps
            for (int k = 0; k < n / 3; k++) {
                int i = rnd.next(0, n - 1);
                int j = rnd.next(0, n - 1);
                swap(S[i], S[j]);
            }
        }

        // Compute the Lehmer code R from S
        vector<int> R(n);
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < i; j++)
                if (S[j] < S[i]) cnt++;
            R[i] = cnt;  // always 0 <= cnt <= i
        }

        // Output this test case
        println(n);
        println(R);
    }

    return 0;
}
