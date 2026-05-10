#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;

    // First line: N and coupon string S
    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    string S = inf.readToken("[1-9\\?]+", "S");
    inf.readEoln();

    ensuref((int)S.size() == N,
            "Length of S must be exactly N, but got |S| = %d, N = %d",
            (int)S.size(), N);

    // Second line: integer A (1 <= A <= 10^100000)
    // Canonical decimal integer without leading zeros.
    string A = inf.readToken("[0-9]+", "A");
    inf.readEoln();

    // Check canonical form for A and numeric constraints 1 <= A <= 10^100000
    ensuref(A.size() >= 1 && A.size() <= 100000,
            "Length of A must be between 1 and 100000, got %d",
            (int)A.size());
    // No leading zeros
    if (A.size() > 1) {
        ensuref(A[0] != '0',
                "A must not have leading zeros, but starts with '0'");
    }
    // A >= 1 is guaranteed since first digit is non-zero and string is digits

    inf.readEof();
}
