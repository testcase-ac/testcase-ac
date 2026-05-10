#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int n = inf.readInt(2, 500000, "n");
    inf.readEoln();

    // 2. Read P_1 ... P_n
    vector<int> P = inf.readInts(n, -1000000000, 1000000000, "P_i");
    inf.readEoln();

    // 3. Check for extra input
    inf.readEof();
}
