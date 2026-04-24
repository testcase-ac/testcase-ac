#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of days
    int N = inf.readInt(1, 1500000, "N");
    inf.readEoln();

    // For each day i, read T_i and P_i
    for (int i = 1; i <= N; i++) {
        inf.readInt(1, 50, "T_i");
        inf.readSpace();
        inf.readInt(1, 1000, "P_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
