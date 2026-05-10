#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 5000, "Q");
    inf.readEoln();

    // Read A_1..A_N
    vector<int> A = inf.readInts(N, 1, 10000, "A_i");
    inf.readEoln();

    // For marking which indices have been set to zero (for 2 i queries)
    // But since the problem doesn't require us to check the queries' effect, we don't need to simulate.

    for (int q = 0; q < Q; ++q) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();

        if (type == 1) {
            // 1 x
            int x = inf.readInt(0, 100000000, "x");
            inf.readEoln();
        } else {
            // 2 i
            int i = inf.readInt(1, N, "i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
