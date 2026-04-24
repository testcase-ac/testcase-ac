#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and S
    int N = inf.readInt(1, 40, "N");
    inf.readSpace();
    long long S = inf.readLong(-1000000LL, 1000000LL, "S");
    inf.readEoln();

    // Read the sequence of N integers
    vector<int> a = inf.readInts(N, -100000, 100000, "a_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
