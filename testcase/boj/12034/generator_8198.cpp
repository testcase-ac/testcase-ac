#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: at least 2, at most 6
    int T = rnd.next(2, 6);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        vector<long long> orig;
        int N;
        if (tc == 0) {
            // Special tricky case with overlapping values (12 appears as both discounted and original)
            N = 4;
            orig = {4, 8, 12, 16};
        } else if (tc == 1) {
            // Trivial smallest case N=1
            N = 1;
            orig = {4LL * rnd.next(1, 25)};
        } else {
            // General random case
            N = rnd.next(2, 10);
            orig.resize(N);
            for (int i = 0; i < N; i++) {
                // original prices are multiples of 4, up to 100
                orig[i] = 4LL * rnd.next(1, 25);
            }
            // allow duplicates and sort
            sort(orig.begin(), orig.end());
        }

        // Build merged sorted list of discounted and original prices
        vector<long long> all(2 * N);
        for (int i = 0; i < N; i++) {
            long long o = orig[i];
            long long d = o * 3 / 4;  // discounted price
            all[i] = d;
            all[i + N] = o;
        }
        sort(all.begin(), all.end());

        // Output this test case
        println(N);
        println(all);
    }

    return 0;
}
