#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_N = 1LL;
    const long long MAX_N = 200000000LL;
    const int MAX_CASES = 100000;

    int case_cnt = 0;
    while (!inf.seekEof()) {
        // Read n
        long long n = inf.readLong(MIN_N, MAX_N, "n");
        ++case_cnt;
        ensuref(case_cnt <= MAX_CASES, "Too many test cases: %d (max %d)", case_cnt, MAX_CASES);

        // After n, expect EOLN (not EOF, because if EOF, readLong would have failed)
        inf.readEoln();

        // If next is EOF, break; otherwise, continue
        if (inf.seekEof()) break;
    }

    inf.readEof();
}
