#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // N from 1 to 20, biased towards smaller values
    int N = rnd.wnext(20, -3) + 1;
    // Decide whether to generate a valid or invalid (impossible) case
    bool makeValid = rnd.next(0, 3) > 0;
    int M, K;
    if (makeValid || N == 1) {
        // Generate M, K such that M+K-1 <= N <= M*K
        M = rnd.next(1, N);
        int maxK = N - M + 1;
        int minK = (N + M - 1) / M;
        minK = max(minK, 1);
        if (minK > maxK) {
            // Choose an M for which a valid K exists
            vector<int> validM;
            for (int m = 1; m <= N; ++m) {
                int mk = (N + m - 1) / m;
                if (mk <= N - m + 1) validM.push_back(m);
            }
            if (!validM.empty()) M = rnd.any(validM);
            else M = 1;
            maxK = N - M + 1;
            minK = max((N + M - 1) / M, 1);
        }
        K = rnd.next(minK, maxK);
    } else {
        // Generate an impossible case: violate either M+K-1 <= N or N <= M*K
        do {
            M = rnd.next(1, N);
            K = rnd.next(1, N);
        } while (M + K - 1 <= N && 1LL * M * K >= N);
    }
    println(N, M, K);
    return 0;
}
