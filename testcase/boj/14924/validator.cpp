#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S, T, D on one line
    int S = inf.readInt(1, 10000, "S");
    inf.readSpace();
    int T = inf.readInt(1, 10000, "T");
    // Validate T > S
    ensuref(T > S, "T must be greater than S, but got T=%d, S=%d", T, S);
    inf.readSpace();
    int D = inf.readInt(1, 10000, "D");
    // Validate D is a multiple of 2*S
    long long twoS = 2LL * S;
    ensuref(D % twoS == 0, "D must be a multiple of 2*S, but got D=%d, 2*S=%lld", D, twoS);
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
