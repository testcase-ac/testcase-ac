#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int K = inf.readInt(2, 5, "K");
    inf.readEoln();

    // Read bead colors
    vector<int> a = inf.readInts(N, 1, 100, "color");
    inf.readEoln();

    // No other implicit constraints to verify
    inf.readEof();
    return 0;
}
