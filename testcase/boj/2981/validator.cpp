#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of integers
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();

    // Read the N numbers, each on its own line
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readEoln();
    }

    // Check for duplicates
    {
        set<long long> st(a.begin(), a.end());
        ensuref((int)st.size() == N, "Duplicate numbers detected: expected all distinct");
    }

    // Sort to compute differences
    sort(a.begin(), a.end());

    // Compute G = gcd of all (a[i] - a[0]) for i = 1..N-1
    long long G = a[1] - a[0];
    for (int i = 2; i < N; i++) {
        long long diff = a[i] - a[0];
        G = std::gcd(G, diff);
    }

    // According to problem, there must be at least one M > 1,
    // so G must be >= 2 (since M are divisors of G > 1).
    ensuref(G > 1, "No valid M exists: gcd of differences is %lld <= 1", G);

    // End of file checks
    inf.readEof();
    return 0;
}
