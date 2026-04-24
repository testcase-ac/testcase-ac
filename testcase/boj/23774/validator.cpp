#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of slices
    int n = inf.readInt(3, 500000, "n");
    inf.readEoln();

    // Read spiciness array s[1..n]
    // Each s_i must be in [0, 1e13]
    const long long MAX_S = 10000000000000LL;  // 10^13
    vector<long long> s = inf.readLongs(n, 0LL, MAX_S, "s_i");
    inf.readEoln();

    // No further global constraints to check for this problem:
    // the input is simply an integer n followed by n values.
    // Since there are no multiple test cases, we now expect EOF.
    inf.readEof();

    return 0;
}
