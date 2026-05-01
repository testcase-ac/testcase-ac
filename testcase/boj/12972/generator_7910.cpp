#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias towards small values, but allow up to 10
    int r = rnd.next(0, 9);
    int N;
    if (r == 0) N = 1;
    else if (r <= 2) N = 2;
    else N = rnd.next(3, 10);

    // Number of distinct base values
    int U = (N > 1 ? rnd.next(1, N) : 1);

    // Generate base values with mixed sizes
    vector<long long> base(U);
    for (int i = 0; i < U; i++) {
        if (rnd.next(0, 1) == 0)
            base[i] = rnd.next(1, 100);      // small
        else
            base[i] = rnd.next(101, 1000);   // medium
    }

    // Build the original sequence A with possible multiples of base values
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        int idx = rnd.next(0, U - 1);
        int mul = rnd.next(1, 3);
        A[i] = base[idx] * mul;
    }

    // Compute the GCD table and flatten it
    vector<long long> G;
    G.reserve(N * N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            G.push_back(std::gcd(A[i], A[j]));
        }
    }

    // Shuffle the entries to randomize order
    shuffle(G.begin(), G.end());

    // Output
    println(N);
    println(G);

    return 0;
}
