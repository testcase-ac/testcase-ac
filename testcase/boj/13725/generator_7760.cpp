#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: order k between 1 and 10
    int k = rnd.next(1, 10);
    long long kll = k;
    // Hyper-parameter: N can be small (<=k), moderate (k+1..k+100), or very large (up to 1e18)
    long long N;
    if (rnd.next(0, 1) == 0) {
        N = rnd.next(1LL, kll);
    } else if (rnd.next(0, 1) == 0) {
        long long lo = kll + 1, hi = kll + 100;
        N = rnd.next(lo, hi);
    } else {
        const long long Nmax = 1000000000000000000LL;
        int t = rnd.next(-3, 3);  // bias parameter
        long long x = rnd.wnext(Nmax, t); // in [0, Nmax-1]
        N = x + 1;
        if (N <= kll) N = kll + 1;
    }
    const int MOD = 104857601;
    // Initial terms A_i
    vector<long long> A(k);
    for (int i = 0; i < k; i++) {
        A[i] = rnd.next(0, MOD - 1);
    }
    // Coefficients C_i with random sparsity
    vector<long long> C(k);
    double density = rnd.next();
    for (int i = 0; i < k; i++) {
        if (rnd.next() < density) C[i] = rnd.next(0, MOD - 1);
        else C[i] = 0;
    }
    // Output
    println(k, N);
    println(A);
    println(C);
    return 0;
}
