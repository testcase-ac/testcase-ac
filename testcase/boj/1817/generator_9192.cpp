#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 7);
    int N = 0;
    int M = 1;
    vector<int> w;

    switch (scenario) {
        case 1: { // N = 0 edge case
            M = rnd.next(1, 1000);
            N = 0;
            break;
        }
        case 2: { // Small random case
            N = rnd.next(1, 5);
            M = rnd.next(1, 20);
            w.resize(N);
            for (int i = 0; i < N; ++i)
                w[i] = rnd.next(1, M);
            break;
        }
        case 3: { // All equal weights
            int type = rnd.next(0, 1);
            if (type == 0) {
                // Weight == M, each book must be in its own box
                M = rnd.next(1, 50);
                N = rnd.next(1, 10);
                w.assign(N, M);
            } else {
                // Same nontrivial weight
                M = rnd.next(2, 50);
                int candidates[4] = {1, M / 2, M / 2 + 1, M - 1};
                int wt = candidates[rnd.next(0, 3)];
                if (wt < 1) wt = 1;
                if (wt > M) wt = M;
                N = rnd.next(1, 15);
                w.assign(N, wt);
            }
            break;
        }
        case 4: { // All books fit into a single box (sum <= M)
            N = rnd.next(1, 10);
            M = rnd.next(N, 100); // ensure M >= N to allow positive composition
            int S = rnd.next(N, M); // total weight S, N positive parts

            w.resize(N);
            if (N == 1) {
                // Single book takes all the weight
                w[0] = S;
            } else {
                // Random composition of S into N positive integers
                // Choose N-1 distinct cut points from [1, S-1]
                vector<int> allPos(S - 1);
                iota(allPos.begin(), allPos.end(), 1);
                shuffle(allPos.begin(), allPos.end());

                vector<int> cuts(allPos.begin(), allPos.begin() + (N - 1));
                sort(cuts.begin(), cuts.end());

                w[0] = cuts[0];
                for (int i = 1; i < N - 1; ++i)
                    w[i] = cuts[i] - cuts[i - 1];
                w[N - 1] = S - cuts.back();
            }
            break;
        }
        case 5: { // Order-sensitive vs sum/M (heavy books > M/2 and < M)
            M = rnd.next(5, 20);
            int heavy = rnd.next(M / 2 + 1, M - 1); // ensure > M/2 and < M
            N = rnd.next(3, 10);
            w.assign(N, heavy);
            break;
        }
        case 6: { // Many boxes: small M, weights close to M
            M = rnd.next(2, 10);
            N = rnd.next(10, 20);
            w.resize(N);
            for (int i = 0; i < N; ++i) {
                int lo = max(1, M - 2);
                int hi = M;
                w[i] = rnd.next(lo, hi);
            }
            break;
        }
        case 7: { // Medium random case
            N = rnd.next(10, 25);
            M = rnd.next(20, 1000);
            w.resize(N);
            for (int i = 0; i < N; ++i)
                w[i] = rnd.next(1, M);
            break;
        }
    }

    println(N, M);
    if (N > 0)
        println(w);

    return 0;
}
