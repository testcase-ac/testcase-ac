#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and B
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int B = inf.readInt(1, 100000, "B");
    inf.readEoln();

    // Read snow depths
    vector<int> f = inf.readInts(N, 0, 1000000000, "f_i");
    inf.readEoln();
    ensuref(f[0] == 0, "f_1 must be 0, found %d", f[0]);
    ensuref(f[N-1] == 0, "f_N must be 0, found %d", f[N-1]);

    // Read boot specs
    for (int i = 0; i < B; i++) {
        long long s = inf.readLong(0LL, 1000000000LL, "s_i");
        inf.readSpace();
        long long d = inf.readLong(1LL, (long long)N - 1LL, "d_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
