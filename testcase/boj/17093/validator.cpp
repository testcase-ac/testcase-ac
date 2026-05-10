#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read P points
    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(-1000000LL, 1000000LL, "P_x");
        inf.readSpace();
        long long y = inf.readLong(-1000000LL, 1000000LL, "P_y");
        inf.readEoln();
    }

    // Read Q points
    for (int i = 0; i < M; i++) {
        long long x = inf.readLong(-1000000LL, 1000000LL, "Q_x");
        inf.readSpace();
        long long y = inf.readLong(-1000000LL, 1000000LL, "Q_y");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
