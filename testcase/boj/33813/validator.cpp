#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and T
    int K = inf.readInt(1, 10000, "K");
    inf.readSpace();
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Read T lines, each with N_i
    for (int i = 0; i < T; ++i) {
        long long N = inf.readLong(1LL, 10000000000LL, "N_i");
        inf.readEoln();
    }

    inf.readEof();
}
