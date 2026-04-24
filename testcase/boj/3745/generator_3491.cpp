#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Small N
        int N = rnd.next(1, 10);
        // Choose a pattern for diversity
        int pat = rnd.next(0, 4);
        // Upper bound for values
        int maxVal = rnd.next(max( N, 1 ), 20);
        vector<int> a(N);
        if (pat == 0) {
            // Pure random
            for (int i = 0; i < N; i++)
                a[i] = rnd.next(1, maxVal);
        } else if (pat == 1) {
            // Strictly increasing
            int start = rnd.next(1, maxVal - (N - 1));
            for (int i = 0; i < N; i++)
                a[i] = start + i;
        } else if (pat == 2) {
            // Strictly decreasing
            int start = rnd.next(N, maxVal);
            for (int i = 0; i < N; i++)
                a[i] = start - i;
        } else if (pat == 3) {
            // Plateaus: several equal-run blocks
            int B = rnd.next(1, min(N, 5));
            vector<int> bs(B, 1);
            int rem = N - B;
            for (int i = 0; i < rem; i++) {
                int j = rnd.next(0, B - 1);
                bs[j]++;
            }
            int idx = 0;
            for (int b = 0; b < B; b++) {
                int v = rnd.next(1, maxVal);
                for (int k = 0; k < bs[b]; k++)
                    a[idx++] = v;
            }
        } else {
            // Bitonic: up then down using unique values
            if (N < 3) {
                for (int i = 0; i < N; i++)
                    a[i] = rnd.next(1, maxVal);
            } else {
                // Sample N distinct values
                vector<int> pool;
                for (int v = 1; v <= maxVal; v++)
                    pool.push_back(v);
                shuffle(pool.begin(), pool.end());
                pool.resize(N);
                sort(pool.begin(), pool.end());
                int peak = rnd.next(1, N - 2);
                // Build bitonic
                for (int i = 0; i <= peak; i++)
                    a[i] = pool[i];
                for (int i = peak + 1; i < N; i++) {
                    int j = N - 1 - (i - (peak + 1));
                    a[i] = pool[j];
                }
            }
        }
        // Output this test case
        println(N);
        println(a);
    }
    return 0;
}
