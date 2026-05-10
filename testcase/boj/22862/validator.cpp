#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read S
    vector<int> S = inf.readInts(N, 1, 1000000, "S_i");
    inf.readEoln();

    inf.readEof();
}
