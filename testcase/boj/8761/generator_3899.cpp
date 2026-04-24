#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int Z = rnd.next(1, 10);
    println(Z);

    for (int zi = 0; zi < Z; zi++) {
        // Small N for hand-checkability
        int N = rnd.next(2, 10);
        println(N);

        // Initialize all stations as single-platform
        vector<int> s(N, 1);

        // Choose a generation mode for diversity
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            // Random density of two-platform stations
            double density = rnd.next(0.0, 1.0);
            for (int i = 0; i < N; i++) {
                if (rnd.next() < density)
                    s[i] = 2;
            }
            // Ensure at least one 2
            bool has2 = false;
            for (int x : s) if (x == 2) { has2 = true; break; }
            if (!has2) {
                s[rnd.next(0, N - 1)] = 2;
            }
        } else if (mode == 1) {
            // Exactly one two-platform station
            int pos = rnd.next(0, N - 1);
            s[pos] = 2;
        } else if (mode == 2) {
            // Random number K of two-platform stations
            int K = rnd.next(1, N);
            vector<int> idx(N);
            iota(idx.begin(), idx.end(), 0);
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < K; i++) {
                s[idx[i]] = 2;
            }
        } else {
            // Ensure both ends are two-platform, random inside
            for (int i = 1; i < N - 1; i++) {
                s[i] = (rnd.next() < 0.5 ? 2 : 1);
            }
            s[0] = s[N - 1] = 2;
        }

        // Output station platforms
        println(s);
    }

    return 0;
}
