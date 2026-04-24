#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of days
    int N = inf.readInt(1, 15, "N");
    inf.readEoln();

    // For each day i = 1..N, read T_i and P_i
    for (int i = 1; i <= N; i++) {
        // T_i: days needed for this consultation
        int T = inf.readInt(1, 5, "T_i");
        inf.readSpace();
        // P_i: profit for this consultation
        int P = inf.readInt(1, 1000, "P_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
