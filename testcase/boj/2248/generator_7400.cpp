#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in small, medium, or large range
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(1, 5);
    } else if (mode == 1) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 31);
    }

    // Choose L, sometimes extreme, sometimes random
    int L;
    if (rnd.next(0, 1) == 0) {
        // pick either 1 or N
        L = (rnd.next(0, 1) == 0 ? 1 : N);
    } else {
        L = rnd.next(1, N);
    }

    // Precompute binomial coefficients C[n][k]
    vector<vector<long long>> C(N+1, vector<long long>(N+1, 0));
    for (int i = 0; i <= N; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    // Total number of valid strings
    long long total = 0;
    for (int k = 0; k <= L; k++) {
        total += C[N][k];
    }

    // Choose I, sometimes first, sometimes last, often random
    long double p = rnd.next();
    long long I;
    if (p < 0.15) {
        I = 1;
    } else if (p < 0.30) {
        I = total;
    } else {
        I = rnd.next((long long)1, total);
    }

    // Output the test case
    println(N, L, I);
    return 0;
}
