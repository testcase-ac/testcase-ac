#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We read lines until we see a 0 (sentinel).
    // For non-zero N, it must satisfy 1 <= N <= 9999.
    // The total number of non-zero lines must be at most 100000.
    int cnt = 0;
    while (true) {
        // Read N, allowing 0 as sentinel or 1..9999 otherwise
        int N = inf.readInt(0, 9999, "N");
        inf.readEoln();

        if (N == 0) {
            // sentinel, stop reading further input
            break;
        }

        // Validate the actual constraint for non-sentinel values
        ensuref(N >= 1, "N must be at least 1, got %d", N);
        ensuref(N <= 9999, "N must be at most 9999, got %d", N);

        // Count test cases, enforce a reasonable upper bound
        cnt++;
        ensuref(cnt <= 100000, "Number of test cases exceeds 100000");
    }

    inf.readEof();
    return 0;
}
