#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity within hand-verifiable limits
    vector<int> Ns = {1, 2, 5, 10, 15};
    vector<int> Ms = {1, 2, 5, 10};

    int N = rnd.any(Ns);
    int M = rnd.any(Ms);

    // profit[j][k]: profit for company j when investing k
    vector<vector<long long>> profit(M, vector<long long>(N + 1, 0));

    for (int j = 0; j < M; j++) {
        int pat = rnd.next(0, 2);
        if (pat == 0) {
            // Pure random profits
            for (int k = 1; k <= N; k++) {
                profit[j][k] = rnd.next(0, 100);
            }
        } else {
            // Convex or concave pattern via sorted marginal returns
            vector<int> d(N);
            for (int i = 0; i < N; i++) {
                d[i] = rnd.next(1, 10);
            }
            if (pat == 1) {
                // Concave: decreasing marginal returns
                sort(d.begin(), d.end(), greater<int>());
            } else {
                // Convex: increasing marginal returns
                sort(d.begin(), d.end());
            }
            long long s = 0;
            for (int k = 1; k <= N; k++) {
                s += d[k - 1];
                profit[j][k] = s;
            }
        }
    }

    // Output
    println(N, M);
    for (int k = 1; k <= N; k++) {
        printf("%d", k);
        for (int j = 0; j < M; j++) {
            printf(" %lld", profit[j][k]);
        }
        printf("\n");
    }

    return 0;
}
