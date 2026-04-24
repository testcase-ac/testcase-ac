#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of test cases T
    double pT = rnd.next();
    int T;
    if (pT < 0.3)      T = rnd.next(1, 3);
    else if (pT < 0.8) T = rnd.next(4, 6);
    else               T = rnd.next(7, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Pick a scenario type to diversify edge cases
        int type = rnd.next(0, 3);

        // Small N for hand‐checkable cases
        int N = rnd.next(1, 10);

        // K choice: sometimes small, sometimes mid
        int K;
        if (type == 2) {
            // fully random
            K = rnd.next(1, 10);
        } else {
            double pK = rnd.next();
            if (pK < 0.5) K = rnd.next(1, 5);
            else          K = rnd.next(6, 10);
        }

        println(N, K);

        vector<int> candies(N);
        if (type == 0) {
            // All candies < K => answer = 0
            for (int i = 0; i < N; ++i) {
                candies[i] = rnd.next(1, max(1, K - 1));
            }
        }
        else if (type == 1) {
            // All are exact multiples of K
            int maxm = max(1, 20 / K);
            for (int i = 0; i < N; ++i) {
                candies[i] = rnd.next(1, maxm) * K;
                if (candies[i] == 0) candies[i] = K;
            }
        }
        else if (type == 2) {
            // Completely random in [1,20]
            for (int i = 0; i < N; ++i)
                candies[i] = rnd.next(1, 20);
        }
        else {
            // Mixed: half multiples, half non‐multiples
            int half = N / 2;
            int maxm = max(1, 20 / K);
            for (int i = 0; i < half; ++i) {
                candies[i] = rnd.next(1, maxm) * K;
                if (candies[i] == 0) candies[i] = K;
            }
            for (int i = half; i < N; ++i) {
                int x = rnd.next(1, 20);
                if (x % K == 0) {
                    // adjust to non multiple
                    x = x == 20 ? 19 : x + 1;
                }
                candies[i] = x;
            }
        }

        // Shuffle so order is random
        shuffle(candies.begin(), candies.end());
        println(candies);
    }

    return 0;
}
