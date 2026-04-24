#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 150, "N");
    inf.readEoln();

    // Read the N scores S_1 ... S_N
    vector<int> S = inf.readInts(N, 1, 100, "S_i");
    inf.readEoln();

    // Read K
    long long K = inf.readLong(1LL, 2000000000LL, "K");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
