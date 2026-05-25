#include "testlib.h"
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAX_A_DIGITS = 100001; // 10^100000 has 100001 decimal digits.

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    string S = inf.readToken("[1-9\\?]+", "S");
    inf.readEoln();

    ensuref((int)S.size() == N,
            "Length of S must be exactly N, but got |S| = %d, N = %d",
            (int)S.size(), N);

    string A = inf.readToken("[1-9][0-9]*", "A");
    inf.readEoln();

    ensuref((int)A.size() <= MAX_A_DIGITS,
            "A has too many decimal digits: %d", (int)A.size());
    if ((int)A.size() == MAX_A_DIGITS) {
        ensuref(A[0] == '1',
                "The only valid %d-digit A is 10^100000", MAX_A_DIGITS);
        ensuref(all_of(A.begin() + 1, A.end(), [](char c) { return c == '0'; }),
                "The only valid %d-digit A is 10^100000", MAX_A_DIGITS);
    }

    inf.readEof();
}
