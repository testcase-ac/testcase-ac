#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case, first line: n p0
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int p0 = inf.readInt(0, 100000000, "p0");
    inf.readEoln();

    const int MAX_SV = 1000000;

    // Read s_{1,1..n}
    vector<long long> s1 = inf.readLongs(n, 0LL, (long long)MAX_SV, "s_1j");
    inf.readEoln();

    // Read s_{2,1..n}
    vector<long long> s2 = inf.readLongs(n, 0LL, (long long)MAX_SV, "s_2j");
    inf.readEoln();

    // Read v_{1,1..n}
    vector<long long> v1 = inf.readLongs(n, 0LL, (long long)MAX_SV, "v_1j");
    inf.readEoln();

    // Read v_{2,1..n}
    vector<long long> v2 = inf.readLongs(n, 0LL, (long long)MAX_SV, "v_2j");
    inf.readEoln();

    // No additional global properties are guaranteed in the statement
    // beyond basic bounds, so no further checks are required.

    inf.readEof();
}
