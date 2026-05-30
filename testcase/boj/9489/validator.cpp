#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_N = 1, MAX_N = 1000;
    const int MIN_VAL = 1, MAX_VAL = 1000000;
    const int MAX_CASES = 100000;
    const int MAX_TOTAL_N = 1000000;

    int case_cnt = 0;
    int total_n = 0;
    while (true) {
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

        // CHECK: The statement does not bound the number of test cases.
        total_n += n;
        ensuref(total_n <= MAX_TOTAL_N, "total n must be at most %d, got %d", MAX_TOTAL_N, total_n);

        vector<int> seq = inf.readInts(n, MIN_VAL, MAX_VAL, "sequence");
        inf.readEoln();

        for (int i = 1; i < n; ++i) {
            ensuref(seq[i] > seq[i-1], "Sequence is not strictly increasing at index %d: %d >= %d", i, seq[i], seq[i-1]);
        }

        if (n > 1) {
            ensuref(seq[1] > seq[0] + 1, "first child value must be greater than root + 1");
        }

        ensuref(find(seq.begin(), seq.end(), k) != seq.end(), "k=%d is not present in the sequence", k);
    }

    inf.readEof();
}
