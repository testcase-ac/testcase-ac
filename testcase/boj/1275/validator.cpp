#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read initial array of N integers, each in signed 32-bit range
    vector<long long> initial = inf.readLongs(N, -2147483648LL, 2147483647LL, "initial");
    inf.readEoln();

    // Read Q operations
    for (int i = 0; i < Q; i++) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readSpace();
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        long long b = inf.readLong(-2147483648LL, 2147483647LL, "b_i");
        inf.readEoln();

        // Ensure the sum range is valid
        ensuref(x <= y,
                "Query %d: x (%d) must be <= y (%d)", i + 1, x, y);
    }

    inf.readEof();
    return 0;
}
