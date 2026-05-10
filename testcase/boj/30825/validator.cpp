#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 200000, "K");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 100000, "A_i");
    inf.readEoln();

    inf.readEof();
}
