#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 300000000LL, "M");
    inf.readEoln();

    // Read sequence A of length N
    vector<int> A = inf.readInts(N, 1, 30000, "A_i");
    inf.readEoln();

    // No additional global constraints to check

    inf.readEof();
    return 0;
}
