#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read the prices P_1 ... P_N
    inf.readInts(N, 1, 10000, "P_i");
    inf.readEoln();

    // No further global constraints to check
    inf.readEof();
    return 0;
}
