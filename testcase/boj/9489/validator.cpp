#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_N = 1, MAX_N = 1000;
    const int MIN_VAL = 1, MAX_VAL = 1000000;
    const int MAX_CASES = 100000;

    int case_cnt = 0;
    while (true) {
        // Read n and k
        int n = inf.readInt(0, MAX_N, "n");
        inf.readSpace();
        int k = inf.readInt(0, MAX_VAL, "k");
        inf.readEoln();

        if (n == 0 && k == 0) {
            break;
        }

        ++case_cnt;
        ensuref(case_cnt <= MAX_CASES, "Too many test cases: %d > %d", case_cnt, MAX_CASES);

        ensuref(n >= MIN_N, "n must be at least %d, got %d", MIN_N, n);
        ensuref(k >= MIN_VAL, "k must be at least %d, got %d", MIN_VAL, k);

        // Read the sequence
        vector<int> seq = inf.readInts(n, MIN_VAL, MAX_VAL, "sequence");
        inf.readEoln();

        // Check strictly increasing
        for (int i = 1; i < n; ++i) {
            ensuref(seq[i] > seq[i-1], "Sequence is not strictly increasing at index %d: %d >= %d", i, seq[i], seq[i-1]);
        }

        // Check k is in the sequence
        ensuref(find(seq.begin(), seq.end(), k) != seq.end(), "k=%d is not present in the sequence", k);

        // No further global properties to check (tree construction is for solution, not input validation)
    }

    inf.readEof();
}
