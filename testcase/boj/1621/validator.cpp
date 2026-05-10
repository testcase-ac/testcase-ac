#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // 2. Read K and C
    int K = inf.readInt(1, 10000, "K");
    inf.readSpace();
    int C = inf.readInt(1, 10000, "C");
    inf.readEoln();

    // 3. Read banana weights
    vector<int> w = inf.readInts(N, 1, 1000, "w_i");
    inf.readEoln();

    inf.readEof();
}
