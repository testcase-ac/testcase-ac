#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N (number of workers) and W (available money)
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    long long W = inf.readLong(1LL, 10000000000LL, "W");
    inf.readEoln();

    // Read each worker's minimum wage S_i and qualification level Q_i
    for (int i = 0; i < N; i++) {
        int S = inf.readInt(1, 20000, "S_i");
        inf.readSpace();
        int Q = inf.readInt(1, 20000, "Q_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
