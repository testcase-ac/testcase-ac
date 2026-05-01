#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 8);
    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter for n: skewed between 1 and 15
        int t = rnd.next(-3, 3);
        int n = rnd.wnext(15, t) + 1;  // yields [1..15]

        // Hyper-parameter for total sum S: skewed between 0 and 30
        int t2 = rnd.next(-5, 5);
        int S = rnd.wnext(31, t2);     // yields [0..30]

        // Generate a random composition of S into n non-negative parts
        vector<int> pool;
        pool.reserve(S + max(0, n - 1));
        // Use 1 to represent a "star", and 0 as separators
        for (int i = 0; i < S; i++) pool.push_back(1);
        for (int i = 0; i < n - 1; i++) pool.push_back(0);
        shuffle(pool.begin(), pool.end());

        vector<int> ratings;
        ratings.reserve(n);
        int cnt = 0;
        for (int x : pool) {
            if (x == 1) {
                cnt++;
            } else {
                ratings.push_back(cnt);
                cnt = 0;
            }
        }
        ratings.push_back(cnt);  // last bin

        // Output this test case
        printf("%d", n);
        for (int r : ratings) {
            printf(" %d", r);
        }
        printf("\n");
    }

    // Termination line
    println(0);
    return 0;
}
