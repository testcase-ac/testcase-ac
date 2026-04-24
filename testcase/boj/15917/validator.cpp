#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries Q
    int Q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    // For each query, read one integer a in [1, 2^31-1]
    for (int i = 0; i < Q; i++) {
        long long a = inf.readLong(1LL, 2147483647LL, "a");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
