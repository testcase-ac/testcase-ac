/* generator code */
#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for clarity
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Compute binomial coefficients up to N+M
    int NM = N + M;
    vector<vector<long long>> C(NM + 1, vector<long long>(NM + 1, 0));
    for (int i = 0; i <= NM; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    long long tot = C[NM][N];  // total number of strings

    // Decide whether to generate a valid K or an invalid one
    bool makeInvalid = rnd.next() < 0.2;  // 20% chance to be invalid
    long long K;
    if (makeInvalid) {
        long long low = tot + 1;
        long long high = min(tot + 10, 1000000000LL);
        if (low > high) low = high;
        K = rnd.next((int)low, (int)high);
    } else {
        long long high = min(tot, 1000000000LL);
        if (high < 1) high = 1;
        K = rnd.next(1, (int)high);
    }

    // Output the single test case
    println(N, M, K);
    return 0;
}
