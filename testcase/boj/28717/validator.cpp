#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read n natural numbers a_i in [2, 1e18]
    const long long MIN_A = 2LL;
    const long long MAX_A = (long long)1e18;

    vector<long long> a = inf.readLongs(n, MIN_A, MAX_A, "a_i");
    inf.readEoln();

    // No additional global constraints are specified in the statement:
    // - We do not enforce any property about possible answers.
    // - We do not check anything about gcds beyond basic range and format.
    // Just ensure we respected canonical integer format (handled by readLongs).

    inf.readEof();
}
