#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and D
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int D = inf.readInt(1, N - 1, "D");
    inf.readEoln();

    // Read K_i
    vector<long long> K = inf.readLongs(N, -1000000000LL, 1000000000LL, "K_i");
    inf.readEoln();

    inf.readEof();
}
