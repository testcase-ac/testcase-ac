#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 1000000000000LL, "M");
    inf.readEoln();

    // Read array A of size N
    vector<long long> A = inf.readLongs(N, 1LL, 1000000000000LL, "A_i");
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
