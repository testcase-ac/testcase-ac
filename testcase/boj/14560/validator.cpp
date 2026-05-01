#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of jobs
    int N = inf.readInt(1, 30, "N");
    inf.readEoln();

    // A_i: rewards for jobs
    vector<long long> A = inf.readLongs(N, 1LL, (long long)1e16, "A_i");
    inf.readEoln();

    // D: maximum allowed absolute difference of total rewards between Ad and Larry
    long long D = inf.readLong(0LL, (long long)1e18, "D");
    inf.readEoln();

    // No extra global properties are guaranteed in the statement that must be validated.
    // Just basic range / format checks above are enough.

    inf.readEof();
}
