#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, T
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(2, 100000, "K");
    inf.readSpace();
    int T = inf.readInt(0, 1000000000, "T");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 0, K - 1, "A_i");
    inf.readEoln();

    inf.readEof();
}
