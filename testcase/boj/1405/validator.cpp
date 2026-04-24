#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of moves, natural number (>=1) and <=14
    int N = inf.readInt(1, 14, "N");
    inf.readSpace();

    // Read probabilities for East, West, South, North
    int pE = inf.readInt(0, 100, "pE");
    inf.readSpace();
    int pW = inf.readInt(0, 100, "pW");
    inf.readSpace();
    int pS = inf.readInt(0, 100, "pS");
    inf.readSpace();
    int pN = inf.readInt(0, 100, "pN");

    // End of the only line
    inf.readEoln();

    // The probabilities must sum to 100
    ensuref(pE + pW + pS + pN == 100,
            "Sum of probabilities must be 100, but got %d", pE + pW + pS + pN);

    // No more data
    inf.readEof();

    return 0;
}
