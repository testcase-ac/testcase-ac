#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // 2. Read N*N GCD table values, all positive integers ≤ 1e9
    int NN = N * N;
    vector<int> g = inf.readInts(NN, 1, 1000000000, "g_ij");
    inf.readEoln();

    // 3. Check that there are exactly N*N values
    ensuref((int)g.size() == NN, "Expected %d GCD values, got %d", NN, (int)g.size());

    // 4. No extra input
    inf.readEof();
}
