#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000; // generic upper bound if multiple testcases ever used

    // Problem statement does not mention multiple test cases.
    // So we validate a single test case format: n on first line, string on second line.

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // Read the string: length must be exactly n, characters only 'A', 'P', 'p'
    string s = inf.readToken("[APp]+", "s");
    inf.readEoln();

    ensuref((int)s.size() == n,
            "String length (%d) does not match n (%d)", (int)s.size(), n);

    // Global property: The output is the maximum number of non-overlapping subsequences
    // "pPAP" (pen, pineapple, apple, pen) in order and contiguous.
    // The statement guarantees just existence of input; no extra global property like
    // "answer always exists" or bounds on answer besides trivial n/4, which holds by construction.
    // So no additional global checks are required.

    inf.readEof();
}
