#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // According to the problem, each N is a natural number
    // and is chosen so that the number of tilings of a 4×N rectangle
    // does not exceed 2^31-1. It is known that for N >= 22,
    // the number of tilings exceeds 2^31-1, and for N <= 21 it does not.
    // Therefore we must enforce 1 <= N <= 21.
    for (int i = 0; i < T; i++) {
        int N = inf.readInt(1, 21, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
