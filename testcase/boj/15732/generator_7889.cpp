#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with variability: small or medium
    int N;
    if (rnd.next(2) == 0) N = rnd.next(1, 10);
    else N = rnd.next(5, 30);

    // Choose K relative to N
    int K = rnd.next(1, min(10, 2 * N));

    vector<int> A(K), B(K), C(K);
    for (int i = 0; i < K; i++) {
        // Some rules start at 1 to test prefix behavior
        if (rnd.next(4) == 0) A[i] = 1;
        else A[i] = rnd.next(1, N);
        // Some rules dense (C=1), others varied
        if (rnd.next(3) == 0) C[i] = 1;
        else C[i] = rnd.next(1, A[i]);
        B[i] = rnd.next(A[i], N);
    }

    // Compute total capacity T
    long long T = 0;
    for (int i = 0; i < K; i++) {
        if (B[i] < A[i]) continue;
        T += ( (B[i] - A[i]) / C[i] + 1 );
    }
    // D in [1, T]
    long long D = rnd.next(1LL, T);

    // Output
    println(N, K, D);
    for (int i = 0; i < K; i++) {
        println(A[i], B[i], C[i]);
    }
    return 0;
}
