#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each point
    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
