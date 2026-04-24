#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20, "M");
    inf.readEoln();

    // Read the N lines of (investment amount) and M profits
    for (int i = 1; i <= N; i++) {
        // The problem guarantees that the i-th of these lines must have investment amount = i
        int t = inf.readInt(1, N, "investment_amount");
        inf.readSpace();

        // Each profit is non-negative and the total maximum is < 2^31, so each entry fits in [0, 2^31-1]
        vector<int> profits = inf.readInts(M, 0, 2147483647, "profit");
        inf.readEoln();

        ensuref(t == i,
                "The %d-th investment amount must be %d, but found %d",
                i, i, t);
    }

    inf.readEof();
    return 0;
}
