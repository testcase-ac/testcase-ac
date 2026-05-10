#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 2 * N, "K");
    inf.readEoln();

    vector<ll> A = inf.readLongs(N, 1LL, 1000000000LL, "A_i");
    inf.readEoln();
    vector<ll> B = inf.readLongs(N, 1LL, 1000000000LL, "B_i");
    inf.readEoln();

    // No additional global properties to validate:
    // - Sequence order is arbitrary.
    // - No constraints on sums or answer existence beyond basic ranges above.

    inf.readEof();
}
