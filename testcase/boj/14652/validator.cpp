#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K with strict whitespace rules
    int N = inf.readInt(1, 30000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 30000, "M");
    inf.readSpace();
    // K must be between 0 and N*M-1
    long long maxK = (long long)N * M - 1;
    inf.readLong(0LL, maxK, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
