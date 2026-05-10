#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, D, K
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int D = inf.readInt(1, 100, "D");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Read s_i
    vector<int> s = inf.readInts(N, 1, K, "s_i");
    inf.readEoln();

    // No further global constraints implied beyond simple bounds

    inf.readEof();
}
