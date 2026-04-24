#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200, "M");
    inf.readEoln();

    // Read M constraints (L_i, S_i)
    for (int i = 1; i <= M; i++) {
        int L = inf.readInt(1, N, "L_i");
        inf.readSpace();
        long long S = inf.readLong(1LL, 1000000000LL, "S_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
