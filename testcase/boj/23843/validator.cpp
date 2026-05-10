#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // Read the N charging times
    vector<int> t = inf.readInts(N, 1, 1 << 15, "t_i");
    inf.readEoln();

    // Each time must be a power of two: ti = 2^k for 0 <= k <= 15
    for (int i = 0; i < N; i++) {
        int ti = t[i];
        ensuref((ti & (ti - 1)) == 0,
                "t_i[%d] = %d is not a power of two", i, ti);
    }

    inf.readEof();
    return 0;
}
