#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Prepare to check the global constraints
    long long maxN = 0;
    vector<long long> Ns;
    Ns.reserve(T);

    for (int tc = 0; tc < T; ++tc) {
        // Read N as token to check for leading zeros
        string n_str = inf.readToken("[0-9]+", "N");
        // Check for leading zeros (except for "0" itself, but N >= 1)
        ensuref(n_str.size() == 1 || n_str[0] != '0', 
            "Leading zeros in N at test case %d: '%s'", tc+1, n_str.c_str());

        // Parse N
        ensuref(n_str.size() <= 13, "N too long at test case %d: '%s'", tc+1, n_str.c_str());
        long long N = 0;
        for (char c : n_str) {
            N = N * 10 + (c - '0');
        }
        ensuref(N >= 1, "N must be at least 1 at test case %d, got %lld", tc+1, N);

        Ns.push_back(N);
        if (N > maxN) maxN = N;

        inf.readEoln();
    }

    // Now check the global constraints
    // At least one of:
    // 1. T == 1 and N <= 1e12
    // 2. T <= 100 and N <= 1e9 for all N
    // 3. T <= 1e4 and N <= 1e6 for all N

    bool cond1 = (T == 1 && maxN <= 1000000000000LL);
    bool cond2 = (T <= 100 && maxN <= 1000000000LL);
    bool cond3 = (T <= 10000 && maxN <= 1000000LL);

    ensuref(cond1 || cond2 || cond3,
        "Input does not satisfy any of the allowed (T,N) constraints: "
        "T=%d, maxN=%lld", T, maxN);

    inf.readEof();
}
